# Class dists: Collection of Distances and Ratios

Advanced Use Only. This low-level function creates an object of class
"dists" from raw numerical data.

## Usage

``` r
dists(df, area, n_obj, max_dist)

is.dists(obj)
```

## Arguments

- df:

  A data frame with the columns `sim`, `dist`, and `ratio` containing an
  indicator of the model run (0:n_sim), distances between the objects of
  the patterns, and the ratios of a buffer with distance `dist` inside
  the study area (needed for Ripley's edge correction).

- area:

  size of the study area in square units

- n_obj:

  number of objects in the pattern

- max_dist:

  maximum distance to be measured in pattern

- obj:

  an R object, preferably of class `dists`

## Value

An object of class `dists`.
