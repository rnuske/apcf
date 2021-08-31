# convert shapefiles to WKB

library(sf)

# read  old shapfiles
area      <- st_read("data-raw/sim_area.shp")
pat_clust <- st_read("data-raw/sim_pat_clust.shp")
pat_rand  <- st_read("data-raw/sim_pat_rand.shp")
pat_reg   <- st_read("data-raw/sim_pat_reg.shp")


# turn geometry columns into wkb (round to nearest centimeter)
sim_area_wkb      <- st_as_binary(st_geometry(area), precision=100)
sim_pat_clust_wkb <- st_as_binary(st_geometry(pat_clust), precision=100)
sim_pat_rand_wkb  <- st_as_binary(st_geometry(pat_rand), precision=100)
sim_pat_reg_wkb   <- st_as_binary(st_geometry(pat_reg), precision=100)


# replace geometry with reduced precision geom
st_geometry(area) <- st_as_sfc(sim_area_wkb)
st_geometry(pat_clust) <- st_as_sfc(sim_pat_clust_wkb)
st_geometry(pat_rand) <- st_as_sfc(sim_pat_rand_wkb)
st_geometry(pat_reg) <- st_as_sfc(sim_pat_reg_wkb)

# the old shapefiles have funny definition of UTM32, using 25832 now
st_crs(area) <- st_crs('epsg:25832')
st_crs(pat_clust) <- st_crs('epsg:25832')
st_crs(pat_rand) <- st_crs('epsg:25832')
st_crs(pat_reg) <- st_crs('epsg:25832')


# write new shapefiles with reduced precision
st_write(area, "inst/shapes/sim_area.shp", driver="ESRI Shapefile", delete_layer=TRUE)
st_write(pat_clust, "inst/shapes/sim_pat_clust.shp", driver="ESRI Shapefile", delete_layer=TRUE)
st_write(pat_rand, "inst/shapes/sim_pat_rand.shp", driver="ESRI Shapefile", delete_layer=TRUE)
st_write(pat_reg, "inst/shapes/sim_pat_reg.shp", driver="ESRI Shapefile", delete_layer=TRUE)



# WKB -> package data
usethis::use_data(sim_area_wkb, sim_pat_clust_wkb, sim_pat_rand_wkb, sim_pat_reg_wkb,
                  internal=FALSE, compress="bzip2", version=2, overwrite=TRUE)



# Object of class WKB
# list of raw vectors
# every element holds one geometry
print(pat_clust_wkb)
str(pat_clust_wkb)
class(pat_clust_wkb)




#==============================================================================
# Test if everything is kosher
#==============================================================================

# read  new shapfiles
area      <- st_read("inst/shapes/sim_area.shp")
pat_clust <- st_read("inst/shapes/sim_pat_clust.shp")
pat_rand  <- st_read("inst/shapes/sim_pat_rand.shp")
pat_reg   <- st_read("inst/shapes/sim_pat_reg.shp")

# read  old shapfiles
area.o      <- st_read("data-raw/sim_area.shp")
pat_clust.o <- st_read("data-raw/sim_pat_clust.shp")
pat_rand.o  <- st_read("data-raw/sim_pat_rand.shp")
pat_reg.o   <- st_read("data-raw/sim_pat_reg.shp")


op <- par(mar=c(0,0,0,0))

# do the shapefiles contain what they are supposed to contain
plot(st_geometry(area))
plot(st_geometry(pat_clust), add=T)
plot(st_geometry(pat_rand), border='darkblue', add=T)
plot(st_geometry(pat_reg), border='darkgreen', add=T)
# => alright!

# how much do old and new (reduced precision) differ
plot(st_geometry(area))
plot(st_geometry(area.o), border='red', lty='dashed', add=T)

plot(st_geometry(pat_clust))
plot(st_geometry(pat_clust.o), border='red', lty='dashed', add=T)

plot(st_geometry(pat_rand))
plot(st_geometry(pat_rand.o), border='red', lty='dashed', add=T)

plot(st_geometry(pat_reg))
plot(st_geometry(pat_reg.o), border='red', lty='dashed', add=T)
# => no visible differences

par(op)


# I did also compare results of apcf calculations with geometries of different
# precision (centimeter, millimeter, micrometer).
# There were very tiny differences between shapfile and WKB in the empirical
# pcf  which do not change the interpretation of the pcf.
# The differences were in the same range for centimeter, millimeter and
# micrometer resolution.
# I think  differences are rather due to different kind of conversion
# to digital numbers in shapefile and WKB.
