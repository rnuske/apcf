## apcf: Adapted Pair Correlation Function

<!-- badges: start -->
[![R-CMD-check](https://github.com/rnuske/apcf/workflows/R-CMD-check/badge.svg)](https://github.com/rnuske/apcf/actions)
[![Drone.io Status](https://cloud.drone.io/api/badges/rnuske/apcf/status.svg)](https://cloud.drone.io/rnuske/apcf) 
[![Package-License](https://img.shields.io/badge/license-GPL--3-brightgreen.svg?style=flat)](https://www.gnu.org/licenses/gpl-3.0.html) 
[![CRAN](https://www.r-pkg.org/badges/version/apcf)](https://cran.r-project.org/package=apcf) 
[![Dependencies](https://tinyverse.netlify.com/badge/apcf)](https://cran.r-project.org/package=apcf) 
[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.2535612.svg)](https://doi.org/10.5281/zenodo.2535612) 
<!-- badges: end -->


The Adapted Pair Correlation Function transfers the concept of the Pair Correlation Function from point patterns to patterns of patches of finite size and irregular shape (eg. lakes within a country). The main tasks are (i) the construction of nullmodels by randomizing the patches of the original pattern within the study area, (ii) the edge correction by determining the proportion of a buffer within the study area, and (iii) the calculation of the shortest distances between the patches.

This is a reimplementation of the Adapted Pair Correlation Function (Nuske et al. 2009) in C++ using only the GEOS library.

![](./man/figures/sim_pat_pcf.png)

### Requirements
For Unix-alikes GEOS (>= 3.4.0) is required.

On Ubuntu bionic (18.04) and beyond one can install the dependency simply with `sudo apt install libgeos-dev`. 
In earlier Ubuntu version either add [ubuntugis-unstable](http://ppa.launchpad.net/ubuntugis/ubuntugis-unstable/ubuntu/) to the `sources.list` and use above command or compile GEOS from source.


### Installation
The stable version can be installed from CRAN
```r
install.packages("apcf")
```

and the development version is available from Github using the package remotes (formerly devtools)
```r
if(!require("remotes")) install.packages("remotes")
remotes::install_github("rnuske/apcf")
```


### Usage
```r
# calculate distances between patches of original pattern and 3 nullmodels
# number of nullmodels should by at least 199 and better yet 999
ds <- pat2dists(area=sim_area, pattern=sim_pat_reg, max_dist=25, n_sim=3)

# derive PCF and envelope from distances
pcf <- dists2pcf(ds, r=0.2, r_max=25, stoyan=0.15, n_rank=1)

# plot PCF
plot(x=pcf, xlim=c(0, 20), ylim=c(0, 2.2))
```


### Links
* [GEOS](https://libgeos.org)
* [Rcpp Website](http://www.rcpp.org)
* [R package `sf`, a modern approach to geo data in R](https://github.com/r-spatial/sf)


### References
Nuske, R.S., Sprauer, S. and Saborowski, J. (2009): Adapting the pair-correlation function for analysing the spatial distribution of canopy gaps. Forest Ecology and Management 259(1): 107–116. https://doi.org/10.1016/j.foreco.2009.09.050
