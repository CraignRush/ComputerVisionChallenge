/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * denseMatch.c
 *
 * Code generation for function 'denseMatch'
 *
 */

/* Include files */
#include "mwmathutil.h"
#include <string.h>
#include "rt_nonfinite.h"
#include "denseMatch.h"
#include "_coder_denseMatch_mex.h"

/* Type Definitions */
#include "emlrt.h"
#ifndef typedef_struct_T
#define typedef_struct_T

typedef struct {
  real_T tv_sec;
  real_T tv_nsec;
} struct_T;

#endif                                 /*typedef_struct_T*/

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
static const volatile char_T *emlrtBreakCheckR2012bFlagVar = NULL;
static struct_T savedTime;
static boolean_T savedTime_not_empty;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131482U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "denseMatch",                        /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

static emlrtRSInfo emlrtRSI = { 43,    /* lineNo */
  "denseMatch",                        /* fcnName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pathName */
};

static emlrtRSInfo b_emlrtRSI = { 51,  /* lineNo */
  "denseMatch",                        /* fcnName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pathName */
};

static emlrtRSInfo c_emlrtRSI = { 56,  /* lineNo */
  "denseMatch",                        /* fcnName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pathName */
};

static emlrtRSInfo d_emlrtRSI = { 74,  /* lineNo */
  "denseMatch",                        /* fcnName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pathName */
};

static emlrtRSInfo e_emlrtRSI = { 81,  /* lineNo */
  "denseMatch",                        /* fcnName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pathName */
};

static emlrtRSInfo f_emlrtRSI = { 100, /* lineNo */
  "denseMatch",                        /* fcnName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pathName */
};

static emlrtRSInfo g_emlrtRSI = { 102, /* lineNo */
  "denseMatch",                        /* fcnName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pathName */
};

static emlrtRSInfo h_emlrtRSI = { 108, /* lineNo */
  "denseMatch",                        /* fcnName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pathName */
};

static emlrtRSInfo i_emlrtRSI = { 110, /* lineNo */
  "denseMatch",                        /* fcnName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pathName */
};

static emlrtRSInfo j_emlrtRSI = { 113, /* lineNo */
  "denseMatch",                        /* fcnName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pathName */
};

static emlrtRSInfo k_emlrtRSI = { 116, /* lineNo */
  "denseMatch",                        /* fcnName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pathName */
};

static emlrtRSInfo l_emlrtRSI = { 118, /* lineNo */
  "denseMatch",                        /* fcnName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pathName */
};

static emlrtRSInfo m_emlrtRSI = { 121, /* lineNo */
  "denseMatch",                        /* fcnName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pathName */
};

static emlrtRSInfo n_emlrtRSI = { 125, /* lineNo */
  "denseMatch",                        /* fcnName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pathName */
};

static emlrtRSInfo o_emlrtRSI = { 126, /* lineNo */
  "denseMatch",                        /* fcnName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pathName */
};

static emlrtRSInfo p_emlrtRSI = { 130, /* lineNo */
  "denseMatch",                        /* fcnName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pathName */
};

static emlrtRSInfo q_emlrtRSI = { 131, /* lineNo */
  "denseMatch",                        /* fcnName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pathName */
};

static emlrtRSInfo r_emlrtRSI = { 141, /* lineNo */
  "denseMatch",                        /* fcnName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pathName */
};

static emlrtRSInfo s_emlrtRSI = { 142, /* lineNo */
  "denseMatch",                        /* fcnName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pathName */
};

static emlrtRSInfo t_emlrtRSI = { 164, /* lineNo */
  "denseMatch",                        /* fcnName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pathName */
};

static emlrtRSInfo u_emlrtRSI = { 37,  /* lineNo */
  "tic",                               /* fcnName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\timefun\\tic.m"/* pathName */
};

static emlrtRSInfo v_emlrtRSI = { 8,   /* lineNo */
  "getTime",                           /* fcnName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\timefun\\private\\getTime.m"/* pathName */
};

static emlrtRSInfo w_emlrtRSI = { 25,  /* lineNo */
  "getTimeEMLRT",                      /* fcnName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\timefun\\private\\getTime.m"/* pathName */
};

static emlrtRSInfo x_emlrtRSI = { 14,  /* lineNo */
  "timeKeeper",                        /* fcnName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\timefun\\private\\timeKeeper.m"/* pathName */
};

static emlrtRSInfo y_emlrtRSI = { 20,  /* lineNo */
  "mean2",                             /* fcnName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\images\\images\\mean2.m"/* pathName */
};

static emlrtRSInfo ab_emlrtRSI = { 9,  /* lineNo */
  "sum",                               /* fcnName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\datafun\\sum.m"/* pathName */
};

static emlrtRSInfo bb_emlrtRSI = { 73, /* lineNo */
  "sumprod",                           /* fcnName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\sumprod.m"/* pathName */
};

static emlrtRSInfo cb_emlrtRSI = { 134,/* lineNo */
  "combineVectorElements",             /* fcnName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\combineVectorElements.m"/* pathName */
};

static emlrtRSInfo db_emlrtRSI = { 193,/* lineNo */
  "colMajorFlatIter",                  /* fcnName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\combineVectorElements.m"/* pathName */
};

static emlrtRSInfo eb_emlrtRSI = { 21, /* lineNo */
  "eml_int_forloop_overflow_check",    /* fcnName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\eml\\eml_int_forloop_overflow_check.m"/* pathName */
};

static emlrtRSInfo fb_emlrtRSI = { 16, /* lineNo */
  "abs",                               /* fcnName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\elfun\\abs.m"/* pathName */
};

static emlrtRSInfo gb_emlrtRSI = { 74, /* lineNo */
  "applyScalarFunction",               /* fcnName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\eml\\+coder\\+internal\\applyScalarFunction.m"/* pathName */
};

static emlrtRSInfo hb_emlrtRSI = { 55, /* lineNo */
  "power",                             /* fcnName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\ops\\power.m"/* pathName */
};

static emlrtRSInfo ib_emlrtRSI = { 64, /* lineNo */
  "fltpower",                          /* fcnName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\ops\\power.m"/* pathName */
};

static emlrtRSInfo jb_emlrtRSI = { 65, /* lineNo */
  "applyBinaryScalarFunction",         /* fcnName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\eml\\+coder\\+internal\\applyBinaryScalarFunction.m"/* pathName */
};

static emlrtRSInfo kb_emlrtRSI = { 187,/* lineNo */
  "flatIter",                          /* fcnName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\eml\\+coder\\+internal\\applyBinaryScalarFunction.m"/* pathName */
};

static emlrtRSInfo lb_emlrtRSI = { 172,/* lineNo */
  "colMajorFlatIter",                  /* fcnName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\combineVectorElements.m"/* pathName */
};

static emlrtRSInfo mb_emlrtRSI = { 31, /* lineNo */
  "toc",                               /* fcnName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\timefun\\toc.m"/* pathName */
};

static emlrtRSInfo nb_emlrtRSI = { 36, /* lineNo */
  "toc",                               /* fcnName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\timefun\\toc.m"/* pathName */
};

static emlrtMCInfo emlrtMCI = { 27,    /* lineNo */
  5,                                   /* colNo */
  "error",                             /* fName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\lang\\error.m"/* pName */
};

