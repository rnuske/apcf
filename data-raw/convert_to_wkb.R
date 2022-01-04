# convert shapefiles to WKB of class wk_wkb
# The data are simulated in a Cartesian coordinate system with unit meter (no .prj)


library(sf)
library(wk)

# read shapfiles (millimeter precision)
area      <- st_read("data-raw/sim_area.shp")
pat_clust <- st_read("data-raw/sim_pat_clust.shp")
pat_rand  <- st_read("data-raw/sim_pat_rand.shp")
pat_reg   <- st_read("data-raw/sim_pat_reg.shp")


# convert sfc to wk_wkb
sim_area      <- as_wkb(area)
sim_pat_clust <- as_wkb(pat_clust)
sim_pat_rand  <- as_wkb(pat_rand)
sim_pat_reg   <- as_wkb(pat_reg)


# drop information about undefined CRS
wk_crs(sim_area)      <- NULL
wk_crs(sim_pat_clust) <- NULL
wk_crs(sim_pat_rand)  <- NULL
wk_crs(sim_pat_reg)   <- NULL


# WKB -> package data
usethis::use_data(sim_area, sim_pat_clust, sim_pat_rand, sim_pat_reg,
                  internal=FALSE, compress="bzip2", version=2, overwrite=TRUE)




# I did also compare results of apcf calculations with geometries of different
# precision (centimeter, millimeter, micrometer).
# There were very tiny differences between shapfile and WKB in the empirical
# pcf  which do not change the interpretation of the pcf.
# The differences were in the same range for centimeter, millimeter and
# micrometer resolution.
# I think  differences are rather due to different kind of conversion
# to digital numbers in shapefile and WKB.
