/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * denseMatch_emxutil.h
 *
 * Code generation for function 'denseMatch_emxutil'
 *
 */

#ifndef DENSEMATCH_EMXUTIL_H
#define DENSEMATCH_EMXUTIL_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "denseMatch_types.h"

/* Function Declarations */
extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);
extern void emxFree_char_T(emxArray_char_T **pEmxArray);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxFree_uint8_T(emxArray_uint8_T **pEmxArray);
extern void emxInit_char_T(emxArray_char_T **pEmxArray, int numDimensions);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);
extern void emxInit_uint8_T(emxArray_uint8_T **pEmxArray, int numDimensions);

#endif

/* End of code generation (denseMatch_emxutil.h) */
