// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// geos_version
std::string geos_version();
RcppExport SEXP _apcf_geos_version() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(geos_version());
    return rcpp_result_gen;
END_RCPP
}
// gdal_version
std::string gdal_version(const char* what);
RcppExport SEXP _apcf_gdal_version(SEXP whatSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const char* >::type what(whatSEXP);
    rcpp_result_gen = Rcpp::wrap(gdal_version(what));
    return rcpp_result_gen;
END_RCPP
}
// test_read_wkb
void test_read_wkb(Rcpp::List& wkb);
RcppExport SEXP _apcf_test_read_wkb(SEXP wkbSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List& >::type wkb(wkbSEXP);
    test_read_wkb(wkb);
    return R_NilValue;
END_RCPP
}
// test_read_write_wkb
Rcpp::List test_read_write_wkb(Rcpp::List& wkb);
RcppExport SEXP _apcf_test_read_write_wkb(SEXP wkbSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List& >::type wkb(wkbSEXP);
    rcpp_result_gen = Rcpp::wrap(test_read_write_wkb(wkb));
    return rcpp_result_gen;
END_RCPP
}
// test_read_polys
void test_read_polys(const char* dsn);
RcppExport SEXP _apcf_test_read_polys(SEXP dsnSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const char* >::type dsn(dsnSEXP);
    test_read_polys(dsn);
    return R_NilValue;
END_RCPP
}
// pcf_envelope
Rcpp::DataFrame pcf_envelope(Rcpp::NumericVector sim, Rcpp::NumericVector dist, Rcpp::NumericVector ratio, Rcpp::NumericVector rs, double area, int nobj, double stoyan, int nrank);
RcppExport SEXP _apcf_pcf_envelope(SEXP simSEXP, SEXP distSEXP, SEXP ratioSEXP, SEXP rsSEXP, SEXP areaSEXP, SEXP nobjSEXP, SEXP stoyanSEXP, SEXP nrankSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type sim(simSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type dist(distSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type ratio(ratioSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type rs(rsSEXP);
    Rcpp::traits::input_parameter< double >::type area(areaSEXP);
    Rcpp::traits::input_parameter< int >::type nobj(nobjSEXP);
    Rcpp::traits::input_parameter< double >::type stoyan(stoyanSEXP);
    Rcpp::traits::input_parameter< int >::type nrank(nrankSEXP);
    rcpp_result_gen = Rcpp::wrap(pcf_envelope(sim, dist, ratio, rs, area, nobj, stoyan, nrank));
    return rcpp_result_gen;
END_RCPP
}
// rand_dists_ratios
Rcpp::DataFrame rand_dists_ratios(const char* fn_pattern, const char* fn_area, const double max_dist, const unsigned int n_simulations, const unsigned int max_tries, const bool save_randomized_patterns, const char* save_basename, const bool verbose);
RcppExport SEXP _apcf_rand_dists_ratios(SEXP fn_patternSEXP, SEXP fn_areaSEXP, SEXP max_distSEXP, SEXP n_simulationsSEXP, SEXP max_triesSEXP, SEXP save_randomized_patternsSEXP, SEXP save_basenameSEXP, SEXP verboseSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const char* >::type fn_pattern(fn_patternSEXP);
    Rcpp::traits::input_parameter< const char* >::type fn_area(fn_areaSEXP);
    Rcpp::traits::input_parameter< const double >::type max_dist(max_distSEXP);
    Rcpp::traits::input_parameter< const unsigned int >::type n_simulations(n_simulationsSEXP);
    Rcpp::traits::input_parameter< const unsigned int >::type max_tries(max_triesSEXP);
    Rcpp::traits::input_parameter< const bool >::type save_randomized_patterns(save_randomized_patternsSEXP);
    Rcpp::traits::input_parameter< const char* >::type save_basename(save_basenameSEXP);
    Rcpp::traits::input_parameter< const bool >::type verbose(verboseSEXP);
    rcpp_result_gen = Rcpp::wrap(rand_dists_ratios(fn_pattern, fn_area, max_dist, n_simulations, max_tries, save_randomized_patterns, save_basename, verbose));
    return rcpp_result_gen;
END_RCPP
}
// rand_dists_ratios_wkb
Rcpp::DataFrame rand_dists_ratios_wkb(const Rcpp::List& wkb_pattern, const Rcpp::List& wkb_area, const double max_dist, const unsigned int n_simulations, const unsigned int max_tries, const bool save_randomized_pattern, const bool verbose);
RcppExport SEXP _apcf_rand_dists_ratios_wkb(SEXP wkb_patternSEXP, SEXP wkb_areaSEXP, SEXP max_distSEXP, SEXP n_simulationsSEXP, SEXP max_triesSEXP, SEXP save_randomized_patternSEXP, SEXP verboseSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::List& >::type wkb_pattern(wkb_patternSEXP);
    Rcpp::traits::input_parameter< const Rcpp::List& >::type wkb_area(wkb_areaSEXP);
    Rcpp::traits::input_parameter< const double >::type max_dist(max_distSEXP);
    Rcpp::traits::input_parameter< const unsigned int >::type n_simulations(n_simulationsSEXP);
    Rcpp::traits::input_parameter< const unsigned int >::type max_tries(max_triesSEXP);
    Rcpp::traits::input_parameter< const bool >::type save_randomized_pattern(save_randomized_patternSEXP);
    Rcpp::traits::input_parameter< const bool >::type verbose(verboseSEXP);
    rcpp_result_gen = Rcpp::wrap(rand_dists_ratios_wkb(wkb_pattern, wkb_area, max_dist, n_simulations, max_tries, save_randomized_pattern, verbose));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_apcf_geos_version", (DL_FUNC) &_apcf_geos_version, 0},
    {"_apcf_gdal_version", (DL_FUNC) &_apcf_gdal_version, 1},
    {"_apcf_test_read_wkb", (DL_FUNC) &_apcf_test_read_wkb, 1},
    {"_apcf_test_read_write_wkb", (DL_FUNC) &_apcf_test_read_write_wkb, 1},
    {"_apcf_test_read_polys", (DL_FUNC) &_apcf_test_read_polys, 1},
    {"_apcf_pcf_envelope", (DL_FUNC) &_apcf_pcf_envelope, 8},
    {"_apcf_rand_dists_ratios", (DL_FUNC) &_apcf_rand_dists_ratios, 8},
    {"_apcf_rand_dists_ratios_wkb", (DL_FUNC) &_apcf_rand_dists_ratios_wkb, 7},
    {NULL, NULL, 0}
};

RcppExport void R_init_apcf(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
