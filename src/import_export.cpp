/*===========================================================================*\
 *                        Reading and writing Geodata
 *
 * - import_wkb:    WKB (R list of raw vectors) -> GEOS
 * - export_wkb:    GEOS ->  WKB (R list of raw vectors)
\*===========================================================================*/

#include <Rcpp.h>        // Rcpp
#include <vector>        // vector
#include <geos_c.h>      // GEOS* functions
//#include <cpl_conv.h>    // CPLFree

#include "import_export.h"
#include "geos_stuff.h"


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

    output.attr("class") = Rcpp::CharacterVector::create("wk_wkb", "wk_vctr", "WKB");
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
