# ToDo

## Medium term
[ ] look at parallelizing C++ part using RcppParallel
[ ] allow sf geometries instead of importing from OGR files
[ ] think about max_dist and kernel bandwidth (xlim <- max_dist - bw/2)
[ ] check imported geometries if assumptions are met
[ ] unit testing
[ ] make it compile on windows
[ ] proper way of seeding RNG 
    (check [report](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3551.pdf) )

## Long term
[ ] retest influence of quad_segs against very high number (sfr uses 30 as default for buffer)
[ ] think about precision in wkb/GEOS. look at [sfr](https://github.com/edzer/sfr))
[ ] figure out if GEOSGeometries need to be destroyed (and how) in case of userInterrupt
[ ] Clean up (destroy GEOSGeometries) before throwing exception and in calling functions
[ ] shall we try to guess a sensible max_dist if none provided by user?
[ ] Think about PreparedGeometries 
[ ] shall we allow disjoint study areas?
