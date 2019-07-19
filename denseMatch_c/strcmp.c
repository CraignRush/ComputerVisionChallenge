/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * strcmp.c
 *
 * Code generation for function 'strcmp'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "denseMatch.h"
#include "strcmp.h"

/* Function Definitions */
boolean_T b_strcmp(const emxArray_char_T *a)
{
  boolean_T b_bool;
  int kstr;
  int exitg1;
  static const char cv6[3] = { 'N', 'C', 'C' };

  b_bool = false;
  if (a->size[1] == 3) {
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 3) {
        if (a->data[kstr] != cv6[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

boolean_T c_strcmp(const emxArray_char_T *a)
{
  boolean_T b_bool;
  int kstr;
  int exitg1;
  static const char cv7[4] = { 'Z', 'N', 'C', 'C' };

  b_bool = false;
  if (a->size[1] == 4) {
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 4) {
        if (a->data[kstr] != cv7[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

/* End of code generation (strcmp.c) */
