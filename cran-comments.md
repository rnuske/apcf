This is a minor update that also fixes the C++11 note.

We have checked the package on local Windows and Linux systems with released R versions, Winbuilder, and across a range of operating systems, compilers, and R versions using Rhub. No errors, no warnings, and no notes were found. 

The large install size on some OS is due to the required library GEOS. This package can not use the R packages rgeos, rgdal, sf etc. because it links to GEOS from its C++ code. All calculations are done in C++ for performance reasons, comparable to package sf.

Many thanks for your service 
