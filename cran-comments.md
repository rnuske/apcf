This is a patch release fixing the CRAN warning "Unknown C++ standard ‘CXX’" for newer compilers and the note "Found '_ZSt4cerr', possibly from 'std::cerr' (C++)" in an older version of the employed library GEOS for r-release and r-devel under windows.

We have checked the package locally with r-release and r-devel, using Rhub on newer compilers with r-release and r-devel under ubuntu, windows and macos, and using the CRAN win builder service. We found no errors, warnings or notes.

The large install size on some OS is due to the required library GEOS. This package links to GEOS from its C++ code, comparable to package sf.

Many thanks for your service 
