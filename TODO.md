# ToDo

## Medium term
- [ ] look at parallelizing C++ part using RcppParallel 
- [ ] think about max_dist and kernel bandwidth (xlim <- max_dist - bw/2) 
- [ ] check imported geometries. Are my assumptions met? 
- [ ] unit testing 

## Long term
- [ ] retest influence of quad_segs against very high number ([sf](https://github.com/r-spatial/sf)  uses 30 as default for buffer) 
- [ ] think about precision in wkb/GEOS (cf. [sf](https://github.com/r-spatial/sf))
- [ ] figure out if GEOSGeometries need to be destroyed (and how) in case of userInterrupt 
- [ ] Clean up (destroy GEOSGeometries) before throwing exception and in calling functions 
- [ ] shall we try to guess a sensible max_dist if none provided by user? 
- [ ] think about PreparedGeometries 
- [ ] shall we allow disjoint study areas? 
