# Convert Distances & Ratios to PCF

Estimates the Adapted Pair Correlation Function (PCF) of a pattern
together with a pointwise critical envelope based on distances and
ratios calculated by
[`pat2dists()`](https://rnuske.github.io/apcf/reference/pat2dists.md).

## Usage

``` r
dists2pcf(dists, r, r_max = NULL, kernel = "epanechnikov", stoyan, n_rank)
```

## Arguments

- dists:

  An object of class
  [dists](https://rnuske.github.io/apcf/reference/dists.md). Usually
  created by
  [`pat2dists()`](https://rnuske.github.io/apcf/reference/pat2dists.md)

- r:

  A step size or a vector of values for the argument r at which g(r)
  should be evaluated.

- r_max:

  maximum value for the argument r.

- kernel:

  String. Choice of smoothing kernel (only the "epanechnikov" kernel is
  currently implemented).

- stoyan:

  Bandwidth coefficient (smoothing the Epanechnikov kernel). Penttinen
  et al. (1992) and Stoyan and Stoyan (1994) suggest values between 0.1
  and 0.2.

- n_rank:

  Rank of the value amongst the n_sim simulated values used to construct
  the envelope. A rank of 1 means that the minimum and maximum simulated
  values will be used. Must be \>= 1 and \< n_sim/2. Determines together
  with `n_sim` in
  [`pat2dists()`](https://rnuske.github.io/apcf/reference/pat2dists.md)
  the alpha level of the envelope. If `alpha` and `n_sim` are fix,
  n_rank can be calculated by `(n_sim+1)*alpha/2` eg.
  `(199+1) * 0.05/2 = 5`

## Value

An object of class
[fv_pcf](https://rnuske.github.io/apcf/reference/fv_pcf.md) containing
the function values of the PCF and the envelope.

## Details

Since the pair-correlation function is a density function, we employ the
frequently used Epanechnikov kernel (Silverman 1986, Stoyan and Stoyan
1994, Nuske et al. 2009). The Epanechnikov kernel is a weight function
putting maximal weight to pairs with distance exactly equal to *r* but
also incorporating pairs only roughly at distance *r* with reduced
weight. This weight falls to zero if the actual distance between the
points differs from *r* by at least \\\delta\\, the so-called bandwidth
parameter, which determines the degree of smoothness of the function.
Penttinen et al. (1992) and Stoyan and Stoyan (1994) suggest to set *c*
aka stoyan-parameter of \\c / {\sqrt{\lambda}}\\ between 0.1 and 0.2
with \\\lambda\\ being the intensity of the pattern.

The edge correction is based on suggestions by Ripley (1981). For each
pair of objects \\i\\ and \\j\\, a buffer with buffer distance
\\r\_{ij}\\ is constructed around the object \\i\\. The object \\j\\ is
then weighted by the inverse of the ratios \\p\_{ij}\\ of the buffer
perimeter being within the study area. That way we account for the
reduced probability of finding objects close to the edge of the study
area.

The alpha level of the pointwise critical envelope is \\\alpha =
\frac{n\\rank \* 2}{n\\sim + 1}\\ according to (Besag and Diggle 1977,
Buckland 1984, Stoyan and Stoyan 1994).

## References

Besag, J. and Diggle, P.J. (1977): Simple Monte Carlo tests for spatial
pattern. Journal of the Royal Statistical Society. Series C (Applied
Statistics), 26(3): 327–333. https://doi.org/10.2307/2346974

Buckland, S.T. (1984). Monte Carlo Confidence Intervals. Biometrics,
40(3): 811-817. https://doi.org/10.2307/2530926

Nuske, R.S., Sprauer, S. and Saborowski, J. (2009): Adapting the
pair-correlation function for analysing the spatial distribution of
canopy gaps. Forest Ecology and Management, 259(1): 107–116.
https://doi.org/10.1016/j.foreco.2009.09.050

Penttinen A., Stoyan D., Henttonen H. M. (1992): Marked point processes
in forest statistics. Forest Science, 38(4): 806–824.
https://doi.org/10.1093/forestscience/38.4.806

Ripley, B.D. (1981): Spatial Statistics. John Wiley & Sons, New York.
https://doi.org/10.1002/0471725218

Silverman, B.W. (1986): Density Estimation for Statistics and Data
Analysis. Chapman and Hall, London.

Stoyan, D. and Stoyan, H. (1994) Fractals, random shapes and point
fields: Methods of geometrical statistics. John Wiley & Sons,
Chichester.

## See also

[`pat2dists()`](https://rnuske.github.io/apcf/reference/pat2dists.md),
[`plot.fv_pcf()`](https://rnuske.github.io/apcf/reference/plot.fv_pcf.md)

## Examples

``` r
# it's advised against setting n_sim < 199
ds <- pat2dists(area=sim_area, pattern=sim_pat_reg, max_dist=25, n_sim=3)

# derive PCF and envelope
pcf <- dists2pcf(ds, r=0.2, r_max=25, stoyan=0.15, n_rank=1)
```
