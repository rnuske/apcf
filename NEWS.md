# News for Package 'apcf'

## Changes in version 0.1.3
* Makevars.win tweaked in expectation of change of win toolchain (thanks @jeroen)

## Changes in version 0.1.2
* added configure.ac to package source bundle
* clarified installation of stable/development version in README
* special treatment for R-devel in configure regarding R version check

## Changes in version 0.1.1
* started using continuous integration tools (Travis, AppVeyor, Drone)
* made it build on windows
* cleanup and wording

## Changes in version 0.1.0
* Intial version. Reimplementation of the Adapted Pair Correlation Function
  in C++ using GEOS and GDAL libraries directly instead of through PostGIS.
  Contains mainly the functions `pat2dists()`, `dists2pcf()`, and 
  a plot-function.
