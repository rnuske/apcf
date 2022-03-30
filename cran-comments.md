This submission fixes a bug that appeared on CRAN as requested by Kurt Hornik. 
It also contains a major overhaul of the dependencies. GDAL is no longer needed, reducing the size of the binary package considerably.

The error on CRAN was due to CXX11 not being found on systems that identified themselves as 4.3 because of a weak R version check in my configure file. This is now fixed. I checked the fix on Rhub platforms on which I previously reproduced the error.


## Test environments
* local Ubuntu 20.04, R 4.1.3

* win-builder
  * R version 4.0.5 (2021-03-31)
  * R version 4.1.3 (2022-03-10)
  * R version 4.2.0 alpha (2022-03-27 r81997 ucrt)
  
* mac-builder
  * r-release-macosx-arm64|4.1.1|macosx|macOS 11.5.2 (20G95)|Mac mini|Apple M1||en_US.UTF-8 

* R-hub
  * Ubuntu Linux 20.04.1 LTS, R-release, GCC
  * Debian Linux, R-devel, GCC ASAN/UBSAN
  * Fedora Linux, R-devel, clang, gfortran
  * Windows Server 2022, R-devel, 64 bit
  
* Continuous Integration Systems
  * Drone: Debian testing, R version 4.1.3 (2022-03-10)
  
  * Github Actions
    * ubuntu-20.04, R version 4.0.5 (2021-03-31)
    * ubuntu-20.04, R version 4.1.3 (2022-03-10)
    * ubuntu-20.04, R Under development (unstable) (2022-03-27 r81995)
    * Windows Server 2022, R version 3.6.3 (2020-02-29)
    * Windows Server 2022, R version 4.1.3 (2022-03-10)
    * Windows Server 2022, R Under development (unstable) (2022-03-27 r81997 ucrt)
    * macOS Big Sur 11, R version 4.1.3 (2022-03-10)
    

## R CMD check results
0 errors | 0 warnings | 1 note

only on macOS the following note:
* checking installed package size ... NOTE
  installed size is 36.9Mb
  sub-directories of 1Mb or more:
    libs  36.4Mb

and on some linux systems:
* checking installed package size ... NOTE
  installed size is  5.3Mb
  sub-directories of 1Mb or more:
    libs   4.5Mb
      
The large install size is due to the required library GEOS. The size of the binary package decreased already considerably since the dependency on GDAL was dropped. This package can not use the the R packages rgeos, rgdal, sf etc. because it links to GEOS from its C++ code. All calculations are done in C++ for performance reasons, comparable to package sf.
