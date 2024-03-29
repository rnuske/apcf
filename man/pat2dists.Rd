% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/pat2dists.R
\name{pat2dists}
\alias{pat2dists}
\title{Convert a Pattern to Distances & Ratios}
\usage{
pat2dists(
  area,
  pattern,
  max_dist,
  n_sim = 199,
  max_tries = 1e+05,
  save_pattern = FALSE,
  verbose = FALSE
)
}
\arguments{
\item{area, pattern}{Geodata (polygons) of study area and pattern in the
formats \code{WKB} (well known binary, list of raw vectors), \code{WKT} (well known
text) or \code{sf}-objects if package \code{sf} is available. Via sf all file formats
supported by GDAL/OGR are possible.}

\item{max_dist}{Maximum distance measured in the pattern. Usually smaller
than half the diameter of the study area.}

\item{n_sim}{Number of simulated patterns (randomizations) to be generated
for computing the envelope and correcting the biased empirical pcf.
Determines together with \code{n_rank} in \code{\link[=dists2pcf]{dists2pcf()}} the alpha level of the
envelope. If \code{alpha} and \code{n_rank} are fix, n_sim can be calculated by
\code{(n_rank*2/alpha)-1} for instance \code{(5*2/0.05)-1 = 199}.}

\item{max_tries}{How often shall a relocation of an object be tried while
randomizing the pattern.}

\item{save_pattern}{Shall one simulated pattern be returned in the attributes
for debugging/later inspections. The pattern is provided as  WKB (list of
raw vectors) in the attribute \code{randPattern}.}

\item{verbose}{Provide progress information in the console. Roman numerals
(x: 10, C: 100, D: 500, M: 1000) indicate the progress of the simulation
and 'e' denotes the empirical PCF.}
}
\value{
An object of class \link{dists}. If \code{save_pattern = TRUE} an additional
attribute \code{randPattern} is returned containing a WKB (list of raw vectors).
}
\description{
Creates \code{n_sim} null models by permutation of the original pattern and
calculates distances between all object of a pattern closer than \code{max_dist}
and determines the fractions of the perimeter of buffers with distance
\code{dist} inside the study area (needed for edge correction).
}
\details{
Null models are created by randomly rotating and randomly placing all
objects within the study area without overlap. They are used for correcting
the biased pcf and constructing a pointwise critical envelope (cf. Nuske
et al. 2009).

Measuring distances between objects and permutation of the pattern is done
using \href{https://libgeos.org}{GEOS}.
}
\examples{
# it's advised against setting n_sim < 199
ds <- pat2dists(area=sim_area, pattern=sim_pat_reg, max_dist=25, n_sim=3)

# verbose and returns one randomized pattern for debugging
ds_plus <- pat2dists(area=sim_area, pattern=sim_pat_reg, max_dist=5, n_sim=3,
                     verbose=TRUE, save_pattern=TRUE)

\dontrun{
  # wk's plot function needs additional package 'vctrs'
  plot(attr(ds_plus, "randPattern"))
}
}
\references{
Nuske, R.S., Sprauer, S. and Saborowski, J. (2009): Adapting the
pair-correlation function for analysing the spatial distribution of canopy
gaps. Forest Ecology and Management, 259(1): 107–116.
https://doi.org/10.1016/j.foreco.2009.09.050
}
\seealso{
\code{\link[=dists2pcf]{dists2pcf()}}, \code{\link[=plot.fv_pcf]{plot.fv_pcf()}}
}
