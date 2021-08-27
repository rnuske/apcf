
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
