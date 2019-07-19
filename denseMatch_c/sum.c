/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sum.c
 *
 * Code generation for function 'sum'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "denseMatch.h"
#include "sum.h"
#include "denseMatch_emxutil.h"

/* Function Definitions */
double b_sum(const emxArray_real_T *x)
{
  double y;
  int vlen;
  int k;
  vlen = x->size[1];
  if (x->size[1] == 0) {
    y = 0.0;
  } else {
    y = x->data[0];
    for (k = 2; k <= vlen; k++) {
      y += x->data[k - 1];
    }
  }

  return y;
}

void sum(const emxArray_real_T *x, emxArray_real_T *y)
{
  int vlen;
  int npages;
  unsigned int sz_idx_1;
  int xpageoffset;
  int i;
  int k;
  vlen = x->size[0];
  if ((x->size[0] == 0) || (x->size[1] == 0)) {
    sz_idx_1 = (unsigned int)x->size[1];
    xpageoffset = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)sz_idx_1;
    emxEnsureCapacity_real_T(y, xpageoffset);
    i = (int)sz_idx_1;
    for (xpageoffset = 0; xpageoffset < i; xpageoffset++) {
      y->data[xpageoffset] = 0.0;
    }
  } else {
    npages = x->size[1];
    xpageoffset = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = x->size[1];
    emxEnsureCapacity_real_T(y, xpageoffset);
    for (i = 0; i < npages; i++) {
      xpageoffset = i * x->size[0];
      y->data[i] = x->data[xpageoffset];
      for (k = 2; k <= vlen; k++) {
        y->data[i] += x->data[(xpageoffset + k) - 1];
      }
    }
  }
}

/* End of code generation (sum.c) */
