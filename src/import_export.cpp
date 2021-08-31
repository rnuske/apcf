/*===========================================================================*\
 *                        Reading and writing Geodata
 *
 * - import_polys:        OGR (~any format) -> GEOS
 * - geometries_from_sfc: SF -> GEOS
 * - export_polys:        GEOS -> OGR (~any format)
 * - sfc_from_geometry:   GEOS -> SF
\*===========================================================================*/

#include <Rcpp.h>        // Rcpp
#include <vector>        // vector
#include <gdal.h>        // GDAL* &  OGR* functions (includes ogr_api.h)
#include <ogr_srs_api.h> // OSR* functions
#include <geos_c.h>      // GEOS* functions
#include <cpl_conv.h>    // CPLFree

#include "import_export.h"
#include "geos_stuff.h"


/* GDAL Version
 *-----------------------------------------------------------------------------
 * adapted from sf (https://github.com/edzer/sfr/blob/master/src/geos.cpp)
 */
// [[Rcpp::export]]
std::string gdal_version(const char* what="RELEASE_NAME")
{
    return GDALVersionInfo(what);
}


/* import polys
 *-----------------------------------------------------------------------------
 *
 * adapted from the OGR tutorial (https://gdal.org/tutorials/vector_api_tut.html)
 */
std::vector<GEOSGeometry*>
import_polys(GEOSContextHandle_t geosCtxtH,
             const char *datasource,
             OGRSpatialReferenceH *hSRS)
{
    GDALAllRegister();

    // open file for reading --------------------------------------------------
    GDALDatasetH hDS = GDALOpenEx(datasource, GDAL_OF_VECTOR, NULL, NULL, NULL);
    if(hDS == NULL)
    {
        Rcpp::Rcout << "Cannot open data source '" << datasource << "'." << std::endl;
        throw std::invalid_argument("Open failed.");
    }

    // grep first layer -------------------------------------------------------
    int nLayer = GDALDatasetGetLayerCount(hDS);
    if(nLayer < 1)
    {
        throw std::invalid_argument("Error: no layers in datasource.");
    }
    else if(nLayer > 1)
    {
        Rcpp::warning("Multiple layers are present in datasource. Reading first layer.");
    }

    OGRLayerH hLayer = GDALDatasetGetLayer(hDS, 0);


    // ensure it's a Polygon --------------------------------------------------
    OGRwkbGeometryType geomType = OGR_L_GetGeomType(hLayer);

    if (wkbFlatten(geomType) != wkbPolygon)
    {
        // other possible types we might want to handle in the future:
        // wkbMultiPolygon wkbPolygonM wkbMultiPolygonM
        // wkbPolygonZM wkbMultiPolygonZM wkbPolygon25D wkbMultiPolygon25D
        throw std::invalid_argument("Input Geometry must be of type polygon.");
    }

    // fetch SpatialReference -------------------------------------------------
    if(hSRS != NULL)
    {
        OGRSpatialReferenceH srs = OGR_L_GetSpatialRef(hLayer);
        *hSRS = OSRClone(srs);
    }

    // iterate over features and convert --------------------------------------
    OGRFeatureH hFeature;
    OGRGeometryH hGeom;
    size_t nDataSize;
    unsigned char *pabyData = NULL;

    GIntBig nFeatures = OGR_L_GetFeatureCount(hLayer, 1);
    std::vector<GEOSGeometry*> vGeom(nFeatures);

    OGR_L_ResetReading(hLayer);
    unsigned int i = 0;
    while((hFeature = OGR_L_GetNextFeature(hLayer)) != NULL)
    {
        hGeom = OGR_F_GetGeometryRef(hFeature);
        if(hGeom == NULL)
        {
            throw std::range_error("GetGeometryRef failed.");
        }

        nDataSize = OGR_G_WkbSize(hGeom);
        pabyData = (unsigned char *) CPLMalloc(nDataSize);

        if(OGR_G_ExportToWkb(hGeom, wkbNDR, pabyData) == OGRERR_NONE)
        {
            GEOSWKBReader* wkbreader = GEOSWKBReader_create_r(geosCtxtH);
            vGeom[i] = GEOSWKBReader_read_r(geosCtxtH, wkbreader, pabyData, nDataSize);
            GEOSWKBReader_destroy_r(geosCtxtH, wkbreader);
        }
        else
        {
            throw std::range_error("Conversion of OGR to WKB went wrong");
        }

        // GetGeometryRef() returns a pointer to the internal geometry owned
        // by the OGRFeature. We do not need to delete the returned geometry.
        OGR_F_Destroy(hFeature);
        CPLFree(pabyData);
        i++;
    }
    GDALClose(hDS);

    OGRCleanupAll();
    OSRCleanup();

    return vGeom;
}


