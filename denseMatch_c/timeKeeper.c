/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * timeKeeper.c
 *
 * Code generation for function 'timeKeeper'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "denseMatch.h"
#include "timeKeeper.h"
#include "getTime.h"

/* Type Definitions */
#ifndef typedef_struct_T
#define typedef_struct_T

typedef struct {
  double tv_sec;
  double tv_nsec;
} struct_T;

#endif                                 /*typedef_struct_T*/

/* Variable Definitions */
static struct_T savedTime;
static boolean_T savedTime_not_empty;

/* Function Definitions */
void b_timeKeeper(double *outTime_tv_sec, double *outTime_tv_nsec)
{
  *outTime_tv_sec = savedTime.tv_sec;
  *outTime_tv_nsec = savedTime.tv_nsec;
}

void savedTime_not_empty_init(void)
{
  savedTime_not_empty = false;
}

void timeKeeper(double newTime_tv_sec, double newTime_tv_nsec)
{
  if (!savedTime_not_empty) {
    getTime(&savedTime.tv_sec, &savedTime.tv_nsec);
    savedTime_not_empty = true;
  }

  savedTime.tv_sec = newTime_tv_sec;
  savedTime.tv_nsec = newTime_tv_nsec;
}

/* End of code generation (timeKeeper.c) */
