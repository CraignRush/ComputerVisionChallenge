/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * timeKeeper.h
 *
 * Code generation for function 'timeKeeper'
 *
 */

#ifndef TIMEKEEPER_H
#define TIMEKEEPER_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "denseMatch_types.h"

/* Function Declarations */
extern void b_timeKeeper(double *outTime_tv_sec, double *outTime_tv_nsec);
extern void savedTime_not_empty_init(void);
extern void timeKeeper(double newTime_tv_sec, double newTime_tv_nsec);

#endif

/* End of code generation (timeKeeper.h) */