/* export polys
 *-----------------------------------------------------------------------------
 *
 * adapted from the OGR tutorial (https://gdal.org/tutorials/vector_api_tut.html)
 *
 * ToDo: check input: driver, dsn, layer must be given
 * ToDo: guess driver from file extension of dsn
 */
void
export_polys(GEOSContextHandle_t geosCtxtH,
             const std::vector<GEOSGeometry*> vGeom,
             const char *dsn,
             const char *layer,
             const char *driver,
             const OGRSpatialReferenceH hSRS)
{
    if(!layer)
        layer = CPLGetBasename(dsn);

    GDALAllRegister();

    // get driver ------------------------------------------------------------
    GDALDriverH hDriver;
    hDriver = GDALGetDriverByName(driver);
    if(hDriver == NULL)
    {
        Rcpp::Rcout << "'" << driver << "' driver not available." << std::endl;
        throw std::invalid_argument("Driver not available.\n");
    }

    // create output file -----------------------------------------------------
    GDALDatasetH hDS;

    // check if layer already exist -> delete layer to overwrite
    // inspired by ogr2ogr_lib.cpp
    hDS = GDALOpenEx(dsn, GDAL_OF_VECTOR | GDAL_OF_UPDATE, NULL, NULL, NULL);
    if(hDS != NULL)
    {
        // data set exists
        OGRLayerH poDstLayer = GDALDatasetGetLayerByName(hDS, layer);
        if(poDstLayer != NULL)
        {
            // layer exists: find index of layer and delete it
            int nLayerCount = GDALDatasetGetLayerCount(hDS);
            for(int iLayer = 0; iLayer < nLayerCount; iLayer++)
            {
                OGRLayerH poLayer = GDALDatasetGetLayer(hDS, iLayer);
                if(poLayer == poDstLayer)
                {
                    GDALDatasetDeleteLayer(hDS, iLayer);
                    break;
                }
            }
        }
    }

    // last argument: Dataset creation options (format specific)
    hDS = GDALCreate(hDriver, dsn, 0, 0, 0, GDT_Unknown, NULL);
    if(hDS == NULL)
    {
        Rcpp::Rcout << "Creation of dataset '" <<  dsn << "' failed." << std::endl;
        throw std::invalid_argument("Creation failed.");
    }

    // create layer -----------------------------------------------------------
    // last argument: Layer creation options (format specific)
    OGRLayerH hLayer;
    hLayer = GDALDatasetCreateLayer(hDS, layer, hSRS, wkbPolygon, NULL);
    if(hLayer == NULL)
    {
        GDALClose(hDS);
        throw std::invalid_argument("Layer creation failed.");
    }

    // convert features and write to file -------------------------------------
    for(unsigned int i = 0; i < vGeom.size(); i++)
    {
        // geos to wkb - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        size_t nSize = 0;
        unsigned char *pabyBuf = NULL;

        int nCoordDim = GEOSGeom_getCoordinateDimension_r(geosCtxtH, vGeom[i]);
        GEOSWKBWriter* wkbwriter = GEOSWKBWriter_create_r(geosCtxtH);
        GEOSWKBWriter_setOutputDimension_r(geosCtxtH, wkbwriter, nCoordDim);
        pabyBuf = GEOSWKBWriter_write_r(geosCtxtH, wkbwriter, vGeom[i], &nSize);
        GEOSWKBWriter_destroy_r(geosCtxtH, wkbwriter);

        if(pabyBuf == NULL || nSize == 0)
        {
            GDALClose(hDS);
            throw std::range_error("Reading GEOS geometry failed.");
        }

        // wkb to ogr - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        OGRGeometryH hOGRGeom;
        if(OGR_G_CreateFromWkb((unsigned char *) pabyBuf, hSRS, &hOGRGeom, (int) nSize)
            != OGRERR_NONE)
        {
            GDALClose(hDS);
            throw std::range_error("Creation of OGR geometry from wkb failed.");
        }

        // create  feature and write to file - - - - - - - - - - - - - - - - -
        OGRFeatureH hFeature;
        hFeature = OGR_F_Create(OGR_L_GetLayerDefn(hLayer));
        OGR_F_SetGeometryDirectly(hFeature, hOGRGeom);
        // ownership of hOGRGeom is passed on to hFeature. no need to destroy it

        if(OGR_L_CreateFeature(hLayer, hFeature) != OGRERR_NONE)
        {
            Rcpp::Rcout << "Failed to create feature " << i << " in " << layer << std::endl;
            GDALClose(hDS);
            throw std::invalid_argument("Feature creation failed.\n");
        }

        OGR_F_Destroy(hFeature);
        if(pabyBuf != NULL)
            GEOSFree_r(geosCtxtH, pabyBuf);
    }

    // It is required to close the dataset.
    // This does not only close the file handle, but also ensures that
    // all the data and metadata have been written to the dataset.
    GDALClose(hDS);

    OGRCleanupAll();
    OSRCleanup();
}





