# Changelog

## apcf 0.3.3

CRAN release: 2025-12-21

- updated Makevars for newer R on windows builds
- removed CXX from Makevars to fix warnings from newer compilers
  (e.g. gcc 15, clang 21)

## apcf 0.3.2

CRAN release: 2025-02-28

- fixed bashism in configure.ac

## apcf 0.3.1

CRAN release: 2024-06-13

- dropped C++11 as a system requirement
- fixed Wsign-compare warning in import_export.cpp
- converted citEntry to bibentry in inst/CITATION and added CITATION.cff

## apcf 0.3.0

CRAN release: 2022-11-12

- switched to R’s random number generator in C++ code
- fixed CRANs M1mac vsnprintf() warning
- changed maintainer email address

## apcf 0.2.0

CRAN release: 2022-03-30

- removed dependence on GDAL.
  [`pat2dists()`](https://rnuske.github.io/apcf/reference/pat2dists.md)
  now takes geometries as `WKB` (using GEOS capabilities). This reduced
  configure code and package size significantly.
- added package ‘wk’ for checking WKBs and reading sfc-geometries if
  package ‘sf’ is available.
- fixed R version check in configure

## apcf 0.1.7

CRAN release: 2021-10-27

- updated message generation in configure.ac as requested by CRAN

## apcf 0.1.6

CRAN release: 2021-07-27

- Windows: update to GDAL 3.2.1 and fix for UCRT support (thanks
  [@jeroen](https://github.com/jeroen))
- drop LazyData from description

## apcf 0.1.5

CRAN release: 2020-07-05

- cleaned up configure
- new maintainer email address due to problem with email provider

## apcf 0.1.4

CRAN release: 2020-02-04

- changed configure to cater to GDAL version 2 and 3 (thanks to package
  sf)

## apcf 0.1.3

CRAN release: 2019-06-13

- tweaked makevars.win in expectation of changes in win toolchain
  (thanks [@jeroen](https://github.com/jeroen))

## apcf 0.1.2

CRAN release: 2019-01-17

- added configure.ac to package source bundle
- clarified installation of stable/development version in README
- special treatment for R-devel in configure regarding R version check

## apcf 0.1.1

CRAN release: 2019-01-11

- started using continuous integration tools (Travis, AppVeyor, Drone)
- made it build on windows
- cleanup and wording

## apcf 0.1.0

- Intial version. Reimplementation of the Adapted Pair Correlation
  Function in C++ using GEOS and GDAL libraries directly instead of
  through PostGIS. Contains mainly the functions
  [`pat2dists()`](https://rnuske.github.io/apcf/reference/pat2dists.md),
  [`dists2pcf()`](https://rnuske.github.io/apcf/reference/dists2pcf.md),
  and a plot-function.
