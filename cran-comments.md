
This is a re-submission.
The package was archived by Prof. Brian Ripley for policy violations.

## Changes
* configure.ac is now part of the source bundle
* clarified installation of stable/development version of the package in README
* special treatment for R-devel in configure regarding R version check


## Test environments
* Ubuntu 18.04, R 3.5.2, R-devel (2019-01-14 r75992) [local]
* Ubuntu 14.04, libgeos-dev & libgdal-dev from ubuntugis-unstable [on Travis CI], 
  R 3.4.4, 3.5.2, devel
* Debian Stretch, GDAL & GEOS via docker image rocker/geospatial [on Drone.io CI],  
  R 3.4.4, 3.5.1, devel
* Windows Server 2012 R2 x64, GDAL & GEOS from winlib/gdal2 [on AppVeyor CI],
  R 3.5.2 Patched
* win-builder, R release, devel


## R CMD check results
0 errors | 0 warnings | 2+1 notes

* Package was archived on CRAN
  Archived on 2019-01-16 for policy violation.
  * Changes to fix the policy violations are addressed above

* Possibly mis-spelled words in DESCRIPTION:
  * Nuske is the name of the author of the cited paper
  * et and al. are commonly used words/abbreviations 
  * The word 'reimplementation' seems to be quite common in software development. 
    According to wiktionary it describes the act of implementing again.
  
* only on windows: 
  * package size note
    installed size is 73.1Mb
    sub-directories of 1Mb or more:
      gdal   3.9Mb
      libs  68.8Mb
      
    - The large install size is due to the required libraries GDAL & GEOS. 
      The package sf is even larger partly because of the additional library proj.
