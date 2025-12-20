# Class fv_pcf: Function Value Table for PCFs

Advanced Use Only. This low-level function creates an object of class
"fv_pcf" from raw numerical data.

## Usage

``` r
fv_pcf(df, n_sim, n_rank, correc, kernel, stoyan, bw)

is.fv_pcf(obj)

# S3 method for class 'fv_pcf'
print(x, ...)

# S3 method for class 'fv_pcf'
summary(object, ...)
```

## Arguments

- df:

  A data frame with at least 2 columns named 'r' and 'g' containing the
  values of the function argument (r) and the corresponding values (g).
  Usually the upper 'upr' and lower 'lwr' bounds of a pointwise critical
  envelope are passed along as well.

- n_sim:

  Integer. Number of generated simulated patterns used for computing the
  envelope

- n_rank:

  Integer. Rank of the envelope value amongst the `n_sim` simulated
  values. A rank of 1 means that the minimum and maximum simulated
  values will be used.

- correc:

  String. Choice of edge correction (eg. "Ripley").

- kernel:

  String. Choice of smoothing kernel (eg. "epanechnikov").

- stoyan:

  Bandwidth coefficient used in smoothing kernel.

- bw:

  Bandwidth used in smoothing kernel.

- x, obj, object:

  an R object, preferably of class `fv_pcf`

- ...:

  additional parameter

## Value

An object of class `fv_pcf`.