/* Geometries from WKB
 *-----------------------------------------------------------------------------
 *
 * adapted from sf's CPL_read_wkb & geometries_from_sfc and geos' geos_c_read_wkb
 * https://github.com/r-spatial/sf/blob/master/src/wkb.cpp
 * https://github.com/r-spatial/sf/blob/master/src/geos.cpp
 * https://github.com/paleolimbot/geos/blob/master/src/geos-io.c
 */
std::vector<GEOSGeometry*>
import_wkb(GEOSContextHandle_t geosCtxtH,
           const Rcpp::List wkb)
{
    GEOSGeometry* geom;
    std::vector<GEOSGeometry*> output(wkb.size());

    GEOSWKBReader *wkb_reader = GEOSWKBReader_create_r(geosCtxtH);

    for (int i = 0; i < wkb.size(); i++) {
        Rcpp::RawVector r = wkb[i];
        geom = GEOSWKBReader_read_r(geosCtxtH, wkb_reader, &(r[0]), r.size());

        // returns NULL on error
        if (geom == NULL) {
            GEOSWKBReader_destroy_r(geosCtxtH, wkb_reader);
            geos_finish(geosCtxtH);
            Rcpp::Rcout << "Could not convert to geos geometry because of broken geometry '"
                        <<  (i+1) << "' ." << std::endl;
            throw std::range_error("Conversion to geos geometry failed.");
        } else {
            output[i] = geom;
        }
    }

    GEOSWKBReader_destroy_r(geosCtxtH, wkb_reader);

    return output;
}



/* Write geometries to Rcpp::List of raws (WKB)
 *-----------------------------------------------------------------------------
 *
 * inspired by sf's CPL_write_wkb ond OGR's OGRGeometryFactory::createFromGEOS
 * https://github.com/r-spatial/sf/blob/master/src/wkb.cpp
 * https://github.com/OSGeo/gdal/blob/master/gdal/ogr/ogrgeometryfactory.cpp
 */

