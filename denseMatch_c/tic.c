/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * tic.c
 *
 * Code generation for function 'tic'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "denseMatch.h"
#include "tic.h"
#include "timeKeeper.h"
#include "getTime.h"

/* Function Definitions */
void tic(void)
{
  double t0_tv_sec;
  double t0_tv_nsec;
  getTime(&t0_tv_sec, &t0_tv_nsec);
  timeKeeper(t0_tv_sec, t0_tv_nsec);
}

/* End of code generation (tic.c) */
