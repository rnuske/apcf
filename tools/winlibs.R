# inherited from sf (https://github.com/r-spatial/sf)

if(getRversion() < "3.3.0") {
  stop("Your version of R is too old. This package requires R-3.3.0 or newer on Windows.")
}

# For details see: https://github.com/rwinlib/geos
VERSION <- commandArgs(TRUE)
if(!file.exists(sprintf("../windows/geos-%s/include/geos_c.h", VERSION))){
  download.file(sprintf("https://github.com/rwinlib/geos/archive/v%s.zip", VERSION), "lib.zip", quiet = TRUE)
  dir.create("../windows", showWarnings = FALSE)
  unzip("lib.zip", exdir = "../windows")
  unlink("lib.zip")
}
