/*===========================================================================*\
 *                   Reading and writing WKB via GEOS
 *
\*===========================================================================*/

#ifndef IMPORT_EXPORT_INCLUDED
#define IMPORT_EXPORT_INCLUDED

#include <vector>        // vector
#include <geos_c.h>      // GEOS functions


/* import WKB geometries via GEOS
 *
 * wkb: An R list of raw vectors (WKB)
 *
 * Returns a vector of GEOSGeometries
 *
 * throws exceptions
 */
std::vector<GEOSGeometry*>
import_wkb(GEOSContextHandle_t geosCtxtH,
           Rcpp::List wkb);


/* Export WKB geometries to R as list of raw vectors
 *
 * vGeom: vector of GeosGeometries
 *
 * Returns an Rcpp::List of raw vectors. Each raw vector holds one WKB geometry.
 *
 * throws exceptions
 */
Rcpp::List
export_wkb(GEOSContextHandle_t geosCtxtH,
           const std::vector<GEOSGeometry*> vGeom);


/* import from R's SimpleFeature (package:sf)
 *
 * sfc: a simple feature collection. most generic simple feature type
 *
 * Returns a vector of GEOSGeometries
 *
 * throws exceptions ???
 */
// std::vector<GEOSGeom>
// geometries_from_sfc(GEOSContextHandle_t geosCtxtH,
//                     Rcpp::List sfc);



/* export to R's SimpleFeature (package:sf)
 *
 * geom: vector of GEOSGeometries
 *
 * Returns a Simple Feature Collection. disguised as a plain List
 *
 * throws exceptions ???
 */
// Rcpp::List
// sfc_from_geometry(GEOSContextHandle_t geosCtxtH,
//                   std::vector<GEOSGeom> geom);

#endif // IMPORT_EXPORT_INCLUDED
