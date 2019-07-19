/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mean2.c
 *
 * Code generation for function 'mean2'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "denseMatch.h"
#include "mean2.h"

/* Function Definitions */
double mean2(const emxArray_real_T *x)
{
  double y;
  int vlen;
  int k;
  vlen = x->size[0] * x->size[1];
  if (x->size[0] * x->size[1] == 0) {
    y = 0.0;
  } else {
    y = x->data[0];
    for (k = 2; k <= vlen; k++) {
      y += x->data[k - 1];
    }
  }

  y /= (double)(x->size[0] * x->size[1]);
  return y;
}

/* End of code generation (mean2.c) */