static emlrtRTEInfo emlrtRTEI = { 47,  /* lineNo */
  1,                                   /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo b_emlrtRTEI = { 48,/* lineNo */
  1,                                   /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo c_emlrtRTEI = { 62,/* lineNo */
  1,                                   /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo d_emlrtRTEI = { 94,/* lineNo */
  24,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo e_emlrtRTEI = { 97,/* lineNo */
  25,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo f_emlrtRTEI = { 105,/* lineNo */
  13,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo g_emlrtRTEI = { 108,/* lineNo */
  37,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo h_emlrtRTEI = { 113,/* lineNo */
  50,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo i_emlrtRTEI = { 110,/* lineNo */
  37,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo j_emlrtRTEI = { 116,/* lineNo */
  34,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo k_emlrtRTEI = { 121,/* lineNo */
  47,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo l_emlrtRTEI = { 113,/* lineNo */
  37,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo m_emlrtRTEI = { 130,/* lineNo */
  37,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo n_emlrtRTEI = { 118,/* lineNo */
  34,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo o_emlrtRTEI = { 131,/* lineNo */
  37,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo p_emlrtRTEI = { 121,/* lineNo */
  34,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo q_emlrtRTEI = { 127,/* lineNo */
  17,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo r_emlrtRTEI = { 132,/* lineNo */
  17,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo s_emlrtRTEI = { 26,/* lineNo */
  54,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo t_emlrtRTEI = { 26,/* lineNo */
  42,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo u_emlrtRTEI = { 130,/* lineNo */
  32,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo v_emlrtRTEI = { 131,/* lineNo */
  32,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo w_emlrtRTEI = { 16,/* lineNo */
  5,                                   /* colNo */
  "abs",                               /* fName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\elfun\\abs.m"/* pName */
};

static emlrtRTEInfo x_emlrtRTEI = { 64,/* lineNo */
  5,                                   /* colNo */
  "power",                             /* fName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\ops\\power.m"/* pName */
};

static emlrtRTEInfo y_emlrtRTEI = { 9, /* lineNo */
  1,                                   /* colNo */
  "sum",                               /* fName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\datafun\\sum.m"/* pName */
};

static emlrtRTEInfo ab_emlrtRTEI = { 134,/* lineNo */
  13,                                  /* colNo */
  "combineVectorElements",             /* fName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\combineVectorElements.m"/* pName */
};

static emlrtRTEInfo bb_emlrtRTEI = { 1,/* lineNo */
  1,                                   /* colNo */
  "_coder_denseMatch_api",             /* fName */
  ""                                   /* pName */
};

static emlrtRTEInfo cb_emlrtRTEI = { 12,/* lineNo */
  9,                                   /* colNo */
  "sqrt",                              /* fName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\elfun\\sqrt.m"/* pName */
};

static emlrtECInfo emlrtECI = { 2,     /* nDims */
  132,                                 /* lineNo */
  33,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtECInfo b_emlrtECI = { 2,   /* nDims */
  127,                                 /* lineNo */
  33,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtECInfo c_emlrtECI = { 2,   /* nDims */
  121,                                 /* lineNo */
  34,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtECInfo d_emlrtECI = { 2,   /* nDims */
  118,                                 /* lineNo */
  34,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtECInfo e_emlrtECI = { 2,   /* nDims */
  116,                                 /* lineNo */
  34,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtECInfo f_emlrtECI = { 2,   /* nDims */
  113,                                 /* lineNo */
  37,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtECInfo g_emlrtECI = { 2,   /* nDims */
  110,                                 /* lineNo */
  37,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtECInfo h_emlrtECI = { 2,   /* nDims */
  108,                                 /* lineNo */
  37,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtBCInfo emlrtBCI = { -1,    /* iFirst */
  -1,                                  /* iLast */
  97,                                  /* lineNo */
  61,                                  /* colNo */
  "rightImage",                        /* aName */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo emlrtDCI = { 97,    /* lineNo */
  61,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo b_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  97,                                  /* lineNo */
  51,                                  /* colNo */
  "rightImage",                        /* aName */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo b_emlrtDCI = { 97,  /* lineNo */
  51,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo c_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  97,                                  /* lineNo */
  44,                                  /* colNo */
  "rightImage",                        /* aName */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo c_emlrtDCI = { 97,  /* lineNo */
  44,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo d_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  97,                                  /* lineNo */
  36,                                  /* colNo */
  "rightImage",                        /* aName */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo d_emlrtDCI = { 97,  /* lineNo */
  36,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo e_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  94,                                  /* lineNo */
  57,                                  /* colNo */
  "leftImage",                         /* aName */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo e_emlrtDCI = { 94,  /* lineNo */
  57,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo f_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  94,                                  /* lineNo */
  49,                                  /* colNo */
  "leftImage",                         /* aName */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo f_emlrtDCI = { 94,  /* lineNo */
  49,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo g_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  94,                                  /* lineNo */
  42,                                  /* colNo */
  "leftImage",                         /* aName */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo g_emlrtDCI = { 94,  /* lineNo */
  42,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo h_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  94,                                  /* lineNo */
  34,                                  /* colNo */
  "leftImage",                         /* aName */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo h_emlrtDCI = { 94,  /* lineNo */
  34,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m",/* pName */
  1                                    /* checkKind */
};

static emlrtRTEInfo db_emlrtRTEI = { 90,/* lineNo */
  15,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo eb_emlrtRTEI = { 77,/* lineNo */
  11,                                  /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtRTEInfo fb_emlrtRTEI = { 75,/* lineNo */
  7,                                   /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"/* pName */
};

static emlrtBCInfo i_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  160,                                 /* lineNo */
  9,                                   /* colNo */
  "dispMap",                           /* aName */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo i_emlrtDCI = { 160, /* lineNo */
  9,                                   /* colNo */
  "denseMatch",                        /* fName */
  "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m",/* pName */
  1                                    /* checkKind */
};

static emlrtRTEInfo gb_emlrtRTEI = { 83,/* lineNo */
  9,                                   /* colNo */
  "checkPOSIXStatus",                  /* fName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\timefun\\private\\getTime.m"/* pName */
};

static emlrtRTEInfo hb_emlrtRTEI = { 31,/* lineNo */
  23,                                  /* colNo */
  "sumprod",                           /* fName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\sumprod.m"/* pName */
};

static emlrtRTEInfo ib_emlrtRTEI = { 88,/* lineNo */
  9,                                   /* colNo */
  "check_forloop_overflow_error",      /* fName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\eml\\eml_int_forloop_overflow_check.m"/* pName */
};

static emlrtRTEInfo jb_emlrtRTEI = { 63,/* lineNo */
  9,                                   /* colNo */
  "sumprod",                           /* fName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\sumprod.m"/* pName */
};

static emlrtRTEInfo kb_emlrtRTEI = { 12,/* lineNo */
  9,                                   /* colNo */
  "timeKeeper",                        /* fName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\timefun\\private\\timeKeeper.m"/* pName */
};

static const char_T cv0[26] = { 'e', 'm', 'l', 'r', 't', 'C', 'l', 'o', 'c', 'k',
  'G', 'e', 't', 't', 'i', 'm', 'e', 'M', 'o', 'n', 'o', 't', 'o', 'n', 'i', 'c'
};

static emlrtRSInfo ob_emlrtRSI = { 27, /* lineNo */
  "error",                             /* fcnName */
  "C:\\Program Files\\MATLAB\\R2019a\\toolbox\\eml\\lib\\matlab\\lang\\error.m"/* pathName */
};

/* Function Declarations */
static void b_abs(const emlrtStack *sp, const emxArray_real_T *x,
                  emxArray_real_T *y);
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_uint8_T *y);
static const mxArray *b_emlrt_marshallOut(const real_T u);
static real_T b_mod(real_T x);
static boolean_T b_strcmp(const emxArray_char_T *a);
static real_T b_sum(const emlrtStack *sp, const emxArray_real_T *x);
static void b_timeKeeper(const emlrtStack *sp, real_T *outTime_tv_sec, real_T
  *outTime_tv_nsec);
static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *corrWindowSize, const char_T *identifier);
static boolean_T c_strcmp(const emxArray_char_T *a);
static void check_forloop_overflow_error(const emlrtStack *sp);
static real_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void denseMatch_once(void);
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *method,
  const char_T *identifier, emxArray_char_T *y);
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *rightImage,
  const char_T *identifier, emxArray_uint8_T *y);
static const mxArray *emlrt_marshallOut(const emxArray_real_T *u);
static void emxEnsureCapacity_char_T(const emlrtStack *sp, emxArray_char_T
  *emxArray, int32_T oldNumel, const emlrtRTEInfo *srcLocation);
static void emxEnsureCapacity_real_T(const emlrtStack *sp, emxArray_real_T
  *emxArray, int32_T oldNumel, const emlrtRTEInfo *srcLocation);
static void emxEnsureCapacity_uint8_T(const emlrtStack *sp, emxArray_uint8_T
  *emxArray, int32_T oldNumel, const emlrtRTEInfo *srcLocation);
static void emxFree_char_T(emxArray_char_T **pEmxArray);
static void emxFree_real_T(emxArray_real_T **pEmxArray);
static void emxFree_uint8_T(emxArray_uint8_T **pEmxArray);
static void emxInit_char_T(const emlrtStack *sp, emxArray_char_T **pEmxArray,
  int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush);
static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush);
static void emxInit_uint8_T(const emlrtStack *sp, emxArray_uint8_T **pEmxArray,
  int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush);
static void error(const emlrtStack *sp, const mxArray *b, emlrtMCInfo *location);
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_char_T *y);
static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_uint8_T *ret);
static real_T h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_char_T *ret);
static real_T mean2(const emlrtStack *sp, const emxArray_real_T *x);
static void power(const emlrtStack *sp, const emxArray_real_T *a,
                  emxArray_real_T *y);
static void sum(const emlrtStack *sp, const emxArray_real_T *x, emxArray_real_T *
                y);
static void tic(const emlrtStack *sp);
static void timeKeeper(const emlrtStack *sp, real_T newTime_tv_sec, real_T
  newTime_tv_nsec);
static real_T toc(const emlrtStack *sp);

/* Function Definitions */
static void b_abs(const emlrtStack *sp, const emxArray_real_T *x,
                  emxArray_real_T *y)
{
  int32_T nx;
  uint32_T unnamed_idx_0;
  uint32_T unnamed_idx_1;
  int32_T k;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &fb_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  nx = x->size[0] * x->size[1];
  unnamed_idx_0 = (uint32_T)x->size[0];
  unnamed_idx_1 = (uint32_T)x->size[1];
  k = y->size[0] * y->size[1];
  y->size[0] = (int32_T)unnamed_idx_0;
  y->size[1] = (int32_T)unnamed_idx_1;
  emxEnsureCapacity_real_T(&st, y, k, &w_emlrtRTEI);
  b_st.site = &gb_emlrtRSI;
  if ((1 <= nx) && (nx > 2147483646)) {
    c_st.site = &eb_emlrtRSI;
    check_forloop_overflow_error(&c_st);
  }

  for (k = 0; k < nx; k++) {
    y->data[k] = muDoubleScalarAbs(x->data[k]);
  }
}

static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_uint8_T *y)
{
  g_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static const mxArray *b_emlrt_marshallOut(const real_T u)
{
  const mxArray *y;
  const mxArray *m4;
  y = NULL;
  m4 = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m4);
  return y;
}

static real_T b_mod(real_T x)
{
  real_T r;
  if (muDoubleScalarIsNaN(x) || muDoubleScalarIsInf(x)) {
    r = rtNaN;
  } else if (x == 0.0) {
    r = 0.0;
  } else {
    r = muDoubleScalarRem(x, 2.0);
    if (r == 0.0) {
      r = 0.0;
    } else {
      if (x < 0.0) {
        r += 2.0;
      }
    }
  }

  return r;
}

static boolean_T b_strcmp(const emxArray_char_T *a)
{
  boolean_T b_bool;
  int32_T kstr;
  int32_T exitg1;
  static const char_T cv7[3] = { 'N', 'C', 'C' };

  b_bool = false;
  if (a->size[1] == 3) {
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 3) {
        if (a->data[kstr] != cv7[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

static real_T b_sum(const emlrtStack *sp, const emxArray_real_T *x)
{
  real_T y;
  int32_T vlen;
  boolean_T overflow;
  int32_T k;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &ab_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  b_st.site = &bb_emlrtRSI;
  vlen = x->size[1];
  if (x->size[1] == 0) {
    y = 0.0;
  } else {
    c_st.site = &cb_emlrtRSI;
    y = x->data[0];
    d_st.site = &db_emlrtRSI;
    overflow = ((2 <= x->size[1]) && (x->size[1] > 2147483646));
    if (overflow) {
      e_st.site = &eb_emlrtRSI;
      check_forloop_overflow_error(&e_st);
    }

    for (k = 2; k <= vlen; k++) {
      y += x->data[k - 1];
    }
  }

  return y;
}

static void b_timeKeeper(const emlrtStack *sp, real_T *outTime_tv_sec, real_T
  *outTime_tv_nsec)
{
  if (!savedTime_not_empty) {
    emlrtErrorWithMessageIdR2018a(sp, &kb_emlrtRTEI,
      "MATLAB:toc:callTicFirstNoInputs", "MATLAB:toc:callTicFirstNoInputs", 0);
  }

  *outTime_tv_sec = savedTime.tv_sec;
  *outTime_tv_nsec = savedTime.tv_nsec;
}

static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *corrWindowSize, const char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(corrWindowSize), &thisId);
  emlrtDestroyArray(&corrWindowSize);
  return y;
}

static boolean_T c_strcmp(const emxArray_char_T *a)
{
  boolean_T b_bool;
  int32_T kstr;
  int32_T exitg1;
  static const char_T cv8[4] = { 'Z', 'N', 'C', 'C' };

  b_bool = false;
  if (a->size[1] == 4) {
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 4) {
        if (a->data[kstr] != cv8[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

static void check_forloop_overflow_error(const emlrtStack *sp)
{
  emlrtErrorWithMessageIdR2018a(sp, &ib_emlrtRTEI,
    "Coder:toolbox:int_forloop_overflow", "Coder:toolbox:int_forloop_overflow",
    3, 4, 5, "int32");
}

static real_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = h_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void denseMatch_once(void)
{
  savedTime_not_empty = false;
}

static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *method,
  const char_T *identifier, emxArray_char_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  f_emlrt_marshallIn(sp, emlrtAlias(method), &thisId, y);
  emlrtDestroyArray(&method);
}

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *rightImage,
  const char_T *identifier, emxArray_uint8_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(rightImage), &thisId, y);
  emlrtDestroyArray(&rightImage);
}

static const mxArray *emlrt_marshallOut(const emxArray_real_T *u)
{
  const mxArray *y;
  const mxArray *m3;
  static const int32_T iv4[2] = { 0, 0 };

  y = NULL;
  m3 = emlrtCreateNumericArray(2, iv4, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m3, &u->data[0]);
  emlrtSetDimensions((mxArray *)m3, u->size, 2);
  emlrtAssign(&y, m3);
  return y;
}

static void emxEnsureCapacity_char_T(const emlrtStack *sp, emxArray_char_T
  *emxArray, int32_T oldNumel, const emlrtRTEInfo *srcLocation)
{
  int32_T newNumel;
  int32_T i;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }

  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel = (int32_T)emlrtSizeMulR2012b((uint32_T)newNumel, (uint32_T)
      emxArray->size[i], srcLocation, sp);
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i <<= 1;
      }
    }

    newData = emlrtCallocMex((uint32_T)i, sizeof(char_T));
    if (newData == NULL) {
      emlrtHeapAllocationErrorR2012b(srcLocation, sp);
    }

    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(char_T) * oldNumel);
      if (emxArray->canFreeData) {
        emlrtFreeMex(emxArray->data);
      }
    }

    emxArray->data = (char_T *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

static void emxEnsureCapacity_real_T(const emlrtStack *sp, emxArray_real_T
  *emxArray, int32_T oldNumel, const emlrtRTEInfo *srcLocation)
{
  int32_T newNumel;
  int32_T i;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }

  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel = (int32_T)emlrtSizeMulR2012b((uint32_T)newNumel, (uint32_T)
      emxArray->size[i], srcLocation, sp);
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i <<= 1;
      }
    }

    newData = emlrtCallocMex((uint32_T)i, sizeof(real_T));
    if (newData == NULL) {
      emlrtHeapAllocationErrorR2012b(srcLocation, sp);
    }

    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(real_T) * oldNumel);
      if (emxArray->canFreeData) {
        emlrtFreeMex(emxArray->data);
      }
    }

    emxArray->data = (real_T *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

static void emxEnsureCapacity_uint8_T(const emlrtStack *sp, emxArray_uint8_T
  *emxArray, int32_T oldNumel, const emlrtRTEInfo *srcLocation)
{
  int32_T newNumel;
  int32_T i;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }

  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel = (int32_T)emlrtSizeMulR2012b((uint32_T)newNumel, (uint32_T)
      emxArray->size[i], srcLocation, sp);
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i <<= 1;
      }
    }

    newData = emlrtCallocMex((uint32_T)i, sizeof(uint8_T));
    if (newData == NULL) {
      emlrtHeapAllocationErrorR2012b(srcLocation, sp);
    }

    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(uint8_T) * oldNumel);
      if (emxArray->canFreeData) {
        emlrtFreeMex(emxArray->data);
      }
    }

    emxArray->data = (uint8_T *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

static void emxFree_char_T(emxArray_char_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_char_T *)NULL) {
    if (((*pEmxArray)->data != (char_T *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((*pEmxArray)->data);
    }

    emlrtFreeMex((*pEmxArray)->size);
    emlrtFreeMex(*pEmxArray);
    *pEmxArray = (emxArray_char_T *)NULL;
  }
}

static void emxFree_real_T(emxArray_real_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real_T *)NULL) {
    if (((*pEmxArray)->data != (real_T *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((*pEmxArray)->data);
    }

    emlrtFreeMex((*pEmxArray)->size);
    emlrtFreeMex(*pEmxArray);
    *pEmxArray = (emxArray_real_T *)NULL;
  }
}

static void emxFree_uint8_T(emxArray_uint8_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_uint8_T *)NULL) {
    if (((*pEmxArray)->data != (uint8_T *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((*pEmxArray)->data);
    }

    emlrtFreeMex((*pEmxArray)->size);
    emlrtFreeMex(*pEmxArray);
    *pEmxArray = (emxArray_uint8_T *)NULL;
  }
}

static void emxInit_char_T(const emlrtStack *sp, emxArray_char_T **pEmxArray,
  int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush)
{
  emxArray_char_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_char_T *)emlrtMallocMex(sizeof(emxArray_char_T));
  if ((void *)*pEmxArray == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void (*)(void *))
      emxFree_char_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (char_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T) * numDimensions);
  if ((void *)emxArray->size == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush)
{
  emxArray_real_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_real_T *)emlrtMallocMex(sizeof(emxArray_real_T));
  if ((void *)*pEmxArray == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void (*)(void *))
      emxFree_real_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (real_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T) * numDimensions);
  if ((void *)emxArray->size == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

static void emxInit_uint8_T(const emlrtStack *sp, emxArray_uint8_T **pEmxArray,
  int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush)
{
  emxArray_uint8_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_uint8_T *)emlrtMallocMex(sizeof(emxArray_uint8_T));
  if ((void *)*pEmxArray == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void (*)(void *))
      emxFree_uint8_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (uint8_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T) * numDimensions);
  if ((void *)emxArray->size == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

static void error(const emlrtStack *sp, const mxArray *b, emlrtMCInfo *location)
{
  const mxArray *pArray;
  pArray = b;
  emlrtCallMATLABR2012b(sp, 0, NULL, 1, &pArray, "error", true, location);
}

static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_char_T *y)
{
  i_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_uint8_T *ret)
{
  static const int32_T dims[2] = { -1, -1 };

  const boolean_T bv0[2] = { true, true };

  int32_T iv5[2];
  int32_T i12;
  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "uint8", false, 2U, dims, &bv0[0],
    iv5);
  ret->allocatedSize = iv5[0] * iv5[1];
  i12 = ret->size[0] * ret->size[1];
  ret->size[0] = iv5[0];
  ret->size[1] = iv5[1];
  emxEnsureCapacity_uint8_T(sp, ret, i12, (emlrtRTEInfo *)NULL);
  ret->data = (uint8_T *)emlrtMxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static real_T h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, &dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_char_T *ret)
{
  static const int32_T dims[2] = { 1, -1 };

  const boolean_T bv1[2] = { false, true };

  int32_T iv6[2];
  int32_T i13;
  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "char", false, 2U, dims, &bv1[0],
    iv6);
  i13 = ret->size[0] * ret->size[1];
  ret->size[0] = iv6[0];
  ret->size[1] = iv6[1];
  emxEnsureCapacity_char_T(sp, ret, i13, (emlrtRTEInfo *)NULL);
  emlrtImportArrayR2015b(sp, src, ret->data, 1, false);
  emlrtDestroyArray(&src);
}

static real_T mean2(const emlrtStack *sp, const emxArray_real_T *x)
{
  real_T y;
  int32_T vlen;
  boolean_T overflow;
  int32_T k;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &y_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  f_st.prev = &e_st;
  f_st.tls = e_st.tls;
  b_st.site = &ab_emlrtRSI;
  c_st.site = &bb_emlrtRSI;
  vlen = x->size[0] * x->size[1];
  if (x->size[0] * x->size[1] == 0) {
    y = 0.0;
  } else {
    d_st.site = &cb_emlrtRSI;
    y = x->data[0];
    e_st.site = &db_emlrtRSI;
    overflow = ((2 <= x->size[0] * x->size[1]) && (x->size[0] * x->size[1] >
      2147483646));
    if (overflow) {
      f_st.site = &eb_emlrtRSI;
      check_forloop_overflow_error(&f_st);
    }

    for (k = 2; k <= vlen; k++) {
      y += x->data[k - 1];
    }
  }

  y /= (real_T)(x->size[0] * x->size[1]);
  return y;
}

static void power(const emlrtStack *sp, const emxArray_real_T *a,
                  emxArray_real_T *y)
{
  uint32_T unnamed_idx_0;
  uint32_T unnamed_idx_1;
  int32_T nx;
  int32_T k;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &hb_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  b_st.site = &ib_emlrtRSI;
  unnamed_idx_0 = (uint32_T)a->size[0];
  unnamed_idx_1 = (uint32_T)a->size[1];
  nx = y->size[0] * y->size[1];
  y->size[0] = (int32_T)unnamed_idx_0;
  y->size[1] = (int32_T)unnamed_idx_1;
  emxEnsureCapacity_real_T(&b_st, y, nx, &x_emlrtRTEI);
  c_st.site = &jb_emlrtRSI;
  nx = (int32_T)unnamed_idx_0 * (int32_T)unnamed_idx_1;
  d_st.site = &kb_emlrtRSI;
  if ((1 <= nx) && (nx > 2147483646)) {
    e_st.site = &eb_emlrtRSI;
    check_forloop_overflow_error(&e_st);
  }

  for (k = 0; k < nx; k++) {
    y->data[k] = a->data[k] * a->data[k];
  }
}

static void sum(const emlrtStack *sp, const emxArray_real_T *x, emxArray_real_T *
                y)
{
  boolean_T overflow;
  int32_T vlen;
  uint32_T sz_idx_1;
  int32_T npages;
  int32_T xpageoffset;
  int32_T i;
  int32_T k;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &ab_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  if (((x->size[0] == 1) && (x->size[1] == 1)) || (x->size[0] != 1)) {
  } else {
    emlrtErrorWithMessageIdR2018a(&st, &hb_emlrtRTEI,
      "Coder:toolbox:autoDimIncompatibility",
      "Coder:toolbox:autoDimIncompatibility", 0);
  }

  overflow = false;
  if ((x->size[0] != 0) || (x->size[1] != 0)) {
  } else {
    overflow = true;
  }

  if (overflow) {
    emlrtErrorWithMessageIdR2018a(&st, &jb_emlrtRTEI,
      "Coder:toolbox:UnsupportedSpecialEmpty",
      "Coder:toolbox:UnsupportedSpecialEmpty", 0);
  }

  b_st.site = &bb_emlrtRSI;
  vlen = x->size[0];
  if ((x->size[0] == 0) || (x->size[1] == 0)) {
    sz_idx_1 = (uint32_T)x->size[1];
    xpageoffset = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int32_T)sz_idx_1;
    emxEnsureCapacity_real_T(&b_st, y, xpageoffset, &y_emlrtRTEI);
    i = (int32_T)sz_idx_1;
    for (xpageoffset = 0; xpageoffset < i; xpageoffset++) {
      y->data[xpageoffset] = 0.0;
    }
  } else {
    c_st.site = &cb_emlrtRSI;
    npages = x->size[1];
    xpageoffset = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = x->size[1];
    emxEnsureCapacity_real_T(&c_st, y, xpageoffset, &ab_emlrtRTEI);
    d_st.site = &lb_emlrtRSI;
    overflow = (x->size[1] > 2147483646);
    if (overflow) {
      e_st.site = &eb_emlrtRSI;
      check_forloop_overflow_error(&e_st);
    }

    for (i = 0; i < npages; i++) {
      xpageoffset = i * x->size[0];
      y->data[i] = x->data[xpageoffset];
      d_st.site = &db_emlrtRSI;
      if ((2 <= vlen) && (vlen > 2147483646)) {
        e_st.site = &eb_emlrtRSI;
        check_forloop_overflow_error(&e_st);
      }

      for (k = 2; k <= vlen; k++) {
        y->data[i] += x->data[(xpageoffset + k) - 1];
      }
    }
  }
}

static void tic(const emlrtStack *sp)
{
  int32_T status;
  emlrtTimespec b_timespec;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &u_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  b_st.site = &v_emlrtRSI;
  status = emlrtClockGettimeMonotonic(&b_timespec);
  c_st.site = &w_emlrtRSI;
  if (status != 0) {
    emlrtErrorWithMessageIdR2018a(&c_st, &gb_emlrtRTEI,
      "Coder:toolbox:POSIXCallFailed", "Coder:toolbox:POSIXCallFailed", 5, 4, 26,
      cv0, 12, status);
  }

  st.site = &u_emlrtRSI;
  timeKeeper(&st, b_timespec.tv_sec, b_timespec.tv_nsec);
}

static void timeKeeper(const emlrtStack *sp, real_T newTime_tv_sec, real_T
  newTime_tv_nsec)
{
  int32_T status;
  emlrtTimespec b_timespec;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  if (!savedTime_not_empty) {
    st.site = &x_emlrtRSI;
    b_st.site = &v_emlrtRSI;
    status = emlrtClockGettimeMonotonic(&b_timespec);
    c_st.site = &w_emlrtRSI;
    if (status != 0) {
      emlrtErrorWithMessageIdR2018a(&c_st, &gb_emlrtRTEI,
        "Coder:toolbox:POSIXCallFailed", "Coder:toolbox:POSIXCallFailed", 5, 4,
        26, cv0, 12, status);
    }

    savedTime.tv_sec = b_timespec.tv_sec;
    savedTime.tv_nsec = b_timespec.tv_nsec;
    savedTime_not_empty = true;
  }

  savedTime.tv_sec = newTime_tv_sec;
  savedTime.tv_nsec = newTime_tv_nsec;
}

static real_T toc(const emlrtStack *sp)
{
  real_T tstart_tv_sec;
  real_T tstart_tv_nsec;
  int32_T status;
  emlrtTimespec b_timespec;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &mb_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  b_timeKeeper(&st, &tstart_tv_sec, &tstart_tv_nsec);
  st.site = &nb_emlrtRSI;
  b_st.site = &v_emlrtRSI;
  status = emlrtClockGettimeMonotonic(&b_timespec);
  c_st.site = &w_emlrtRSI;
  if (status != 0) {
    emlrtErrorWithMessageIdR2018a(&c_st, &gb_emlrtRTEI,
      "Coder:toolbox:POSIXCallFailed", "Coder:toolbox:POSIXCallFailed", 5, 4, 26,
      cv0, 12, status);
  }

  return (b_timespec.tv_sec - tstart_tv_sec) + (b_timespec.tv_nsec -
    tstart_tv_nsec) / 1.0E+9;
}

void denseMatch(const emlrtStack *sp, const emxArray_uint8_T *rightImage, const
                emxArray_uint8_T *leftImage, real_T corrWindowSize, real_T dMin,
                real_T dMax, const emxArray_char_T *method, emxArray_real_T
                *dispMap, real_T *timeTaken)
{
  emxArray_real_T *b_leftImage;
  const mxArray *y;
  const mxArray *m0;
  static const int32_T iv0[2] = { 1, 74 };

  int32_T i0;
  static const char_T varargin_1[74] = { 'B', 'o', 't', 'h', ' ', 'l', 'e', 'f',
    't', ' ', 'a', 'n', 'd', ' ', 'r', 'i', 'g', 'h', 't', ' ', 'i', 'm', 'a',
    'g', 'e', 's', ' ', 's', 'h', 'o', 'u', 'l', 'd', ' ', 'h', 'a', 'v', 'e',
    ' ', 't', 'h', 'e', ' ', 's', 'a', 'm', 'e', ' ', 'n', 'u', 'm', 'b', 'e',
    'r', ' ', 'o', 'f', ' ', 'r', 'o', 'w', 's', ' ', 'a', 'n', 'd', ' ', 'c',
    'o', 'l', 'u', 'm', 'n', 's' };

  int32_T loop_ub;
  emxArray_real_T *b_rightImage;
  const mxArray *m1;
  static const int32_T iv1[2] = { 1, 38 };

  static const char_T b_varargin_1[38] = { 'T', 'h', 'e', ' ', 'w', 'i', 'n',
    'd', 'o', 'w', ' ', 's', 'i', 'z', 'e', ' ', 'm', 'u', 's', 't', ' ', 'b',
    'e', ' ', 'a', 'n', ' ', 'o', 'd', 'd', ' ', 'n', 'u', 'm', 'b', 'e', 'r',
    '.' };

  const mxArray *m2;
  static const int32_T iv2[2] = { 1, 58 };

  static const char_T c_varargin_1[58] = { 'M', 'i', 'n', 'i', 'm', 'u', 'm',
    ' ', 'D', 'i', 's', 'p', 'a', 'r', 'i', 't', 'y', ' ', 'm', 'u', 's', 't',
    ' ', 'b', 'e', ' ', 'l', 'e', 's', 's', ' ', 't', 'h', 'a', 'n', ' ', 't',
    'h', 'e', ' ', 'M', 'a', 'x', 'i', 'm', 'u', 'm', ' ', 'd', 'i', 's', 'p',
    'a', 'r', 'i', 't', 'y', '.' };

  real_T win;
  int32_T maximize;
  real_T meanLeft;
  emxArray_real_T *tempCorrScore;
  emxArray_real_T *r0;
  emxArray_real_T *r1;
  emxArray_real_T *c_leftImage;
  int32_T i;
  real_T b_i;
  int32_T i1;
  int32_T j;
  real_T b_j;
  real_T prevcorrScore;
  int32_T i2;
  int32_T i3;
  int32_T i4;
  int32_T d;
  real_T b_d;
  real_T meanRight;
  int32_T i5;
  int32_T i6;
  int32_T i7;
  real_T den;
  real_T d0;
  int32_T i8;
  int32_T i9;
  int32_T b_loop_ub;
  int32_T i10;
  int32_T i11;
  int32_T c_loop_ub;
  int32_T d_loop_ub;
  int32_T e_loop_ub;
  uint32_T u0;
  uint32_T u1;
  boolean_T b_bool;
  int32_T iv3[2];
  int32_T exitg1;
  int32_T b_tempCorrScore[2];
  static const char_T cv1[3] = { 'S', 'A', 'D' };

  static const char_T cv2[4] = { 'Z', 'S', 'A', 'D' };

  static const char_T cv3[4] = { 'L', 'S', 'A', 'D' };

  static const char_T cv4[3] = { 'S', 'S', 'D' };

  static const char_T cv5[4] = { 'Z', 'S', 'S', 'D' };

  static const char_T cv6[4] = { 'L', 'S', 'S', 'D' };

  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &st;
  c_st.tls = st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b(sp);

  /*  ************************************************************************* */
  /*  Title: Function-Compute Correlation between two images using */
  /*  various  */
  /*  similarity measures with Left Image as reference. */
  /*  Author: Siddhant Ahuja */
  /*  Created: March 2010 */
  /*  Copyright Siddhant Ahuja, 2010 */
  /*  Inputs:  */
  /*  1. Left Image (var: rightImage),  */
  /*  2. Right Image (var: leftImage), */
  /*  3. Correlation Window Size (var: corrWindowSize),  */
  /*  4. Minimum Disparity in X-direction (var: dMin),  */
  /*  5. Maximum Disparity in X-direction (var: dMax), */
  /*  6. Method used for calculating the correlation scores (var: */
  /*  method) */
  /*  Valid values include: 'SAD', 'LSAD', 'ZSAD', 'SSD', 'LSSD', */
  /*  ZSSD', 'NCC', */
  /*  'ZNCC' */
  /*  Outputs:  */
  /*  1. Disparity Map (var: dispMap),  */
  /*  2. Time taken (var: timeTaken) */
  /*  Example Usage of Function: [dispMap, */
  /*  timeTaken]=denseMatch('tsukuba_left.tiff', 'tsukuba_right.tiff', */
  /*  9, 0, 16, 'ZNCC'); */
  /*  ************************************************************************* */
  /*  Find the size (columns and rows) of the left image and assign the */
  /*  rows to */
  /*  variable nrLeft, and columns to variable ncLeft */
  /*  Find the size (columns and rows) of the right image and assign */
  /*  the rows to */
  /*  variable nrRight, and columns to variable ncRight */
  /*  Check to see if both the left and right images have same number */
  /*  of rows */
  /*  and columns */
  if ((leftImage->size[0] == rightImage->size[0]) && (leftImage->size[1] ==
       rightImage->size[1])) {
  } else {
    st.site = &emlrtRSI;
    y = NULL;
    m0 = emlrtCreateCharArray(2, iv0);
    emlrtInitCharArrayR2013a(&st, 74, m0, &varargin_1[0]);
    emlrtAssign(&y, m0);
    b_st.site = &ob_emlrtRSI;
    error(&b_st, y, &emlrtMCI);
  }

  emxInit_real_T(sp, &b_leftImage, 2, &s_emlrtRTEI, true);

  /*  Convert the left and right images from uint8 to double */
  i0 = b_leftImage->size[0] * b_leftImage->size[1];
  b_leftImage->size[0] = leftImage->size[0];
  b_leftImage->size[1] = leftImage->size[1];
  emxEnsureCapacity_real_T(sp, b_leftImage, i0, &emlrtRTEI);
  loop_ub = leftImage->size[0] * leftImage->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_leftImage->data[i0] = (real_T)leftImage->data[i0] / 255.0;
  }

  emxInit_real_T(sp, &b_rightImage, 2, &t_emlrtRTEI, true);
  i0 = b_rightImage->size[0] * b_rightImage->size[1];
  b_rightImage->size[0] = rightImage->size[0];
  b_rightImage->size[1] = rightImage->size[1];
  emxEnsureCapacity_real_T(sp, b_rightImage, i0, &b_emlrtRTEI);
  loop_ub = rightImage->size[0] * rightImage->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_rightImage->data[i0] = (real_T)rightImage->data[i0] / 255.0;
  }

  /*  Check the size of window to see if it is an odd number. */
  if (b_mod(corrWindowSize) == 0.0) {
    st.site = &b_emlrtRSI;
    y = NULL;
    m1 = emlrtCreateCharArray(2, iv1);
    emlrtInitCharArrayR2013a(&st, 38, m1, &b_varargin_1[0]);
    emlrtAssign(&y, m1);
    b_st.site = &ob_emlrtRSI;
    error(&b_st, y, &emlrtMCI);
  }

  /*  Check whether minimum disparity is less than the maximum */
  /*  disparity. */
  if (dMin > dMax) {
    st.site = &c_emlrtRSI;
    y = NULL;
    m2 = emlrtCreateCharArray(2, iv2);
    emlrtInitCharArrayR2013a(&st, 58, m2, &c_varargin_1[0]);
    emlrtAssign(&y, m2);
    b_st.site = &ob_emlrtRSI;
    error(&b_st, y, &emlrtMCI);
  }

  /*  Create an image of size nrLeft and ncLeft, fill it with zeros and */
  /*  assign */
  /*  it to variable dispMap */
  i0 = dispMap->size[0] * dispMap->size[1];
  dispMap->size[0] = leftImage->size[0];
  dispMap->size[1] = leftImage->size[1];
  emxEnsureCapacity_real_T(sp, dispMap, i0, &c_emlrtRTEI);
  loop_ub = leftImage->size[0] * leftImage->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    dispMap->data[i0] = 0.0;
  }

  /*  Find out how many rows and columns are to the left/right/up/down */
  /*  of the */
  /*  central pixel based on the window size */
  win = (corrWindowSize - 1.0) / 2.0;

  /*  The objective of CC, NCC and ZNCC is to maxmize the */
  /*  correlation score, whereas other methods try to minimize */
  /*  it. */
  maximize = 0;
  if (b_strcmp(method) || c_strcmp(method)) {
    maximize = 1;
  }

  st.site = &d_emlrtRSI;
  tic(&st);

  /*  Initialize the timer to calculate the time consumed. */
  meanLeft = (real_T)leftImage->size[0] - win;
  i0 = (int32_T)(meanLeft + (1.0 - (1.0 + win)));
  emlrtForLoopVectorCheckR2012b(1.0 + win, 1.0, meanLeft, mxDOUBLE_CLASS, i0,
    &fb_emlrtRTEI, sp);
  emxInit_real_T(sp, &tempCorrScore, 2, &f_emlrtRTEI, true);
  emxInit_real_T(sp, &r0, 2, &u_emlrtRTEI, true);
  emxInit_real_T(sp, &r1, 2, &v_emlrtRTEI, true);
  emxInit_real_T(sp, &c_leftImage, 2, &d_emlrtRTEI, true);
  for (i = 0; i < i0; i++) {
    b_i = (1.0 + win) + (real_T)i;

    /*  For every row in Left Image */
    meanLeft = ((real_T)leftImage->size[1] - win) - dMax;
    i1 = (int32_T)(meanLeft + (1.0 - (1.0 + win)));
    emlrtForLoopVectorCheckR2012b(1.0 + win, 1.0, meanLeft, mxDOUBLE_CLASS, i1,
      &eb_emlrtRTEI, sp);
    for (j = 0; j < i1; j++) {
      b_j = (1.0 + win) + (real_T)j;

      /*  For every column in Left Image */
      /*  Initialize the temporary variable to hold the previous */
      /*  correlation score */
      st.site = &e_emlrtRSI;
      if (maximize != 0) {
        prevcorrScore = 0.0;
      } else {
        prevcorrScore = 65532.0;
      }

      /*  Initialize the temporary variable to store the best */
      /*  matched */
      /*  disparity score */
      i2 = dispMap->size[0];
      if (b_i != (int32_T)muDoubleScalarFloor(b_i)) {
        emlrtIntegerCheckR2012b(b_i, &i_emlrtDCI, sp);
      }

      i3 = (int32_T)b_i;
      if ((i3 < 1) || (i3 > i2)) {
        emlrtDynamicBoundsCheckR2012b(i3, 1, i2, &i_emlrtBCI, sp);
      }

      i2 = dispMap->size[1];
      if (b_j != (int32_T)muDoubleScalarFloor(b_j)) {
        emlrtIntegerCheckR2012b(b_j, &i_emlrtDCI, sp);
      }

      i4 = (int32_T)b_j;
      if ((i4 < 1) || (i4 > i2)) {
        emlrtDynamicBoundsCheckR2012b(i4, 1, i2, &i_emlrtBCI, sp);
      }

      dispMap->data[(i3 + dispMap->size[0] * (i4 - 1)) - 1] = dMin;
      i2 = (int32_T)(dMax + (1.0 - dMin));
      emlrtForLoopVectorCheckR2012b(dMin, 1.0, dMax, mxDOUBLE_CLASS, i2,
        &db_emlrtRTEI, sp);
      for (d = 0; d < i2; d++) {
        b_d = dMin + (real_T)d;

        /*  For every disparity value in x-direction */
        /*  Construct a region with window around */
        /*  central/selected pixel in left image */
        meanLeft = b_i - win;
        meanRight = b_i + win;
        if (meanLeft > meanRight) {
          i5 = 0;
          i6 = 0;
        } else {
          i5 = b_leftImage->size[0];
          if (meanLeft != (int32_T)muDoubleScalarFloor(meanLeft)) {
            emlrtIntegerCheckR2012b(meanLeft, &h_emlrtDCI, sp);
          }

          i7 = (int32_T)meanLeft;
          if ((i7 < 1) || (i7 > i5)) {
            emlrtDynamicBoundsCheckR2012b(i7, 1, i5, &h_emlrtBCI, sp);
          }

          i5 = i7 - 1;
          i7 = b_leftImage->size[0];
          if (meanRight != (int32_T)muDoubleScalarFloor(meanRight)) {
            emlrtIntegerCheckR2012b(meanRight, &g_emlrtDCI, sp);
          }

          i6 = (int32_T)meanRight;
          if ((i6 < 1) || (i6 > i7)) {
            emlrtDynamicBoundsCheckR2012b(i6, 1, i7, &g_emlrtBCI, sp);
          }
        }

        den = b_j - win;
        d0 = b_j + win;
        if (den > d0) {
          i7 = 0;
          i8 = 0;
        } else {
          i7 = b_leftImage->size[1];
          if (den != (int32_T)muDoubleScalarFloor(den)) {
            emlrtIntegerCheckR2012b(den, &f_emlrtDCI, sp);
          }

          i9 = (int32_T)den;
          if ((i9 < 1) || (i9 > i7)) {
            emlrtDynamicBoundsCheckR2012b(i9, 1, i7, &f_emlrtBCI, sp);
          }

          i7 = i9 - 1;
          i9 = b_leftImage->size[1];
          if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
            emlrtIntegerCheckR2012b(d0, &e_emlrtDCI, sp);
          }

          i8 = (int32_T)d0;
          if ((i8 < 1) || (i8 > i9)) {
            emlrtDynamicBoundsCheckR2012b(i8, 1, i9, &e_emlrtBCI, sp);
          }
        }

        /*  Construct a region with window around */
        /*  central/selected pixel in right image */
        if (meanLeft > meanRight) {
          i9 = 0;
          b_loop_ub = 0;
        } else {
          i9 = b_rightImage->size[0];
          if (meanLeft != (int32_T)muDoubleScalarFloor(meanLeft)) {
            emlrtIntegerCheckR2012b(meanLeft, &d_emlrtDCI, sp);
          }

          i10 = (int32_T)meanLeft;
          if ((i10 < 1) || (i10 > i9)) {
            emlrtDynamicBoundsCheckR2012b(i10, 1, i9, &d_emlrtBCI, sp);
          }

          i9 = i10 - 1;
          i10 = b_rightImage->size[0];
          if (meanRight != (int32_T)muDoubleScalarFloor(meanRight)) {
            emlrtIntegerCheckR2012b(meanRight, &c_emlrtDCI, sp);
          }

          b_loop_ub = (int32_T)meanRight;
          if ((b_loop_ub < 1) || (b_loop_ub > i10)) {
            emlrtDynamicBoundsCheckR2012b(b_loop_ub, 1, i10, &c_emlrtBCI, sp);
          }
        }

        meanLeft = b_j + b_d;
        meanRight = meanLeft - win;
        meanLeft += win;
        if (meanRight > meanLeft) {
          i10 = 0;
          i11 = 0;
        } else {
          i10 = b_rightImage->size[1];
          if (meanRight != (int32_T)muDoubleScalarFloor(meanRight)) {
            emlrtIntegerCheckR2012b(meanRight, &b_emlrtDCI, sp);
          }

          c_loop_ub = (int32_T)meanRight;
          if ((c_loop_ub < 1) || (c_loop_ub > i10)) {
            emlrtDynamicBoundsCheckR2012b(c_loop_ub, 1, i10, &b_emlrtBCI, sp);
          }

          i10 = c_loop_ub - 1;
          c_loop_ub = b_rightImage->size[1];
          if (meanLeft != (int32_T)muDoubleScalarFloor(meanLeft)) {
            emlrtIntegerCheckR2012b(meanLeft, &emlrtDCI, sp);
          }

          i11 = (int32_T)meanLeft;
          if ((i11 < 1) || (i11 > c_loop_ub)) {
            emlrtDynamicBoundsCheckR2012b(i11, 1, c_loop_ub, &emlrtBCI, sp);
          }
        }

        /*  Calculate the local mean in left region */
        c_loop_ub = c_leftImage->size[0] * c_leftImage->size[1];
        loop_ub = i6 - i5;
        c_leftImage->size[0] = loop_ub;
        d_loop_ub = i8 - i7;
        c_leftImage->size[1] = d_loop_ub;
        emxEnsureCapacity_real_T(sp, c_leftImage, c_loop_ub, &d_emlrtRTEI);
        for (i6 = 0; i6 < d_loop_ub; i6++) {
          for (i8 = 0; i8 < loop_ub; i8++) {
            c_leftImage->data[i8 + c_leftImage->size[0] * i6] =
              b_leftImage->data[(i5 + i8) + b_leftImage->size[0] * (i7 + i6)];
          }
        }

        st.site = &f_emlrtRSI;
        meanLeft = mean2(&st, c_leftImage);

        /*  Calculate the local mean in right region */
        i6 = c_leftImage->size[0] * c_leftImage->size[1];
        e_loop_ub = b_loop_ub - i9;
        c_leftImage->size[0] = e_loop_ub;
        c_loop_ub = i11 - i10;
        c_leftImage->size[1] = c_loop_ub;
        emxEnsureCapacity_real_T(sp, c_leftImage, i6, &e_emlrtRTEI);
        for (i6 = 0; i6 < c_loop_ub; i6++) {
          for (i8 = 0; i8 < e_loop_ub; i8++) {
            c_leftImage->data[i8 + c_leftImage->size[0] * i6] =
              b_rightImage->data[(i9 + i8) + b_rightImage->size[0] * (i10 + i6)];
          }
        }

        st.site = &g_emlrtRSI;
        meanRight = mean2(&st, c_leftImage);

        /*  Initialize the variable to store temporarily the */
        /*  correlation scores */
        u0 = (uint32_T)loop_ub;
        u1 = (uint32_T)d_loop_ub;
        i6 = tempCorrScore->size[0] * tempCorrScore->size[1];
        tempCorrScore->size[0] = (int32_T)u0;
        tempCorrScore->size[1] = (int32_T)u1;
        emxEnsureCapacity_real_T(sp, tempCorrScore, i6, &f_emlrtRTEI);
        b_loop_ub = (int32_T)u0 * (int32_T)u1;
        for (i6 = 0; i6 < b_loop_ub; i6++) {
          tempCorrScore->data[i6] = 0.0;
        }

        /*  Calculate the correlation score */
        b_bool = false;
        if (method->size[1] == 3) {
          b_loop_ub = 0;
          do {
            exitg1 = 0;
            if (b_loop_ub < 3) {
              if (method->data[b_loop_ub] != cv1[b_loop_ub]) {
                exitg1 = 1;
              } else {
                b_loop_ub++;
              }
            } else {
              b_bool = true;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }

        if (b_bool) {
          iv3[0] = loop_ub;
          iv3[1] = d_loop_ub;
          b_tempCorrScore[0] = e_loop_ub;
          b_tempCorrScore[1] = c_loop_ub;
          if ((loop_ub != e_loop_ub) || (d_loop_ub != c_loop_ub)) {
            emlrtSizeEqCheckNDR2012b(&iv3[0], &b_tempCorrScore[0], &h_emlrtECI,
              sp);
          }

          i6 = c_leftImage->size[0] * c_leftImage->size[1];
          c_leftImage->size[0] = loop_ub;
          c_leftImage->size[1] = d_loop_ub;
          emxEnsureCapacity_real_T(sp, c_leftImage, i6, &g_emlrtRTEI);
          for (i6 = 0; i6 < d_loop_ub; i6++) {
            for (i8 = 0; i8 < loop_ub; i8++) {
              c_leftImage->data[i8 + c_leftImage->size[0] * i6] =
                b_leftImage->data[(i5 + i8) + b_leftImage->size[0] * (i7 + i6)]
                - b_rightImage->data[(i9 + i8) + b_rightImage->size[0] * (i10 +
                i6)];
            }
          }

          st.site = &h_emlrtRSI;
          b_abs(&st, c_leftImage, tempCorrScore);
        } else {
          b_bool = false;
          if (method->size[1] == 4) {
            b_loop_ub = 0;
            do {
              exitg1 = 0;
              if (b_loop_ub < 4) {
                if (method->data[b_loop_ub] != cv2[b_loop_ub]) {
                  exitg1 = 1;
                } else {
                  b_loop_ub++;
                }
              } else {
                b_bool = true;
                exitg1 = 1;
              }
            } while (exitg1 == 0);
          }

          if (b_bool) {
            iv3[0] = loop_ub;
            iv3[1] = d_loop_ub;
            b_tempCorrScore[0] = e_loop_ub;
            b_tempCorrScore[1] = c_loop_ub;
            if ((loop_ub != e_loop_ub) || (d_loop_ub != c_loop_ub)) {
              emlrtSizeEqCheckNDR2012b(&iv3[0], &b_tempCorrScore[0], &g_emlrtECI,
                sp);
            }

            i6 = c_leftImage->size[0] * c_leftImage->size[1];
            c_leftImage->size[0] = loop_ub;
            c_leftImage->size[1] = d_loop_ub;
            emxEnsureCapacity_real_T(sp, c_leftImage, i6, &i_emlrtRTEI);
            for (i6 = 0; i6 < d_loop_ub; i6++) {
              for (i8 = 0; i8 < loop_ub; i8++) {
                c_leftImage->data[i8 + c_leftImage->size[0] * i6] =
                  ((b_leftImage->data[(i5 + i8) + b_leftImage->size[0] * (i7 +
                     i6)] - meanLeft) - b_rightImage->data[(i9 + i8) +
                   b_rightImage->size[0] * (i10 + i6)]) + meanRight;
              }
            }

            st.site = &i_emlrtRSI;
            b_abs(&st, c_leftImage, tempCorrScore);
          } else {
            b_bool = false;
            if (method->size[1] == 4) {
              b_loop_ub = 0;
              do {
                exitg1 = 0;
                if (b_loop_ub < 4) {
                  if (method->data[b_loop_ub] != cv3[b_loop_ub]) {
                    exitg1 = 1;
                  } else {
                    b_loop_ub++;
                  }
                } else {
                  b_bool = true;
                  exitg1 = 1;
                }
              } while (exitg1 == 0);
            }

            if (b_bool) {
              meanLeft /= meanRight;
              i6 = tempCorrScore->size[0] * tempCorrScore->size[1];
              tempCorrScore->size[0] = e_loop_ub;
              tempCorrScore->size[1] = c_loop_ub;
              emxEnsureCapacity_real_T(sp, tempCorrScore, i6, &h_emlrtRTEI);
              for (i6 = 0; i6 < c_loop_ub; i6++) {
                for (i8 = 0; i8 < e_loop_ub; i8++) {
                  tempCorrScore->data[i8 + tempCorrScore->size[0] * i6] =
                    meanLeft * b_rightImage->data[(i9 + i8) + b_rightImage->
                    size[0] * (i10 + i6)];
                }
              }

              iv3[0] = loop_ub;
              iv3[1] = d_loop_ub;
              b_tempCorrScore[0] = tempCorrScore->size[0];
              b_tempCorrScore[1] = tempCorrScore->size[1];
              if ((loop_ub != b_tempCorrScore[0]) || (d_loop_ub !=
                   b_tempCorrScore[1])) {
                emlrtSizeEqCheckNDR2012b(&iv3[0], &b_tempCorrScore[0],
                  &f_emlrtECI, sp);
              }

              i6 = c_leftImage->size[0] * c_leftImage->size[1];
              c_leftImage->size[0] = loop_ub;
              c_leftImage->size[1] = d_loop_ub;
              emxEnsureCapacity_real_T(sp, c_leftImage, i6, &l_emlrtRTEI);
              for (i6 = 0; i6 < d_loop_ub; i6++) {
                for (i9 = 0; i9 < loop_ub; i9++) {
                  c_leftImage->data[i9 + c_leftImage->size[0] * i6] =
                    b_leftImage->data[(i5 + i9) + b_leftImage->size[0] * (i7 +
                    i6)] - tempCorrScore->data[i9 + tempCorrScore->size[0] * i6];
                }
              }

              st.site = &j_emlrtRSI;
              b_abs(&st, c_leftImage, tempCorrScore);
            } else {
              b_bool = false;
              if (method->size[1] == 3) {
                b_loop_ub = 0;
                do {
                  exitg1 = 0;
                  if (b_loop_ub < 3) {
                    if (method->data[b_loop_ub] != cv4[b_loop_ub]) {
                      exitg1 = 1;
                    } else {
                      b_loop_ub++;
                    }
                  } else {
                    b_bool = true;
                    exitg1 = 1;
                  }
                } while (exitg1 == 0);
              }

              if (b_bool) {
                iv3[0] = loop_ub;
                iv3[1] = d_loop_ub;
                b_tempCorrScore[0] = e_loop_ub;
                b_tempCorrScore[1] = c_loop_ub;
                if ((loop_ub != e_loop_ub) || (d_loop_ub != c_loop_ub)) {
                  emlrtSizeEqCheckNDR2012b(&iv3[0], &b_tempCorrScore[0],
                    &e_emlrtECI, sp);
                }

                i6 = c_leftImage->size[0] * c_leftImage->size[1];
                c_leftImage->size[0] = loop_ub;
                c_leftImage->size[1] = d_loop_ub;
                emxEnsureCapacity_real_T(sp, c_leftImage, i6, &j_emlrtRTEI);
                for (i6 = 0; i6 < d_loop_ub; i6++) {
                  for (i8 = 0; i8 < loop_ub; i8++) {
                    c_leftImage->data[i8 + c_leftImage->size[0] * i6] =
                      b_leftImage->data[(i5 + i8) + b_leftImage->size[0] * (i7 +
                      i6)] - b_rightImage->data[(i9 + i8) + b_rightImage->size[0]
                      * (i10 + i6)];
                  }
                }

                st.site = &k_emlrtRSI;
                power(&st, c_leftImage, tempCorrScore);
              } else {
                b_bool = false;
                if (method->size[1] == 4) {
                  b_loop_ub = 0;
                  do {
                    exitg1 = 0;
                    if (b_loop_ub < 4) {
                      if (method->data[b_loop_ub] != cv5[b_loop_ub]) {
                        exitg1 = 1;
                      } else {
                        b_loop_ub++;
                      }
                    } else {
                      b_bool = true;
                      exitg1 = 1;
                    }
                  } while (exitg1 == 0);
                }

                if (b_bool) {
                  iv3[0] = loop_ub;
                  iv3[1] = d_loop_ub;
                  b_tempCorrScore[0] = e_loop_ub;
                  b_tempCorrScore[1] = c_loop_ub;
                  if ((loop_ub != e_loop_ub) || (d_loop_ub != c_loop_ub)) {
                    emlrtSizeEqCheckNDR2012b(&iv3[0], &b_tempCorrScore[0],
                      &d_emlrtECI, sp);
                  }

                  i6 = c_leftImage->size[0] * c_leftImage->size[1];
                  c_leftImage->size[0] = loop_ub;
                  c_leftImage->size[1] = d_loop_ub;
                  emxEnsureCapacity_real_T(sp, c_leftImage, i6, &n_emlrtRTEI);
                  for (i6 = 0; i6 < d_loop_ub; i6++) {
                    for (i8 = 0; i8 < loop_ub; i8++) {
                      c_leftImage->data[i8 + c_leftImage->size[0] * i6] =
                        ((b_leftImage->data[(i5 + i8) + b_leftImage->size[0] *
                          (i7 + i6)] - meanLeft) - b_rightImage->data[(i9 + i8)
                         + b_rightImage->size[0] * (i10 + i6)]) + meanRight;
                    }
                  }

                  st.site = &l_emlrtRSI;
                  power(&st, c_leftImage, tempCorrScore);
                } else {
                  b_bool = false;
                  if (method->size[1] == 4) {
                    b_loop_ub = 0;
                    do {
                      exitg1 = 0;
                      if (b_loop_ub < 4) {
                        if (method->data[b_loop_ub] != cv6[b_loop_ub]) {
                          exitg1 = 1;
                        } else {
                          b_loop_ub++;
                        }
                      } else {
                        b_bool = true;
                        exitg1 = 1;
                      }
                    } while (exitg1 == 0);
                  }

                  if (b_bool) {
                    meanLeft /= meanRight;
                    i6 = tempCorrScore->size[0] * tempCorrScore->size[1];
                    tempCorrScore->size[0] = e_loop_ub;
                    tempCorrScore->size[1] = c_loop_ub;
                    emxEnsureCapacity_real_T(sp, tempCorrScore, i6, &k_emlrtRTEI);
                    for (i6 = 0; i6 < c_loop_ub; i6++) {
                      for (i8 = 0; i8 < e_loop_ub; i8++) {
                        tempCorrScore->data[i8 + tempCorrScore->size[0] * i6] =
                          meanLeft * b_rightImage->data[(i9 + i8) +
                          b_rightImage->size[0] * (i10 + i6)];
                      }
                    }

                    iv3[0] = loop_ub;
                    iv3[1] = d_loop_ub;
                    b_tempCorrScore[0] = tempCorrScore->size[0];
                    b_tempCorrScore[1] = tempCorrScore->size[1];
                    if ((loop_ub != b_tempCorrScore[0]) || (d_loop_ub !=
                         b_tempCorrScore[1])) {
                      emlrtSizeEqCheckNDR2012b(&iv3[0], &b_tempCorrScore[0],
                        &c_emlrtECI, sp);
                    }

                    i6 = c_leftImage->size[0] * c_leftImage->size[1];
                    c_leftImage->size[0] = loop_ub;
                    c_leftImage->size[1] = d_loop_ub;
                    emxEnsureCapacity_real_T(sp, c_leftImage, i6, &p_emlrtRTEI);
                    for (i6 = 0; i6 < d_loop_ub; i6++) {
                      for (i9 = 0; i9 < loop_ub; i9++) {
                        c_leftImage->data[i9 + c_leftImage->size[0] * i6] =
                          b_leftImage->data[(i5 + i9) + b_leftImage->size[0] *
                          (i7 + i6)] - tempCorrScore->data[i9 +
                          tempCorrScore->size[0] * i6];
                      }
                    }

                    st.site = &m_emlrtRSI;
                    power(&st, c_leftImage, tempCorrScore);
                  } else if (b_strcmp(method)) {
                    /*  Calculate the term in the denominator (var: den) */
                    i6 = c_leftImage->size[0] * c_leftImage->size[1];
                    c_leftImage->size[0] = loop_ub;
                    c_leftImage->size[1] = d_loop_ub;
                    emxEnsureCapacity_real_T(sp, c_leftImage, i6, &d_emlrtRTEI);
                    for (i6 = 0; i6 < d_loop_ub; i6++) {
                      for (i8 = 0; i8 < loop_ub; i8++) {
                        c_leftImage->data[i8 + c_leftImage->size[0] * i6] =
                          b_leftImage->data[(i5 + i8) + b_leftImage->size[0] *
                          (i7 + i6)];
                      }
                    }

                    st.site = &n_emlrtRSI;
                    power(&st, c_leftImage, tempCorrScore);
                    st.site = &n_emlrtRSI;
                    sum(&st, tempCorrScore, r0);
                    i6 = c_leftImage->size[0] * c_leftImage->size[1];
                    c_leftImage->size[0] = e_loop_ub;
                    c_leftImage->size[1] = c_loop_ub;
                    emxEnsureCapacity_real_T(sp, c_leftImage, i6, &e_emlrtRTEI);
                    for (i6 = 0; i6 < c_loop_ub; i6++) {
                      for (i8 = 0; i8 < e_loop_ub; i8++) {
                        c_leftImage->data[i8 + c_leftImage->size[0] * i6] =
                          b_rightImage->data[(i9 + i8) + b_rightImage->size[0] *
                          (i10 + i6)];
                      }
                    }

                    st.site = &o_emlrtRSI;
                    power(&st, c_leftImage, tempCorrScore);
                    st.site = &o_emlrtRSI;
                    sum(&st, tempCorrScore, r1);
                    st.site = &n_emlrtRSI;
                    b_st.site = &n_emlrtRSI;
                    c_st.site = &o_emlrtRSI;
                    den = b_sum(&b_st, r0) * b_sum(&c_st, r1);
                    if (den < 0.0) {
                      emlrtErrorWithMessageIdR2018a(&st, &cb_emlrtRTEI,
                        "Coder:toolbox:ElFunDomainError",
                        "Coder:toolbox:ElFunDomainError", 3, 4, 4, "sqrt");
                    }

                    den = muDoubleScalarSqrt(den);
                    iv3[0] = loop_ub;
                    iv3[1] = d_loop_ub;
                    b_tempCorrScore[0] = e_loop_ub;
                    b_tempCorrScore[1] = c_loop_ub;
                    if ((loop_ub != e_loop_ub) || (d_loop_ub != c_loop_ub)) {
                      emlrtSizeEqCheckNDR2012b(&iv3[0], &b_tempCorrScore[0],
                        &b_emlrtECI, sp);
                    }

                    i6 = tempCorrScore->size[0] * tempCorrScore->size[1];
                    tempCorrScore->size[0] = loop_ub;
                    tempCorrScore->size[1] = d_loop_ub;
                    emxEnsureCapacity_real_T(sp, tempCorrScore, i6, &q_emlrtRTEI);
                    for (i6 = 0; i6 < d_loop_ub; i6++) {
                      for (i8 = 0; i8 < loop_ub; i8++) {
                        tempCorrScore->data[i8 + tempCorrScore->size[0] * i6] =
                          b_leftImage->data[(i5 + i8) + b_leftImage->size[0] *
                          (i7 + i6)] * b_rightImage->data[(i9 + i8) +
                          b_rightImage->size[0] * (i10 + i6)] / den;
                      }
                    }
                  } else {
                    if (c_strcmp(method)) {
                      /*  Calculate the term in the denominator (var: den) */
                      i6 = c_leftImage->size[0] * c_leftImage->size[1];
                      c_leftImage->size[0] = loop_ub;
                      c_leftImage->size[1] = d_loop_ub;
                      emxEnsureCapacity_real_T(sp, c_leftImage, i6, &m_emlrtRTEI);
                      for (i6 = 0; i6 < d_loop_ub; i6++) {
                        for (i8 = 0; i8 < loop_ub; i8++) {
                          c_leftImage->data[i8 + c_leftImage->size[0] * i6] =
                            b_leftImage->data[(i5 + i8) + b_leftImage->size[0] *
                            (i7 + i6)] - meanLeft;
                        }
                      }

                      st.site = &p_emlrtRSI;
                      power(&st, c_leftImage, tempCorrScore);
                      st.site = &p_emlrtRSI;
                      sum(&st, tempCorrScore, r0);
                      i6 = c_leftImage->size[0] * c_leftImage->size[1];
                      c_leftImage->size[0] = e_loop_ub;
                      c_leftImage->size[1] = c_loop_ub;
                      emxEnsureCapacity_real_T(sp, c_leftImage, i6, &o_emlrtRTEI);
                      for (i6 = 0; i6 < c_loop_ub; i6++) {
                        for (i8 = 0; i8 < e_loop_ub; i8++) {
                          c_leftImage->data[i8 + c_leftImage->size[0] * i6] =
                            b_rightImage->data[(i9 + i8) + b_rightImage->size[0]
                            * (i10 + i6)] - meanRight;
                        }
                      }

                      st.site = &q_emlrtRSI;
                      power(&st, c_leftImage, tempCorrScore);
                      st.site = &q_emlrtRSI;
                      sum(&st, tempCorrScore, r1);
                      st.site = &p_emlrtRSI;
                      b_st.site = &p_emlrtRSI;
                      c_st.site = &q_emlrtRSI;
                      den = b_sum(&b_st, r0) * b_sum(&c_st, r1);
                      if (den < 0.0) {
                        emlrtErrorWithMessageIdR2018a(&st, &cb_emlrtRTEI,
                          "Coder:toolbox:ElFunDomainError",
                          "Coder:toolbox:ElFunDomainError", 3, 4, 4, "sqrt");
                      }

                      den = muDoubleScalarSqrt(den);
                      iv3[0] = loop_ub;
                      iv3[1] = d_loop_ub;
                      b_tempCorrScore[0] = e_loop_ub;
                      b_tempCorrScore[1] = c_loop_ub;
                      if ((loop_ub != e_loop_ub) || (d_loop_ub != c_loop_ub)) {
                        emlrtSizeEqCheckNDR2012b(&iv3[0], &b_tempCorrScore[0],
                          &emlrtECI, sp);
                      }

                      i6 = tempCorrScore->size[0] * tempCorrScore->size[1];
                      tempCorrScore->size[0] = loop_ub;
                      tempCorrScore->size[1] = d_loop_ub;
                      emxEnsureCapacity_real_T(sp, tempCorrScore, i6,
                        &r_emlrtRTEI);
                      for (i6 = 0; i6 < d_loop_ub; i6++) {
                        for (i8 = 0; i8 < loop_ub; i8++) {
                          tempCorrScore->data[i8 + tempCorrScore->size[0] * i6] =
                            (b_leftImage->data[(i5 + i8) + b_leftImage->size[0] *
                             (i7 + i6)] - meanLeft) * (b_rightImage->data[(i9 +
                            i8) + b_rightImage->size[0] * (i10 + i6)] -
                            meanRight) / den;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }

        /*  Compute the final score by summing the values in */
        /*  tempCorrScore, */
        /*  and store it in a temporary variable signifying the */
        /*  distance */
        /*  (var: corrScore) */
        st.site = &r_emlrtRSI;
        sum(&st, tempCorrScore, r0);
        st.site = &r_emlrtRSI;
        meanLeft = b_sum(&st, r0);
        st.site = &s_emlrtRSI;
        if (maximize != 0) {
          if (meanLeft > prevcorrScore) {
            /*  If the current disparity value is greater */
            /*  than */
            /*  previous one, then swap them */
            prevcorrScore = meanLeft;
            i5 = dispMap->size[0];
            if ((i3 < 1) || (i3 > i5)) {
              emlrtDynamicBoundsCheckR2012b(i3, 1, i5, &i_emlrtBCI, sp);
            }

            i5 = dispMap->size[1];
            if ((i4 < 1) || (i4 > i5)) {
              emlrtDynamicBoundsCheckR2012b(i4, 1, i5, &i_emlrtBCI, sp);
            }

            dispMap->data[(i3 + dispMap->size[0] * (i4 - 1)) - 1] = b_d;
          }
        } else {
          if (prevcorrScore > meanLeft) {
            /*  If the current disparity value is less than */
            /*  previous one, then swap them */
            prevcorrScore = meanLeft;
            i5 = dispMap->size[0];
            if ((i3 < 1) || (i3 > i5)) {
              emlrtDynamicBoundsCheckR2012b(i3, 1, i5, &i_emlrtBCI, sp);
            }

            i5 = dispMap->size[1];
            if ((i4 < 1) || (i4 > i5)) {
              emlrtDynamicBoundsCheckR2012b(i4, 1, i5, &i_emlrtBCI, sp);
            }

            dispMap->data[(i3 + dispMap->size[0] * (i4 - 1)) - 1] = b_d;
          }
        }

        if (*emlrtBreakCheckR2012bFlagVar != 0) {
          emlrtBreakCheckR2012b(sp);
        }
      }

      /*  Store the final matched value in variable dispMap */
      if (*emlrtBreakCheckR2012bFlagVar != 0) {
        emlrtBreakCheckR2012b(sp);
      }
    }

    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b(sp);
    }
  }

  emxFree_real_T(&c_leftImage);
  emxFree_real_T(&r1);
  emxFree_real_T(&r0);
  emxFree_real_T(&b_rightImage);
  emxFree_real_T(&b_leftImage);
  emxFree_real_T(&tempCorrScore);

  /*  Stop the timer to calculate the time consumed. */
  st.site = &t_emlrtRSI;
  *timeTaken = toc(&st);
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

void denseMatch_api(const mxArray * const prhs[6], int32_T nlhs, const mxArray
                    *plhs[2])
{
  emxArray_uint8_T *rightImage;
  emxArray_uint8_T *leftImage;
  emxArray_char_T *method;
  emxArray_real_T *dispMap;
  real_T corrWindowSize;
  real_T dMin;
  real_T dMax;
  real_T timeTaken;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInit_uint8_T(&st, &rightImage, 2, &bb_emlrtRTEI, true);
  emxInit_uint8_T(&st, &leftImage, 2, &bb_emlrtRTEI, true);
  emxInit_char_T(&st, &method, 2, &bb_emlrtRTEI, true);
  emxInit_real_T(&st, &dispMap, 2, &bb_emlrtRTEI, true);

  /* Marshall function inputs */
  rightImage->canFreeData = false;
  emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "rightImage", rightImage);
  leftImage->canFreeData = false;
  emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "leftImage", leftImage);
  corrWindowSize = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]),
    "corrWindowSize");
  dMin = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "dMin");
  dMax = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "dMax");
  e_emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "method", method);

  /* Invoke the target function */
  denseMatch(&st, rightImage, leftImage, corrWindowSize, dMin, dMax, method,
             dispMap, &timeTaken);

  /* Marshall function outputs */
  dispMap->canFreeData = false;
  plhs[0] = emlrt_marshallOut(dispMap);
  emxFree_real_T(&dispMap);
  emxFree_char_T(&method);
  emxFree_uint8_T(&leftImage);
  emxFree_uint8_T(&rightImage);
  if (nlhs > 1) {
    plhs[1] = b_emlrt_marshallOut(timeTaken);
  }

  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

void denseMatch_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void denseMatch_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  emlrtBreakCheckR2012bFlagVar = emlrtGetBreakCheckFlagAddressR2012b();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    denseMatch_once();
  }
}

void denseMatch_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

mxArray *emlrtMexFcnProperties(void)
{
  mxArray *xResult;
  mxArray *xEntryPoints;
  const char * fldNames[6] = { "Name", "NumberOfInputs", "NumberOfOutputs",
    "ConstantInputs", "FullPath", "TimeStamp" };

  mxArray *xInputs;
  const char * b_fldNames[4] = { "Version", "ResolvedFunctions", "EntryPoints",
    "CoverageInfo" };

  xEntryPoints = emlrtCreateStructMatrix(1, 1, 6, fldNames);
  xInputs = emlrtCreateLogicalMatrix(1, 6);
  emlrtSetField(xEntryPoints, 0, "Name", emlrtMxCreateString("denseMatch"));
  emlrtSetField(xEntryPoints, 0, "NumberOfInputs", emlrtMxCreateDoubleScalar(6.0));
  emlrtSetField(xEntryPoints, 0, "NumberOfOutputs", emlrtMxCreateDoubleScalar
                (2.0));
  emlrtSetField(xEntryPoints, 0, "ConstantInputs", xInputs);
  emlrtSetField(xEntryPoints, 0, "FullPath", emlrtMxCreateString(
    "C:\\SDXC\\Uni\\10. Semester (2. Master)\\Computer Vision\\AutoMEXGeneration\\denseMatch.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp", emlrtMxCreateDoubleScalar
                (737625.75631944439));
  xResult = emlrtCreateStructMatrix(1, 1, 4, b_fldNames);
  emlrtSetField(xResult, 0, "Version", emlrtMxCreateString(
    "9.6.0.1135713 (R2019a) Update 3"));
  emlrtSetField(xResult, 0, "ResolvedFunctions", (mxArray *)
                emlrtMexFcnResolvedFunctionsInfo());
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

const mxArray *emlrtMexFcnResolvedFunctionsInfo(void)
{
  const mxArray *nameCaptureInfo;
  const char * data[71] = {
    "789ced7d5d8c2bc9755e6ba5b5770dc8a22dc8fab17eee95169bddc899e17038c31919b2f93324871cfe7338c399bbbb334db249f6b0ffd8dde4700818a05f6c"
    "c3b06127828d3cc4800d3f58161c64f31249918050808004521e1c43910d05b183c47202c1d08300fb258012369b3d33ddb7eb4edfcb6291dd3c05dcad691eb2",
    "beeab3a7ce3975aaea14f59e54f63d1445fdf4e49f56537ffd92f65feafd945e7cb3fa25ca5cacf4f7cceaa1e5d9282f53ef33fdcea0ffab595d17059519a8fa"
    "03c70a4caec7d71879f220d03c73db4c43e4598116d4e31b89a1644611b93ed398529a2cc71cb33c9311ef3d1cb293073e718f74fba091b4bf636da6de29f778",
    "4a6e2b77dde5ee3f50f7f8f3957befbfbf1fba7dfff7d9f0e73edd78df13047f7c16fa93f8dbb1cf6d960faab1cd8ac06e6ef9371e95199e5154467ef44660e3"
    "5196d6fe7c733326f2524ffbf084555851d88cf454311baf261981916955fba4c1080a93a5d57a7b83bf7b8fc1bd7edec7ff099bf7b84f37fafd5ec47bbc3aab",
    "3f72ffc3512aacd771bda63261a31f97081c3b7edaf5e365443f7c330a23cba22645b8f0de6779bec3d329f536adc1dde27d714ebc43249e99fe2495a94e45a6"
    "208b2d99e61f69b2ad6c6623c7994874b314f06fedd39baa28723571b0c9f0dc26c7d636795ae5e8da26470badcd29a336f887f8e4543eacb5515ea55e99fd35",
    "fe6af2fcbb1172787a59173cd4f8762a773f87c0f359e874ae71d44a49c99beb067b3d481dd66a07fc59f4ae1f8507701eea07857826d5fe7d7d7ffff74ef9b8"
    "2afa5e42f4d3a9fcbd6479368aa1ef7df73f1c25c3fa1f87e187f09df2f155cb3365f99e4167f94043ecd538c3652065677aaca0ee51f8f47e1c8967a63f4939",
    "57fb3375cff2746bf29d5b4e696242524ffd3ffa8dff0a7a7f4178a4f47e6c2b14e0ae4bb1c390d0edd1295e8cf74ad749efe87d18bfe66292b751248c4bde3e"
    "6279a62cdf33e875b1c1c81b1325cbc802cd6d08b4dc62857abb33af7eb716543f8c62e08d5f10cf68ffad07f00cfa73f9f5ca64f2c13436a7bc9afdf7b3b3ca",
    "e0dce62de7a66243506e461ffc5ce93ba0f71784474aefdf0cae53fb74a2d9daf1d7f371b17c95e885aee3ded1fb63c4efdd3aae89c679a84f87f5faf559fd0b"
    "c4e23c4d4ec41ae7f909cbf31d9e4e31261906debb73e2a5907866fa3c711e866bf684cd29a77421a188eaab6f545e07bfdfedfa7faf1bca1f77b9839d4eb47d",
    "5c4c96d5eec1413de11dfd0fe3d8beff66b97b74abd74788f69cf2eb53083c9f856ef1ff5925da63393525e47a3c23b3f5a5e9fdff34275e1d8967a663f717ac"
    "1c9c49124139fa16f56388ffbbdd1e5c9f472bc3e1a01dca4bbd783c10abef94e83d0fc5ffc11ed8f7df2c77af61b3073f8fc0f359e8167ba0d4698e96378c59",
    "c0fcf3006b711a179a77bda8f2009e417f6e79d1fe3d65043eabf3ed9eec108c077de9f4a3301f70bbfeafb5770b5581531b65918ff784c3ed5a3c9af6d03a00"
    "e87ffbfea3f4ffef22da73caaf3711783e0bdda2ff6949e26eca536596e809756d213c251438ba6e5d0796e6ecdf071ee89f416fce7a71d1a685c664c2806bbe",
    "507b00dfa0e3b10f68b61a824650ce8aa73f80f982dbed45af108b0d42b1532977bcc38472eded6c26d48979c75ec0f8b67f2f67f2886fbde015cb3375fb3d9d"
    "c22a8a44cb0ae3d6f5821c12cf4c9fc7afd038a4791606afeeef27bb44f40f9f3c845ff9fc3ba0efddaeefaf4f534a82eb9c24024db9ccf5aff2696158047d0f",
    "fa7e5a363c17377a517b007123fbda28103722830771233cedc3fe517331cb5b14dbfed19f45e0f92cf43ecdb10d5a65685595d95a4f6566e7fb889d0b6338ee"
    "3edecaea7bebb9b0a719475adfffdefffc2acc03dcaeeff77387c162a3a9aae249afcf4462792177183df08ebe87f16c5f1bc52c7f596c7eff2710783e0bfda9",
    "fd4305514909aa3e17a2dcebf73b3e5f88c5ef37b38d6c3c88fa677f2f80dfef763b705a8f16622da520c80d85d9bf890612edfdce21d881351ccf93f2716c76"
    "e063083c9f85fe941db86f0428f7da813212cf4cc7253726a1a188ae0bbc0e76c0fd76a073ae9c1495c0712123270f6a4299976e72d71eda370ae3d9be360aea",
    "3c010a0fce89e9650df693c139b105e2c139313ced837eb7af8db22cfdce2aacd0a440bf3f5bbf4ffed89c726a09fa7df4957ff81ee877b7ebf79d41964b74fa"
    "8dabd46e75906ec881a050def5907e87716cdfff459dfb8273c0283c331dce01cf8d372deb8207e780f1b4ef953ca097887ee295bf14367f1f957fc837a3f0a2",
    "9efe7b597a7fde7d5e49249e993e7f3c67c2a9892010f4f3bff3dbdf05bdee76bdbecba65bdb997ca31ccc9c0f6207b138b777d4f250be37b78e5f09d1af85e4"
    "73a68261bdde057f9f027fff59ef05fefe72f1c0dfc7d3be5bedc225a25f78f33f1f60dbbfff61049ecf42b73db7156fb936ce5fb03c5396ef19743ceb3f06bb",
    "88deeff2a3b36f839e5f553dff21049ecf428f0485a698f6b365ffd96ea1b095694576821ce51d3d0fe3d8beff667d7fb75f1f35ef70caaff75b9e29cbf70c3a"
    "ab08ba7faa6a37bdb9773d378fc433d35fc80f68b203a6218913f1d834f18bac3ff0afe13ceeeaea79a7fe7c72bb7353eeb6582e761ceb94bad1d671a712f7d0",
    "f92cd0f3f6fd47e979141ebefc3b4d76328d69bb55afa7917866fafc7a5de7d312f273805e5f201e29ffbddf65e252bfaeec57afb745b1a094b7b6cfce29efe8"
    "f579d765ab88f67d163a6ebdfeb8c9ca8ada6489ca5f98c616bfff2402cf67a14fd8703179fd8ba62873a2285d887d466e72e2f5455dbb77797ebfde5a50fd31",
    "8a81377e413ca3fd4bcbb315cfa0cf15dfd3c5e819fc231acff9faf75f8678ceaada03a77ebe72141fc40f86c3427a10086603fe5831b2e5f7d07aeeff41fcde"
    "291f7f0dd1becf425ff4b87efcec2f5cb4194e6264d2f29ac4363f78285f8ee6f76af592d71958a1c10c52828a6d5d28f1403f0c3a8e7903e17d5fb0af7f8178",
    "a4ec43f94662f99d6ee9748bad3582a9f36221bbd5f7501c08c6afb998e5cdef9938ff83f9d8da7ac60788f3dbd746817810193c88f3e3691ffc7f737f57755f"
    "ff43f1fac9abf3f4c0bdf660a1eb03e6f37f534e915f1f18bdfcab7f05f120b7db8333993e2cf76bfd5aa8c41cc46ff89dfdd33306ec01d803c47b9bd78bc9da",
    "0356007be0cc1eb002797b30feda875f057be0767bd0a2cf42f9edd35c37548ba8b11d3a1f6482450fe5e587f562fbda2826f9bba4b1e9f7e78df7cf8b47fa1c"
    "af87e38210d75f201ec4f5f1b4ef5abd3e646451e9ddeee340c5dd1772ae37fc4e785a8fdf26a6e79b3df33d28f3e2796adfa7e5de458d574b88ebfc5b88f3bb",
    "5fdfabbb01be74709a6c9f6f8bc3be9ae513d92dd543fa1ecee79a0bea7cee08d11e817b15998114e13851cf64b02c7d3faf5f708cc433d3f1f90506db74cd4f"
    "4e6ec2ed6ffe09c46f5655ef3bddefcf9f9fcb27ede1a952aeb0db07d12dfff03c00fbfdd7713c6be56e3fcf6f20da73cab74f23f07c16fa33ec404e8ce97bfe",
    "b5b22c7b309e13ef0912cf4cc72f3f33f611cfd733fe32c47f56d72e389e0f048e6eaadd56f5a4ddea844a49b5932e0ce21eba770be603e66296b712b6f9c047"
    "11783e0bddfe9e75235be7f2ce7db9ebde06e39e755d66eebfc725a29f18f5fe3f79f71b301f70bbde2f77623529751cbcca7539bf2a3027f9ed1cdcb3be267a",
    "7f5cc4e6ffbf81c0f359e816bd4f4b12771365055abed1af9f49f484ba969e1ad739830f3cd02f83de9ce15eb469a131991018f8f3e6f1a41fc037e878ec0192"
    "9dcbb8ffa178fa03b00f6eb70f89aa12ad169347b972e5e0309392e5fdc382e021fb00e3dbfebd9cc963089bfdf80c02cf67a15bed475f641b1159a66f121cad",
    "aa8cc00aade9f796357f18bf209ed1fe5b0fe019744cf264c33ee271c8d13fd6c04eb8dd4e0cd387dbb18a54e58bb57c23526d1e66077cde43f123b013f6efe5"
    "4c1ef1ad37af4a7cc9c027bdde0cf1a545e1e9655df020be84a7fd31e2f7abe9ef99c6f3e32627d2ea4c259295c35f0ae39243b81fc08a67a6bb37df2cdc0fb0",
    "483cb81f004ffb63c4ef41ff9b8b590e7f19db798287ee7f6424655a2feb5cb03bd69fb473c1134e91bdfff16fbff01ae8f755d5ef4efdfb06a7a6130945da4f"
    "aa6c34508f1c246aca299c235883f1ab95d7977d8e8055129a118b71b4b25c3defae7dc7f7d9463ade3ffad34f401e08d7ebfdebe636cbdfc403fe4339d3296f",
    "4582c9722b0ff73bae89def763f3df7f1281e79b51b4b4469a0fbf0e7abd309f204832dba7556673c632e2e7c3fe0d9c0b76bf5e17ceaff68ee4742799cc6ccb"
    "223314f7c4c28e87fc7918cff6b551ccf2f7dab2d76da721aaece4336e4677ab1d2821f1cc743cfefd1ddb9690e7ed4b6007dc6f07fa7bdbc110933eca370ff6",
    "d5f3105dcac458de43fb79c688df43dcde5ccc7218c3e6f7bf8cc0f3cd28ac22d002e5de3c4029249e998e219fa7c6a925eceb1a41deb705e2915a9fed467a79"
    "3e78530dfa4b72a017db62f6fb7c8ef28e9e87716cdfff45f9f99f42e0f92cf4a7e2f8d11ecba92921a7df5eb234bd3fef3edf3a12cf4c7f2e7951269311a6b1",
    "a97b0533dfe0e990be9983c4f76b52dfa27e0c71fd55b5078ee3fae7d1ca70386887f2522f1e0fc4ea3b257acf4371fd31e2f76ef5fb25447f17920f74e2ffeb"
    "7582e03c80159a14cc039cf80f134ec13cc06378a4f4fece20cb253afdc6556ab73a4837e4405028ef2640efafaadebf44f4176f9ed0bb78cfbc72f8b3083c9f",
    "856e9917e84120cabd71ff13249e998e7d3e309b4c128cfbffd94b5f00ff7f55ed80d378d061f5e48a4b47226c31c7176b7bfbcd4afeac4879c70e101bcfd3c1"
    "5c3ea8c6362b02bbb9e5df7854667846998cce476f04361e6569edcf373763222ff5b40f4f26fe9b286c467aaa988d57938cc0c8b4766277b3c1080a93a5d57a",
    "fbfe7846ed4f722a7faf5a9e29cbe787f73f1c17c37a6ddc07f0d6ac3ed7ebf0dbb3fa895e5397b37af67dea2d6c76c4a91c5bcf7ba9729dd7e64af3da116b41"
    "f5c328b8e611b907f00c3aa6f35e537611be47e68ffee06fc17eacaafd703a8f08846aad407dab3b3c0bfa77aef9bd8090beaa7968ff108c63fbfe9be5ee17b0",
    "e9fb8f20f07c16fa53f306b9c50af5766759fa7efc82780b9d6f3a9b37cc3847fc5cc0073f57fa0ee8ff05e191d2ff3783ebd43e9d68b676fcf57c5c2c5f257a"
    "a1ebb877f4ff4ac6031ed4ff8fb5b0c6d4015ecabac1653d3cad47756ceb06af589ea9dbefe9145699bc3b2bb49615379ad74fc822f1ccf4b9ee1153a7d78819",
    "ac9a2a7c82e7057eb303e7c05cafefa5e3de311b6c9c44a44efe28779649d4f6848687d60d40dfebe5b9f4fdff6886f53f5ad8e6012f98e74792c586c20e99b9"
    "e33ecbb20305cb3365f99e41c7233f06bb48e6f919c1fd310bc42365073add722e22a56a793625e52aed7e65cfdf553db46fc82b76e012d14facf2f787ecb2e3",
    "fd1c23b4d43605f17e67f2a2b38b6c9c30fcce373f08feffaaea7da7e3ee387372becf37aa72e434181a6c6d9ff0fedc11057a7f2df5fee515b673049f44e0f9"
    "2c74ed70f4e4f52f9aa2cc89a27421f619b9c989d71775fd2e49b7c6ff2f2dcf563c833ed7be515d8c9ec13fa2f93ebffefd97c11eacaa3d703a0f508ee283f8",
    "c17058480f02c16cc01f2b46b6fc10ff7f7e7bb0e0fd4397887ee2dd3f7a77af240a0f579e4f95d54f56b9d5df27714e406579460bf8abb7a7c388cac3d77ee7"
    "fd7f09fa7d4178a4f4fb80cf56e8562d99df2ed6f7b6d3897c6950ad7b282f048c63fbfe9bf57a149b5e7f28ff5b8b518f27afbb34bd4e72fef7c2f9a20c8130",
    "3246cd9846d8de837e5f201e29fdce9e670ffda5cc5979a75ce4f9de9958e22abc87f66f923cdf8f7f3c3f9efd15cf664ac7a6f7ba44f41baf3cee608bebff0c"
    "02cf67a1f374477f5bedb5158931f8bb0e711d6cf2f3141349c675c2f9277f07711db7db85ec6e2c993b4d55f9fdad6abc7dd2a926cee4e39877ec02f8fdf6fd",
    "47f9fd12a23da7fcfa29049ecf42d7def988612446d69f71cd3b1eca03a1a872afaee2d3fb67483c331dabdebf63de12e405f4fe22f148e9fd5268af22b63a79"
    "be1fe9c55359312a744f540fe9fd31e2f730aecd0575be0b8507f11fbd40fc676178d3b22e7810ffc1d3be57d66f51fef742f6f3878fc3d37a4c63dbdff30904",
    "becf42b7eceb54c58cd862eb3417d3b7f7ac855d987f5f98996d84f302fd7af7bfc0fe7eb7db851c47ef8b87d5ddec7942629b95f3b828b404d8dfbf86e3592b"
    "af63f3ffe11e00bdb8377f38e4ff5c241edc0380a77df0fbf5f27cf99ecfc2d36a74464cdff30c2d04a8e5e9fb79effd8c20f1ccf42729e7ea9ee5e9d68438ab",
    "a61c5a869efffdfff0c710cf5f553defd48fdf0b144a15ee50aa7563c16caddcbe398c1d153c94af01c6afb998e52d486c3fbed2d3df10fc76b4dfdea0555a0b"
    "db4f78b50479187fe84903fcf655d5e74efdf66c996d54bbe7836666a8b49a83ec55aa2d7429efe87318c7f6fd37cbdd236cfb3221dfa63d1ee4db9c174f2feb",
    "8207f936f1b40ffadfbeff66b9fb34b1fd389377d4928461f3eb57f93e9617de8f630884b11f67c634c2f9757e78f66d88d7b85dbf970e59aebf53e89d7174e1"
    "a052a815856cf6dc43fa1dc6b37d6d14d4ba2bf8f9cf87077efe7ae865d278e0e7e3691fec807d6d14b3fc05b0edc384fbda5178663adcd73e37deb4ac0b1edc",
    "d78ea77db00bf6b55116959fc1f1fd0fb2586714e562f6ca17ac20f55405dfbaeff3c687e6b5070c12cf4cc72a2ff64c247d1f0bc48b1688476a3c6e85b2fbfd"
    "1853dc0e29adab6386199eeed28c87ce6fc1f8b67fafe79d3740fce8f9f0207eb41e7a9a341ec48ff0b40f76c1febd9cc9e336b678d2c710783e0bfda978d209",
    "535745f980d5c320ae5d5f2e23f1cc743ce700efb18d7cfc08e60b0bc423651786d5dd58e8400c5dd7d247cdab6d5e64d3bb52d23b7601c6b37d6d14b3fcf997"
    "3d3f60956366a096c46bb7eaff2212cf4cc7252f33762de33cd817fedd7f04fdef76fd2fed2bf5b3a3b4da3dad264ea37b85b444a74e3d741e0cc6b37d6d1454",
    "7c0885872faf832c5e53cbf3f3df9d138f645e077929f210febf3f84bc0eaed7efa14c2810d9af26ceafd59c3fd6edaa8376a0e821ff1ec6b17dffcd72f71a36"
    "bdfe8ae599bafd9e4e6195c9bbcaecc0ad7a3d83c433d371c883ce29d2f1fcf037fe6912fc76b7ebf55cbd739a9213f56642ad6ed7b78a3bd1b36cd4437a1dfc",
    "76fbda28a8f83d0a0fd7f92f5661ba3d9a736d5e8723249e998e43bf4f39453c8e17fe8b2ffe16e8f755d5ef4ef33aa4a5e15637946f54ceb6b80053624ecfd5"
    "ed7dca3bfa1dc6b17dff51791d24447b4ef985faffe3b3d4d3fbc0f537bea88b32b32c3d3f9e13ef6d249e993ed77abe2e20c66abe9575a4f76f164f7f007adf",
    "ed7a7f471a840689dd9c7c759cd9556f1272e12658a7bca3f7c788dfc3b83617b31cbeb1ec7559d8b709fb361fc0d3cbbae0c1be4d3cedff39e2f74ef9c821da"
    "f759e80bb5078f6bec6498df189fde7fbf4b44ffb1ca65f884607c5f91685959dabc60de79630e8967a6cf336fd438a46df335784538efcf2b9f7f07e6016ed7",
    "fbd7a72925c1754e1281a65ce6fa57f9b4302c7ae8de45d0fbcf7e3f4772393abdd5fbbf8168cf293f3f83c0f359e8967901dd17d9464496e99b0447ab2a23b0"
    "426bfa3d9827385937b2631fe9790235fac71ad80bb7db8b61fa703b5691aa7cb1966f44aacdc3ec80cf1f82bd582d7b613c2a759a33ef5bb944f41fef3c8121",
    "b8bf13eeed827bbb56470f93c6837bbbf0b40fe7b7ec6ba398e56f0bdb7af1ab9667caf23d83aea832c7082db53d7b76ebbe4f227121751a16ba6519d9b8d0e8"
    "3d5ffd1ef8f9abaaef9dfaf995a36bae97c845a474f2fc2a97dba153d956c743e7b5601cdbf7df2c771f87f5e017c45b689c07d68357461f93c683f5603ced8f",
    "11bf77cac73344fb3e0b1daffe7facb9a3cfe507e395c35f8473bb0ef1bc7fde0fceed2e120fceede2691ff2b5d9bf9723791cc596bdee5b170545cd89429915"
    "5a1ca38a8291b8cdade705c8aefbdab18ff8baaff237158807b9dd4ea49b995e20ba43dfe4f8a1d291d5d6c97edbefa17d4263c4ef615c9b8b590ef7603fa843",
    "3cd80f8a1b4f2feb8207fb41f1b4ff5788df3be5a38268df67a113990f3c36084d8e6e29a6f7bc44bc07def94109d6815f10cffbeb47b00ebc483c5807c6d33e"
    "c487ecdfcb99fecf605b1ffe3002cf67a15be243fa06d778cbb5fb3f0b9667caf23d838e67de68b06b83272727e31f41fefed5b5034ef77f468242534cfbd9b2",
    "ff6cb750d8cab4223b418ef28e1d80fb1fed6ba398f57e1e5bdc07f2c0e9c5bdf9a3200fdc22f1200f1c9ef641bfdbd746319fdf2a61f3eb9dca5f5de46bacc0"
    "e8c71ae21cc3338276bdefed7bcf1b5ffac003fd30e813f6d75556142edab4d09818025cf3c4c603f8061dabfcd83295f43ad178f82f7e05ecc3aada07a77120",
    "3a74b69fecedec317bb1da90499f8891d37c19eefb85f1ad95517a69f38165db05981fd8f71fe60764f0607e80a77d18c7f6fd5fd53cd1cbd6fbe339f1d72fbf"
    "2ce48d5e241ee48dc6d33ecc03ecdfcb913c8ecbcb3e2f0079e2204fdcf3e24dcbbae0419e383ced7bd54ea0fc6aa7f2f812e2bd8cfd9b263d39aa84a7f5f81d",
    "3847e0100fce11e0c6d3cbbae0c139023cedcf7b8ea08768df67a193d0ff8feb2297a5af445973fa521357905a923d18d7c3fa1f8d65ef2bd596dd1576c8cc3d"
    "6f58969d28589e29cbf70c3a9e7983c12e92fb4a475f86bca2eeb7139d6e39179152b53c9b92729576bfb2e7efaa51b0136027f4626b271eb5c3d37a7497677a",
    "8468df299f3f89c0f759e8d320baa05e3445991345e942ec33729313af2fea6da6de716f9ce9d2f26cc533e873ad5fe9e6e319fc237a2ee1ebdf7f19e6196eb7"
    "1fca517c103f180e0be94120980df863c5c896df4379ea88ed5b9d0eeaf24135b65911d8cd2dffc6a3f244ef2b132dffe88dc0c6a32cadfdf9e6664ce4a59ef6",
    "e109abb0a2b019e9a962365e4d320223d3da42e966831114264bab75d37953943c3895bff722dec3b00f1f317dfa243cad46b33afc16b6f812aa1fbe1985ae39"
    "3b87bda879c317e7c44b22f1ccf4f9f63168cec68453130121a8efc795d761bee0767ddfadd51acda054cb1f17ca7251dc4a26b94cd043f30518bfe682da7f34",
    "42b4e7944f9f42e0f92c744b5c8855a23d96535342aec733325b5f9a9e9f77fda98ec433d3b1e7a5b67290fc3eb66f513f06bfdfed76e0fa3c5a190e07ed505e"
    "eac5e381587da744ef811d58133be0c766073e8ac0f359e8b67927360c6f7f79711f77dd5bf4599d6f3399b9ff1e97887e62f4fffff97ffb1cf8ff6ed7fb573b",
    "c962ab513c49ed27725bfb27b5e24eab59f0d0ba32e87d7341e9fd79f7977e1a81e7b3d0adfb4b2589bb294f955862763240ff9e57ce253c7900dfa063da6ffa"
    "343bc9cf07e05cc202f148d9857afaaa3054634767ddc0d609db1aec2707a5530fad038c11bf87716d2e6639dc81f308b302e711ecdfc7811cc1798405e2c179",
    "043ced8f11bf07fb602e66394c618b237d0281e7b3d02df6a1a730055a6e8a724cbbd181c2b76efcbcf9ac49e6c79a5f7ecc6c239cd7bafc6417ec81dbedc14d"
    "9797f6abfb692e78c2b68b4cf470d0ef9f79289f118c67fbda28a87b6c4688f69cf2ede711783e0bfda97bce1a13d73621cac942654a77eb7ac2f10378061dd7",
    "3d48776c233e2fd8c896c10eb8dd0e84761a47c71956aec55acda32a7dcd46867b6710375aef79c1bd7b6d4688f6e05cc1b3f18cf62f2dcf563c830ee70a5e14"
    "4f2feb8207e70af0b43f46fc1eec82b998f31be1b30babb2efc8c07fdefda7b0efc8be360aec3b228307fb8ef0b4ef95736612a29f0b39871c7e27acd777e7cb",
    "e695c79f41e0fb2c74cddfe55576c2b98b36c349d3b3d85a716bdc6861f6e0de3c419494cda7f846de8ff8ef3ffccf303f70bb3d28441be5c1f94d3bb1951906"
    "d2ed505f281e843cb47e30eff9221ad1becf425fc0787e5c17795e14f499bfd54f266a1f46f9f0b40e17e0dc1a8547aee0dcda7ae871d278706e0d4ffb5e9947",
    "fc4b443f9dca1fea1e1bc34eec993e7d3b3cad4617b37af67c3bbf987d1ebed4ebcb4b6cf92c5e46f4d337a348e2b529cfd3bc785ecc67a1f921533e113d0f33"
    "face6f7f17ecc1aada03a7f729dcf8f785762a769d3f9ca82161b7b25b3b4f1e52deb1076e1dbf44e709d44658afb7609e40c13ce159ef05f384e5e2c13c014f",
    "fbef227ebff4fcc6f676e1719353a77f1295bb7b71a325e5c1d6d74de3ada5d981959513db7566835d44f71bfde8ecdba0ef5755df3b9d07448242534cfbd9b2"
    "ff6cb750d8cab4223b418e027dbf56fa9ebad3f7f39e577e0381e7b3d0edf25b445981962ddbad1e9a1791ca6fb1b2eb52e87d6b76ec9ccd0a20cf8557f048cd",
    "0b1255255a2d268f72e5cac1612625cbfb870521e91d3b01e3dbfebd1cc9e328b1ec736c9a03cc0ca408c7897a84c5adfb53c99e63bbcf36d2e7d8c2ed6ffe09"
    "d88555b50b4ee70ffcf9b97cd21e9e2ae50abb7d10ddf20fcf03e714d805b00b5ac1b7ff08f25ca0f0cc74f79f8b873c178bc4833c1778daff73c4ef9df2f10a",
    "d1becf425fb85d78dcbcbb548d222c97972d38ef3cfbcef805f18cf62f2dcf563c830ee79d5f144f2feb8207e79df1b43f46fcde291fcf11edfb2c745ceb0ffa"
    "4ae2c56448d3ea85b10993222c8718cfb5c1fab315cf4c87f567a7787a59173c587fc6d3febcf3fe5344fb3e0b1d97fe17443547e7f2726a32b45b13e54f56fe",
    "ce889d2f60158116a8e5ad13ccabdf53483c337dbefb36267f6c4e39b584f8e1e82bfff03dc85fe176fdde8df4f27cf0a61af497e4402fb6c5ecf7f91c05fa7d"
    "ddf5fb08d11e8175625ade984c6f447d62e3d675e20a12cf4cc79bc768cab7a92d206807be74fa51b003ab6a079cc6796aeddd4255e0d44659e4e33de170bb16",
    "8fa63db47fc82be78f51fb3f9dca1fcaef36ce9fbd71ffc33fa4c3d3da38673c5adc79e3f722fae59b51949eeee1c27c00ed47346895d66ee09bf06a09f381f1"
    "879e34c00eacaa1d703a1fc896d946b57b3e6866864aab39c85ea5da4297023bb06a764042f47331f9eceef43ea9fd394a57d6b603b936bfc42112cf4c9fffbe",
    "558d5324e3fae16f545e073dbfaa7adea9bf1f4cc69b6dff6eea2a1fdf4ea985a220f463071ebaf70cc6afb998e5ed756c719e8f23f07c16fa53f9240e449e66"
    "85b82c8ba67d9828bb46ea1c99bbe23e2636928efbfcfbbf87fb2f5d6f07b82cdfe03b32939562a7ea9ed86b34cf7aac87f249c078b6af8d6296bf5d6cfefd2b",
    "9667eaf67b3a855514899615c6adf19c1c12cf4c9fc73fd038a4790806afc8eef30fbff2f97740bfbb5dbf5f9fa69404d73949049a7299eb5fe5d3c2b008f713"
    "aca97eff3cb63c129f41e0f92c74b8f75e2f70effd0be34dcbbae0c1bdf778da87f88fb998e56d035bfce763083c9f856ebfcfc788f22f4fffbb2b1f84b1cf47",
    "9799fbef7189e827c6f5dd2fffafff0d71ff55d5fb4ed777f77a99b2ff643b1f9153db71a19a2eed0aa55d0af4febae9fddf45b4e7944f6f22f07c16ba5d1e39"
    "f311e79450e0e83a33fbfeaaac03cc9b57a4f600be415fd83da833b61a1b8108ca19e4935b201ea9f941af108b0d42b1532977bcc38472eded6c26d4f150dc08",
    "c6b7fd7badebfcc1c0f7763e39983f78150fe60f78daf7cafed04b443ff1e6156d10dbffaf62ca1b6a2d4ee344efbe209ed13e89fdffda75a7dacc5235928552"
    "44e5e16bbff3febf04fdbe203c527e7ff2b8d2de8d9ee4bb35693759d9a3eb5ce1a0e3a17360308eedfb6f96bb5fbed5ebf3c6617e0a81e7b3d0b5773e6218c9",
    "693ea3555d0f3e7b00cfa06bf2519857402499edd32ab379c7bc25c84b38ffe4ef20dee376bd5f0aed55c45627cff723bd782a2b4685ee89eaa1780fe87dfbfe"
    "9be52e8acd9f47dd73ec9b515a8c7a3c795dd7aefb3e4fbe676c7a7ec634c2f33cf0eb1788474abfb3e7d9437f297356de291779be772696b80aefa17ccfa0df",
    "edfb6f96bb1836bffea711783e0b5d7be706db6c323223d499f9fd7a03efa138bda2cabdba8acfaf7f1b8967a663f7ebef984778bf30f8f58bc423a5f74f0a27"
    "83ed74ad76b55daa243af4b5dacfd109c8dfbcc6e35a2baf61b303af5a9e29cbf70cbaf6cad3dbac66cf6ef5fbab0fe01974ecf232651ed13c0fa0ff1788476a",
    "bd364a2bd57ce448dced24b78fda078d5034ad0429f7ebffff0fa3baa5a9", "" };

  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(data, 187928U, &nameCaptureInfo);
  return nameCaptureInfo;
}

/* End of code generation (denseMatch.c) */
