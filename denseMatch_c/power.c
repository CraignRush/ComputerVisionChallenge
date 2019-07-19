/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * power.c
 *
 * Code generation for function 'power'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "denseMatch.h"
#include "power.h"
#include "denseMatch_emxutil.h"

/* Function Definitions */
void power(const emxArray_real_T *a, emxArray_real_T *y)
{
  unsigned int unnamed_idx_0;
  unsigned int unnamed_idx_1;
  int nx;
  int k;
  unnamed_idx_0 = (unsigned int)a->size[0];
  unnamed_idx_1 = (unsigned int)a->size[1];
  nx = y->size[0] * y->size[1];
  y->size[0] = (int)unnamed_idx_0;
  y->size[1] = (int)unnamed_idx_1;
  emxEnsureCapacity_real_T(y, nx);
  nx = (int)unnamed_idx_0 * (int)unnamed_idx_1;
  for (k = 0; k < nx; k++) {
    y->data[k] = a->data[k] * a->data[k];
  }
}

/* End of code generation (power.c) */
