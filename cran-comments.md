
This submission contains an update of the configure file to enable the package to compile with the library GDAL version 2 and 3 fixing errors on r-release-linux-x86_64, r-patched-linux-x86_64,  r-devel-linux-x86_64-debian-clang, r-devel-linux-x86_64-debian-gcc.


## Test environments
* Ubuntu 18.04, R 3.6.0, R devel [local]
* Ubuntu 14.04, libgeos-dev & libgdal-dev from ubuntugis-unstable [on Travis CI], 
  R 3.6.2 (2017-01-27), devel (2020-02-04 r77771)
* Debian Stretch, GDAL & GEOS via docker image rocker/geospatial [on Drone CI],  
  R 3.6.2, devel (2020-01-28 r77738)
* Windows Server 2012 R2 x64, GDAL & GEOS from winlib/gdal2 [on AppVeyor CI],
  R 3.6.2 Patched (2020-01-25 r77764)
* win-builder, R 3.6.2, R devel (2020-01-27 r77730)


## R CMD check results
0 errors | 0 warnings | 1 notes

* only on windows: 
  * checking installed package size ... NOTE
    installed size is 73.7Mb
    sub-directories of 1Mb or more:
      gdal   3.9Mb
      libs  69.4Mb
      
    - The large install size is due to the required libraries GDAL & GEOS.
      apcf can not use the the R packages rgeos, rgdal, sf etc. 
      because it links to GDAL & GEOS from its C++ code. 
      All calculations are done in C++ for performance reasons.
      The package sf is even larger partly because of the additional library proj.
