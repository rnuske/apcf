#' Convert a Pattern to Distances & Ratios
#'
#' Creates `n_sim` null models by permutation of the original pattern and
#' calculates distances between all object of a pattern closer than `max_dist`
#' and determines the fractions of the perimeter of buffers with distance
#' `dist` inside the study area (needed for edge correction).
#'
#' Null models are created by randomly rotating and randomly placing all
#' objects within the study area without overlap. They are used for correcting
#' the biased pcf and constructing a pointwise critical envelope (cf. Nuske
#' et al. 2009).
#'
#' Measuring distances between objects and permutation of the pattern is done
#' using [GEOS](https://libgeos.org).
#'
#' @param area,pattern Geodata (polygons) of study area and pattern in the
#'   formats `WKB` (well known binary, list of raw vectors), `WKT` (well known
#'   text) or `sf`-objects if package `sf` is available. Via sf all file formats
#'   supported by GDAL/OGR are possible.
#' @param max_dist Maximum distance measured in the pattern. Usually smaller
#'   than half the diameter of the study area.
#' @param n_sim Number of simulated patterns (randomizations) to be generated
#'   for computing the envelope and correcting the biased empirical pcf.
#'   Determines together with `n_rank` in [dists2pcf()] the alpha level of the
#'   envelope. If `alpha` and `n_rank` are fix, n_sim can be calculated by
#'   `(n_rank*2/alpha)-1` for instance `(5*2/0.05)-1 = 199`.
#' @param max_tries How often shall a relocation of an object be tried while
#'   randomizing the pattern.
#' @param save_pattern Shall one simulated pattern be returned in the attributes
#'   for debugging/later inspections. The pattern is provided as  WKB (list of
#'   raw vectors) in the attribute `randPattern`.
#' @param verbose Provide progress information in the console. Roman numerals
#'   (x: 10, C: 100, D: 500, M: 1000) indicate the progress of the simulation
#'   and 'e' denotes the empirical PCF.
#'
#' @return An object of class [dists]. If `save_pattern = TRUE` an additional
#'   attribute `randPattern` is returned containing a WKB (list of raw vectors).
#'
#' @references
#' Nuske, R.S., Sprauer, S. and Saborowski, J. (2009): Adapting the
#' pair-correlation function for analysing the spatial distribution of canopy
#' gaps. Forest Ecology and Management, 259(1): 107–116.
#' https://doi.org/10.1016/j.foreco.2009.09.050
#'
#' @seealso [dists2pcf()], [plot.fv_pcf()]
#'
#' @examples
#' # it's advised against setting n_sim < 199
#' ds <- pat2dists(area=sim_area, pattern=sim_pat_reg, max_dist=25, n_sim=3)
#'
#' # verbose and returns one randomized pattern for debugging
#' ds_plus <- pat2dists(area=sim_area, pattern=sim_pat_reg, max_dist=5, n_sim=3,
#'                      verbose=TRUE, save_pattern=TRUE)
#'
#' \dontrun{
#'   # wk's plot function needs additional package 'vctrs'
#'   plot(attr(ds_plus, "randPattern"))
#' }
#' @export

pat2dists <- function(area, pattern, max_dist, n_sim=199, max_tries=100000,
                      save_pattern=FALSE, verbose=FALSE){

  if(missing(max_dist) || !is.numeric(max_dist))
    stop("max_dist must be given and must be numeric")

  if(length(area) > 1 )
    warning("using only the first element of area")

  # expect area and pattern to be lists of WKB objects or sth convertible to WKB
  # check if it's a valid WKB and basic check of geometry type
  area <- wk::validate_wk_wkb(wk::as_wkb(area))[[1]]
  if(!wk::wk_meta(area)["geometry_type"] %in% c(3, 6))
    stop("area must be polygon or multipolygon")

  pattern <- wk::validate_wk_wkb(wk::as_wkb(pattern))
  if(!all(wk::wk_meta(pattern)["geometry_type"] == 3))
    stop("pattern must be all polygons")


  rand_dists_ratios_wkb(pattern, area, max_dist, as.integer(n_sim),
                        as.integer(max_tries), save_pattern, verbose)
}
