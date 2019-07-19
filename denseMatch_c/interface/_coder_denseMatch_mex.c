/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_denseMatch_mex.c
 *
 * Code generation for function '_coder_denseMatch_mex'
 *
 */

/* Include files */
#include "_coder_denseMatch_api.h"
#include "_coder_denseMatch_mex.h"

/* Function Declarations */
static void denseMatch_mexFunction(int32_T nlhs, mxArray *plhs[2], int32_T nrhs,
  const mxArray *prhs[6]);

/* Function Definitions */
static void denseMatch_mexFunction(int32_T nlhs, mxArray *plhs[2], int32_T nrhs,
  const mxArray *prhs[6])
{
  const mxArray *outputs[2];
  int32_T b_nlhs;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 6) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 6, 4,
                        10, "denseMatch");
  }

  if (nlhs > 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 10,
                        "denseMatch");
  }

  /* Call the function. */
  denseMatch_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(denseMatch_atexit);

  /* Module initialization. */
  denseMatch_initialize();

  /* Dispatch the entry-point. */
  denseMatch_mexFunction(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  denseMatch_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_denseMatch_mex.c) */
