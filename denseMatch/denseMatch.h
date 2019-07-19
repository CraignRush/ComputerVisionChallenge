/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * denseMatch.h
 *
 * Code generation for function 'denseMatch'
 *
 */

#ifndef DENSEMATCH_H
#define DENSEMATCH_H

/* Include files */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include "rtwtypes.h"
#include "denseMatch_types.h"

/* Type Definitions */

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void denseMatch(const emlrtStack *sp, const emxArray_uint8_T *rightImage,
  const emxArray_uint8_T *leftImage, real_T corrWindowSize, real_T dMin, real_T
  dMax, const emxArray_char_T *method, emxArray_real_T *dispMap, real_T
  *timeTaken);
extern void denseMatch_api(const mxArray * const prhs[6], int32_T nlhs, const
  mxArray *plhs[2]);
extern void denseMatch_atexit(void);
extern void denseMatch_initialize(void);
extern void denseMatch_terminate(void);
MEXFUNCTION_LINKAGE mxArray *emlrtMexFcnProperties(void);
extern const mxArray *emlrtMexFcnResolvedFunctionsInfo(void);

#endif

/* End of code generation (denseMatch.h) */
