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
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "denseMatch_types.h"

/* Function Declarations */
extern void denseMatch(const emxArray_uint8_T *rightImage, const
  emxArray_uint8_T *leftImage, double corrWindowSize, double dMin, double dMax,
  const emxArray_char_T *method, emxArray_real_T *dispMap, double *timeTaken);

#endif

/* End of code generation (denseMatch.h) */
