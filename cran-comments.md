This is a minor update that also fixes the M1mac warning reported under "Additional issues".

The maintainer stays the same, but the email address changed.

This package checks okay locally on ubuntu 20.04 R-release, all win-builder flavors, macOS builder, Rhub's check_for_cran suite and Github Actions CI.

The large install size on some OS is due to the required library GEOS. This package can not use the R packages rgeos, rgdal, sf etc. because it links to GEOS from its C++ code. All calculations are done in C++ for performance reasons, comparable to package sf.
