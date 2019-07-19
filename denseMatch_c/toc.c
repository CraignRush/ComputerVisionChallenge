/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * toc.c
 *
 * Code generation for function 'toc'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "denseMatch.h"
#include "toc.h"
#include "getTime.h"
#include "timeKeeper.h"

/* Function Definitions */
double toc(void)
{
  double tstart_tv_sec;
  double tstart_tv_nsec;
  double tnow_tv_sec;
  double tnow_tv_nsec;
  b_timeKeeper(&tstart_tv_sec, &tstart_tv_nsec);
  getTime(&tnow_tv_sec, &tnow_tv_nsec);
  return (tnow_tv_sec - tstart_tv_sec) + (tnow_tv_nsec - tstart_tv_nsec) /
    1.0E+9;
}

/* End of code generation (toc.c) */
