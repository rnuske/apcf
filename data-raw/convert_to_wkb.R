# convert shapefiles to WKB

library(sf)

# read shapfiles
area      <- st_read("inst/shapes/sim_area.shp")
pat_clust <- st_read("inst/shapes/sim_pat_clust.shp")
pat_rand  <- st_read("inst/shapes/sim_pat_rand.shp")
pat_reg   <- st_read("inst/shapes/sim_pat_reg.shp")


# turn geometry columns into wkb
sim_area_wkb      <- st_as_binary(st_geometry(area), precision=10)
sim_pat_clust_wkb <- st_as_binary(st_geometry(pat_clust), precision=10)
sim_pat_rand_wkb  <- st_as_binary(st_geometry(pat_rand), precision=10)
sim_pat_reg_wkb   <- st_as_binary(st_geometry(pat_reg), precision=10)


# Object of class WKB
# list of raw vectors
# every element holds one geometry
print(pat_clust_wkb)
str(pat_clust_wkb)
class(pat_clust_wkb)


# create package data
usethis::use_data(sim_area_wkb, sim_pat_clust_wkb, sim_pat_rand_wkb, sim_pat_reg_wkb,
                  internal=FALSE, compress="bzip2", version=2, overwrite=TRUE)
