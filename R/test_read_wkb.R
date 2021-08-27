
#' Test WKB Reading
#'
#' @param wkb a list of wkb
#'
#' @return nothing but the C++ function prints the WKT of the geometry to stdout
#'
#' @export
#'
#' @examples
#' test_reading_wkb(sim_area_wkb)
#' test_reading_wkb(sim_pat_reg_wkb)
#'
test_reading_wkb <- function(wkb){
  test_read_wkb(wkb)
}


#' Test old Reading
#'
#' @param dsn name of a data source
#'
#' @return nothing but the C++ function prints the WKT of the geometry to stdout
#'
#' @export
#'
#' @examples
#' test_reading_polys(system.file("shapes/sim_area.shp", package="apcf"))
#' test_reading_polys(system.file("shapes/sim_pat_reg.shp", package="apcf"))
#'
test_reading_polys <- function(dsn){
  test_read_polys(dsn[1])
}
