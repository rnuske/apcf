
This submission contains a minor update requested by Jeroen Ooms because of changes in the windows toolchain.

## Test environments
* Ubuntu 18.04, R 3.6.0 [local]
* Ubuntu 14.04, libgeos-dev & libgdal-dev from ubuntugis-unstable [on Travis CI], 
  R 3.5.3, 3.6.0, devel (2019-06-11 r76693)
* Debian Stretch, GDAL & GEOS via docker image rocker/geospatial [on Drone CI],  
  R 3.5.3, 3.6.0, devel (2019-06-08 r76690) 
* Windows Server 2012 R2 x64, GDAL & GEOS from winlib/gdal2 [on AppVeyor CI],
  R 3.6.0 Patched (2019-06-07 r76691)
* win-builder, R old-release, release


## R CMD check results
0 errors | 0 warnings | 2 notes

* Possibly mis-spelled words in DESCRIPTION:
  * Nuske is the name of the author of the cited paper
  * et and al. are commonly used words/abbreviations 
  * The word 'reimplementation' seems to be quite common in software development. 
    According to wiktionary it describes the act of 'implementing sth. again'.
  
* only on windows: 
  * package size note
    installed size is 73.1Mb
    sub-directories of 1Mb or more:
      gdal   3.9Mb
      libs  68.8Mb
      
    - The large install size is due to the required libraries GDAL & GEOS.
      apcf can not use the the R packages rgeos, rgdal, sf etc. 
      because it links to GDAL & GEOS from its C++ code. 
      All calculations are done in C++ for performance reasons.
      The package sf is even larger partly because of the additional library proj.
