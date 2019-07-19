/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * denseMatch_initialize.c
 *
 * Code generation for function 'denseMatch_initialize'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "denseMatch.h"
#include "denseMatch_initialize.h"
#include "getTime.h"
#include "timeKeeper.h"

/* Function Definitions */
void denseMatch_initialize(void)
{
  rt_InitInfAndNaN(8U);
  savedTime_not_empty_init();
  freq_not_empty_init();
}

/* End of code generation (denseMatch_initialize.c) */
