/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * abs.c
 *
 * Code generation for function 'abs'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "denseMatch.h"
#include "abs.h"
#include "denseMatch_emxutil.h"

/* Function Definitions */
void b_abs(const emxArray_real_T *x, emxArray_real_T *y)
{
  int nx;
  unsigned int unnamed_idx_0;
  unsigned int unnamed_idx_1;
  int k;
  nx = x->size[0] * x->size[1];
  unnamed_idx_0 = (unsigned int)x->size[0];
  unnamed_idx_1 = (unsigned int)x->size[1];
  k = y->size[0] * y->size[1];
  y->size[0] = (int)unnamed_idx_0;
  y->size[1] = (int)unnamed_idx_1;
  emxEnsureCapacity_real_T(y, k);
  for (k = 0; k < nx; k++) {
    y->data[k] = fabs(x->data[k]);
  }
}

/* End of code generation (abs.c) */