int native_endian(void) {
    const int one = 1;
    unsigned char *cp = (unsigned char *) &one;
    return (int) *cp;
}

Rcpp::List
export_wkb(GEOSContextHandle_t geosCtxtH,
           const std::vector<GEOSGeometry*> vGeom)
{
    Rcpp::List output(vGeom.size());
    int endian = native_endian();

    for (int i = 0; i < vGeom.size(); i++) {
        Rcpp::checkUserInterrupt();

        size_t nSize = 0;
        unsigned char *pabyBuf = NULL;

        GEOSWKBWriter *writer = GEOSWKBWriter_create_r(geosCtxtH);
        int nCoordDim = GEOSGeom_getCoordinateDimension_r(geosCtxtH, vGeom[i]);
        GEOSWKBWriter_setOutputDimension_r(geosCtxtH, writer, nCoordDim);
        GEOSWKBWriter_setByteOrder_r(geosCtxtH, writer, endian);
        // maybe set precision here
        pabyBuf = GEOSWKBWriter_write_r(geosCtxtH, writer, vGeom[i], &nSize);
        GEOSWKBWriter_destroy_r(geosCtxtH, writer);

        if(pabyBuf == NULL || nSize == 0){
            GEOSFree_r(geosCtxtH, pabyBuf);
            geos_finish(geosCtxtH);
            Rcpp::Rcout << "Could not convert to WKB at pos " <<  (i+1) << std::endl;
            throw std::range_error("Conversion to WKB failed.");
        }

        // shove it into R (unsigned char buffer to list of raw vectors)
        Rcpp::RawVector raw((int)nSize);
        for (size_t j = 0; j < (int)nSize; j++)
            raw[j] = pabyBuf[j];
        output[i] = raw; // raw vector to list
    }

    output.attr("class") = Rcpp::CharacterVector::create("WKB");
    return output;
}


/* geometries from sfc
 *-----------------------------------------------------------------------------
 *
 * adapted from sfr/src/geos.cpp @7621d66 (2017-01-31)
 * https://github.com/edzer/sfr/blob/7621d66fe881c8d238564deaa6ef7dd9675ae0e5/src/geos.cpp
 */
// std::vector<GEOSGeom>
// geometries_from_sfc(GEOSContextHandle_t geosCtxtH, Rcpp::List sfc)
// {
//     double precision = sfc.attr("precision");
//     Rcpp::List wkblst = CPL_write_wkb(sfc, false, native_endian(), "XY", precision);
//     std::vector<GEOSGeom> g(sfc.size());
//     for (int i = 0; i < sfc.size(); i++)
//     {
//         Rcpp::RawVector r = wkblst[i];
//         g[i] = GEOSGeomFromWKB_buf_r(geosCtxtH, &(r[0]), r.size());
//     }
//     return g;
// }


/* sfc from geometry
 *-----------------------------------------------------------------------------
 *
 * adapted from sfr/src/geos.cpp @7621d66 (2017-01-31)
 * https://github.com/edzer/sfr/blob/7621d66fe881c8d238564deaa6ef7dd9675ae0e5/src/geos.cpp
 *
 * destroys geometry in the process
 */
// Rcpp::List
// sfc_from_geometry(GEOSContextHandle_t geosCtxtH, std::vector<GEOSGeom> geom)
// {
//     Rcpp::List out(geom.size());
//     for (size_t i = 0; i < geom.size(); i++)
//     {
//         size_t size;
//         unsigned char *buf = GEOSGeomToWKB_buf_r(geosCtxtH, geom[i], &size);
//         Rcpp::RawVector raw(size);
//         memcpy(&(raw[0]), buf, size);
//         free(buf);
//         out[i] = raw;
//         GEOSGeom_destroy_r(geosCtxtH, geom[i]);
//     }
//     return CPL_read_wkb(out, false, native_endian());
// }
