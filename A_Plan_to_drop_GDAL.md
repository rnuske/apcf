# Have a Plan

## **Goal:** Drop dependency on GDAL library

The GDAL library is a very heavy dependency but it is currently totally underutilized only turning shapefiles into geos geometries.

GEOS itself is capable of reading WKB. So apcf could read WKB without depending on any other library. This is very good minimum import feature.

Since most polygonal input data will come in many different other formats (shapefiles, geopackages, geojson, GML, flatgeobuf, PostGIS EWKT, ... ) it would be good to have an intermediary such as sf. The sf package has become the go to place for spatial data handling. It's the foundation for most if not all new spatial packages and is very good at interfacing with GDAL using its full potential.

apcf should take WKB and sf polygons, turn them into geos geometries and return my apcf objects and maybe sf objects for visualization. It would be great not to depend on sf but only to suggest it, since sf is also a very big animal.


## Plan

For now I think I will not pass geos geometries back to R. 

This would require passing external pointers back and forth, which seems not so easy. The memory the pointer points to must be freed when the R object goes out of scope. The GEOSGeometry needs some special handling with its context and stuff. the geos package has -maybe because of that- some funny globale_context object. I do not entirely grok the init and finish business in the geos package.

sf does not take external pointer into R since it holds the geometries in R objects.

I think the calling R Function pat2dists must figure out which class of geometries it has to deal with and handle it / call the appropriate C++-Function. Reading and working with geometries happens then completely within C++.


### Make it work with WKB
  * create wkb versions of example data
  * adapt wkb reading code from package sf (C and R code)
  * thoroughly test it
  
  * rip out the GDAL stuff
    * C++ Code: src/import_export.cpp, src/RcppExports.cpp, src/import_export.h
    * R functions, help pages: R/RcppExports.R, R/pat2dists.R, R/apcf-package.R
    * R helper functions: R/init.R
    * config files, src/Makewars.win, src/Makevars.ucrt, tools/winlibs.R
    * DESCRIPTION
    * README, vignette
  
#### Notes
* borrowing Code from package geos did not work as expected the design is to different.

*  I don't want to depend on geos because it depends on libgeos. That way I would have the geos library twice: 
  * a) through my code depending on geos library in its usual place (system dependency) 
  * b) libgeos brings complete geos library in via the libgeos package


### Make it work with sf objects
  * adapt sf reading code from package sfheaders and geos
  * test it thoroughly
  
#### Notes
  * It would be great not to depend on sf but only to suggest it, since sf is also a very big animal. Look at geos it managed to do so.
