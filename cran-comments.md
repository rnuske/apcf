
This is a minor update. Mainly due to an upgrade to the latest version of GDAL on Windows, and also prepares for upcoming UCRT toolchains.


## Test environments
* local Ubuntu 20.04, R 4.1.0

* win-builder
  * R Under development (unstable) (2021-07-25 r80663)
  * R version 4.1.0 (2021-05-18)
  * R version 4.0.5 (2021-03-31)

* R-hub
  * Windows Server 2008 R2 SP1, R-devel, 32/64 bit
  * Ubuntu Linux 20.04.1 LTS, R-release, GCC
  * Fedora Linux, R-devel, clang, gfortran
  * Debian Linux, R-devel, GCC ASAN/UBSAN
  
* Continuous Integration Systems
  * Drone CI: Debian testing, R 4.1.0 (2021-05-18)
  * AppVeyor: Windows Server 2012 R2 x64, R 4.1.0 Patched (2021-07-20 r80665)
  * TravisCI: Ubuntu 18.04, R 4.0.2 (2020-06-22) & R devel (2021-07-26 r80665)
 

## R CMD check results
0 errors | 0 warnings | 1 note

only on windows: 
* checking installed package size ... NOTE
  installed size is 92.1Mb
  sub-directories of 1Mb or more:
    gdal   2.2Mb
    libs  89.5Mb
      
The large install size is due to the required libraries GDAL & GEOS. This package can not use the the R packages rgeos, rgdal, sf etc. because it links to GDAL & GEOS from its C++ code. All calculations are done in C++ for performance reasons. It is comparable to package sf.
