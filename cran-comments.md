
This is a Re-submission of a package that was archived because email to maintainer bounced. A different email address is provided now.

I asked Simon Urbanek to set the configure argument "--with-data-copy=yes" for the macOS binary builds. I have not received an answer in the last 2 weeks, will politely ask again.




## Test environments
* Ubuntu 18.04, R 4.0.2, R devel [local]
* Ubuntu 14.04, libgeos-dev & libgdal-dev from ubuntugis-unstable [on Travis CI], 
  R 4.0.0 (2020-04-24), devel (2020-06-29 r78750)
* Debian testing, using docker container rocker/r-devel [on Drone CI],  
  R 4.0.2 (2020-06-22)
* Windows Server 2012 R2 x64, GDAL & GEOS from winlib/gdal2 [on AppVeyor CI],
  4.0.2 Patched (2020-06-24 r78747)
* win-builder, 4.0.2 (2020-06-22), R devel (2020-07-03 r78775), 3.6.3 (2020-02-29)


## R CMD check results
0 errors | 0 warnings | 2 notes

1) New submission

2) only on windows: 
* checking installed package size ... NOTE
  installed size is 73.8Mb
  sub-directories of 1Mb or more:
    gdal   3.9Mb
    libs  69.5Mb
      
The large install size is due to the required libraries GDAL & GEOS. apcf can not use the the R packages rgeos, rgdal, sf etc. because it links to GDAL & GEOS from its C++ code. All calculations are done in C++ for performance reasons. The package sf is even larger partly because of the additional library proj.
