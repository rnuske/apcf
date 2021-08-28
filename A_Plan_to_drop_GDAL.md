# Have a Plan

## **Goal:** Drop dependency on GDAL library

The GDAL library is a very heavy dependency but it is currently totally underutilized only turning shapefiles into geos geometries.

GEOS itself is capable of reading WKB. So apcf could read WKB without depending on any other library. This is very good minimum import feature.

Since most polygonal input data will come in many different other formats (shapefiles, geopackages, geojson, GML, flatgeobuf, PostGIS EWKT, ... ) it would be good to have an intermediary such as sf. The sf package has become the go to place for spatial data handling. It's the foundation for most if not all new spatial packages and is very good at interfacing with GDAL using its full potential.

apcf should take WKB and sf polygons, turn them into geos geometries and return my apcf objects and maybe sf objects for visualization. It would be great not to depend on sf but only to suggest it, since sf is also a very big animal.


## Plan

For now I think I will not pass geos geometries back to R. 

This would require passing external pointers back and forth, which seems not so easy. The memory the pointer points to must be freed when the R object goes out of scope. The GEOSGeometry needs some special handling with its context and stuff. the geos package has -maybe because of that- some funny globale_context object. I do not entirely grok the init and finish business in the geos package.

- [@paleolimbot]: I used to create a context at the start and end of every method, but instead, the lifecycle of the context is at package load and unload. This made it easier to write the ten million GEOS functions because I never had to worry that the context object wouldn't get released. The important part about the context object is to save the last error message so you can report it when you get a NULL back from GEOS.

sf does not take external pointer into R since it holds the geometries in R objects.

I think the calling R Function pat2dists must figure out which class of geometries it has to deal with and handle it / call the appropriate C++-Function. Reading and working with geometries happens then completely within C++.

- [@paleolimbot]: `wk::wk_meta()` and `wk::wk_vector_meta()` might be able to help (i.e., reduce the compiled code that you have to write) you with this...`wk::wk_vector_meta()` is lazy (e.g., it never does a full scan of the object if the object reports the bbox/geometry type up front) and you can fall back on `wk::wk_meta()` and/or `wk::wk_bbox()` to calculate. These work with sf, geos, and wkb among others.

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

- [@paleolimbot]: You can depend on libgeos, too, for the C API in the same way that geos does it (i.e., one copy of GEOS in libgeos so you don't need any system requirements). The only part of your code that *should* need to change is the header name (libgeos.h) + you'll need to find a way to call `libgeos_init_api()` on package load. It's safe to work with `geos::geos_geometry()` objects (list of externalptr) because they, too are created by libgeos (one DLL always generating the pointers). Totally not offended if you use or don't use libgeos/geos, but if you did use them you get to drop the configure script and all your IO (because the geos package has converters to/from sf that you get for free).


### Make it work with sf objects

  * adapt sf reading code from package sfheaders and geos
  * test it thoroughly
  
#### Notes
  * It would be great not to depend on sf but only to suggest it, since sf is also a very big animal. Look at geos it managed to do so.
