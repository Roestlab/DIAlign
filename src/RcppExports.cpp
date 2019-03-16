// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// initializeMatrix
NumericMatrix initializeMatrix(float initVal, int ROW_SIZE, int COL_SIZE);
RcppExport SEXP _DIAlignR_initializeMatrix(SEXP initValSEXP, SEXP ROW_SIZESEXP, SEXP COL_SIZESEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< float >::type initVal(initValSEXP);
    Rcpp::traits::input_parameter< int >::type ROW_SIZE(ROW_SIZESEXP);
    Rcpp::traits::input_parameter< int >::type COL_SIZE(COL_SIZESEXP);
    rcpp_result_gen = Rcpp::wrap(initializeMatrix(initVal, ROW_SIZE, COL_SIZE));
    return rcpp_result_gen;
END_RCPP
}
// getseqSimMat
void getseqSimMat(std::string seq1, std::string seq2, float Match, float MisMatch, NumericMatrix s);
RcppExport SEXP _DIAlignR_getseqSimMat(SEXP seq1SEXP, SEXP seq2SEXP, SEXP MatchSEXP, SEXP MisMatchSEXP, SEXP sSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type seq1(seq1SEXP);
    Rcpp::traits::input_parameter< std::string >::type seq2(seq2SEXP);
    Rcpp::traits::input_parameter< float >::type Match(MatchSEXP);
    Rcpp::traits::input_parameter< float >::type MisMatch(MisMatchSEXP);
    Rcpp::traits::input_parameter< NumericMatrix >::type s(sSEXP);
    getseqSimMat(seq1, seq2, Match, MisMatch, s);
    return R_NilValue;
END_RCPP
}
// setAffineAlignObj1_S4
S4 setAffineAlignObj1_S4(bool TorF);
RcppExport SEXP _DIAlignR_setAffineAlignObj1_S4(SEXP TorFSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< bool >::type TorF(TorFSEXP);
    rcpp_result_gen = Rcpp::wrap(setAffineAlignObj1_S4(TorF));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_s4
S4 rcpp_s4(std::string Name);
RcppExport SEXP _DIAlignR_rcpp_s4(SEXP NameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type Name(NameSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_s4(Name));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_DIAlignR_initializeMatrix", (DL_FUNC) &_DIAlignR_initializeMatrix, 3},
    {"_DIAlignR_getseqSimMat", (DL_FUNC) &_DIAlignR_getseqSimMat, 5},
    {"_DIAlignR_setAffineAlignObj1_S4", (DL_FUNC) &_DIAlignR_setAffineAlignObj1_S4, 1},
    {"_DIAlignR_rcpp_s4", (DL_FUNC) &_DIAlignR_rcpp_s4, 1},
    {NULL, NULL, 0}
};

RcppExport void R_init_DIAlignR(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
