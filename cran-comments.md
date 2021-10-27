
This is a minor update changing the way messages are generated (obsolete 'AC_HELP_STRING' constructs) in configure.ac as requested by CRAN. This submission fixes the autoreconf warnings.


## Test environments
* local Ubuntu 20.04, R 4.1.1

* win-builder
  * R Under development (unstable) (2021-10-25 r81104)
  * R version 4.1.1 (2021-08-10)
  * R version 4.0.5 (2021-03-31)
  
* mac-builder
  * r-release-macosx-arm64|4.1.1|macosx|macOS 11.5.2 (20G95)|Mac mini|Apple M1|

* R-hub
  * Windows Server 2008 R2 SP1, R-devel, 32/64 bit
  * Ubuntu Linux 20.04.1 LTS, R-release, GCC
  * Fedora Linux, R-devel, clang, gfortran
  
* Continuous Integration Systems
  * Drone CI: Debian testing, R 4.1.1 (2021-08-10)
  

## R CMD check results
0 errors | 0 warnings | 1 note

only on windows and MacOS something like:
* checking installed package size ... NOTE
  installed size is 92.1Mb
  sub-directories of 1Mb or more:
    gdal   2.2Mb
    libs  89.5Mb
      
The large install size is due to the currently required libraries GDAL & GEOS. This package can not use the the R packages rgeos, rgdal, sf etc. because it links to GDAL & GEOS from its C++ code. All calculations are done in C++ for performance reasons, comparable to package sf.
