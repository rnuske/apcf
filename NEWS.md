# apcf 0.3.0
* switched to R's random number generator in C++ code
* fixed CRANs M1mac vsnprintf() warning
* changed maintainer email address

# apcf 0.2.0
* removed dependence on GDAL. `pat2dists()` now takes geometries as `WKB` (using GEOS capabilities). This reduced configure code and package size significantly.
* added package 'wk' for checking WKBs and reading sfc-geometries if package 'sf' is available.
* fixed R version check in configure

# apcf 0.1.7
* updated message generation in configure.ac as requested by CRAN

# apcf 0.1.6
* Windows: update to GDAL 3.2.1 and fix for UCRT support  (thanks @jeroen)
* drop LazyData from description

# apcf 0.1.5
* cleaned up configure
* new maintainer email address due to problem with email provider

# apcf 0.1.4
* changed configure to cater to GDAL version 2 and 3 (thanks to package sf)

# apcf 0.1.3
* tweaked makevars.win in expectation of changes in win toolchain (thanks @jeroen)

# apcf 0.1.2
* added configure.ac to package source bundle
* clarified installation of stable/development version in README
* special treatment for R-devel in configure regarding R version check

# apcf 0.1.1
* started using continuous integration tools (Travis, AppVeyor, Drone)
* made it build on windows
* cleanup and wording

# apcf 0.1.0
* Intial version. Reimplementation of the Adapted Pair Correlation Function
  in C++ using GEOS and GDAL libraries directly instead of through PostGIS.
  Contains mainly the functions `pat2dists()`, `dists2pcf()`, and 
  a plot-function.
