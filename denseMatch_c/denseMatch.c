/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * denseMatch.c
 *
 * Code generation for function 'denseMatch'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "denseMatch.h"
#include "toc.h"
#include "denseMatch_emxutil.h"
#include "sum.h"
#include "abs.h"
#include "power.h"
#include "strcmp.h"
#include "mean2.h"
#include "tic.h"

/* Function Definitions */
void denseMatch(const emxArray_uint8_T *rightImage, const emxArray_uint8_T
                *leftImage, double corrWindowSize, double dMin, double dMax,
                const emxArray_char_T *method, emxArray_real_T *dispMap, double *
                timeTaken)
{
  emxArray_real_T *b_leftImage;
  int i0;
  int loop_ub;
  emxArray_real_T *b_rightImage;
  double win;
  int maximize;
  emxArray_real_T *tempCorrScore;
  emxArray_real_T *r0;
  emxArray_real_T *r1;
  emxArray_real_T *r2;
  emxArray_real_T *c_leftImage;
  int i;
  double b_i;
  int i1;
  int j;
  double b_j;
  double prevcorrScore;
  int i2;
  double d0;
  int d;
  double d1;
  double b_d;
  int i3;
  int i4;
  double meanRight;
  double meanLeft;
  int i5;
  int i6;
  int i7;
  int i8;
  int i9;
  int i10;
  int loop_ub_tmp;
  int i11;
  unsigned int unnamed_idx_0;
  unsigned int unnamed_idx_1;
  int b_loop_ub;
  int c_loop_ub;
  int kstr;
  int d_loop_ub;
  int e_loop_ub;
  boolean_T b_bool;
  int exitg1;
  static const char cv0[3] = { 'S', 'A', 'D' };

  static const char cv1[4] = { 'Z', 'S', 'A', 'D' };

  static const char cv2[4] = { 'L', 'S', 'A', 'D' };

  static const char cv3[3] = { 'S', 'S', 'D' };

  static const char cv4[4] = { 'Z', 'S', 'S', 'D' };

  static const char cv5[4] = { 'L', 'S', 'S', 'D' };

  emxInit_real_T(&b_leftImage, 2);

  /*  ************************************************************************* */
  /*  Title: Function-Compute Correlation between two images using */
  /*  various  */
  /*  similarity measures with Left Image as reference. */
  /*  Author: Siddhant Ahuja */
  /*  Created: March 2010 */
  /*  Copyright Siddhant Ahuja, 2010 */
  /*  Inputs:  */
  /*  1. Left Image (var: rightImage),  */
  /*  2. Right Image (var: leftImage), */
  /*  3. Correlation Window Size (var: corrWindowSize),  */
  /*  4. Minimum Disparity in X-direction (var: dMin),  */
  /*  5. Maximum Disparity in X-direction (var: dMax), */
  /*  6. Method used for calculating the correlation scores (var: */
  /*  method) */
  /*  Valid values include: 'SAD', 'LSAD', 'ZSAD', 'SSD', 'LSSD', */
  /*  ZSSD', 'NCC', */
  /*  'ZNCC' */
  /*  Outputs:  */
  /*  1. Disparity Map (var: dispMap),  */
  /*  2. Time taken (var: timeTaken) */
  /*  Example Usage of Function: [dispMap, */
  /*  timeTaken]=denseMatch('tsukuba_left.tiff', 'tsukuba_right.tiff', */
  /*  9, 0, 16, 'ZNCC'); */
  /*  ************************************************************************* */
  /*  Find the size (columns and rows) of the left image and assign the */
  /*  rows to */
  /*  variable nrLeft, and columns to variable ncLeft */
  /*  Find the size (columns and rows) of the right image and assign */
  /*  the rows to */
  /*  variable nrRight, and columns to variable ncRight */
  /*  Check to see if both the left and right images have same number */
  /*  of rows */
  /*  and columns */
  /*  Convert the left and right images from uint8 to double */
  i0 = b_leftImage->size[0] * b_leftImage->size[1];
  b_leftImage->size[0] = leftImage->size[0];
  b_leftImage->size[1] = leftImage->size[1];
  emxEnsureCapacity_real_T(b_leftImage, i0);
  loop_ub = leftImage->size[0] * leftImage->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_leftImage->data[i0] = (double)leftImage->data[i0] / 255.0;
  }

  emxInit_real_T(&b_rightImage, 2);
  i0 = b_rightImage->size[0] * b_rightImage->size[1];
  b_rightImage->size[0] = rightImage->size[0];
  b_rightImage->size[1] = rightImage->size[1];
  emxEnsureCapacity_real_T(b_rightImage, i0);
  loop_ub = rightImage->size[0] * rightImage->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_rightImage->data[i0] = (double)rightImage->data[i0] / 255.0;
  }

  /*  Check the size of window to see if it is an odd number. */
  /*  Check whether minimum disparity is less than the maximum */
  /*  disparity. */
  /*  Create an image of size nrLeft and ncLeft, fill it with zeros and */
  /*  assign */
  /*  it to variable dispMap */
  i0 = dispMap->size[0] * dispMap->size[1];
  dispMap->size[0] = leftImage->size[0];
  dispMap->size[1] = leftImage->size[1];
  emxEnsureCapacity_real_T(dispMap, i0);
  loop_ub = leftImage->size[0] * leftImage->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    dispMap->data[i0] = 0.0;
  }

  /*  Find out how many rows and columns are to the left/right/up/down */
  /*  of the */
  /*  central pixel based on the window size */
  win = (corrWindowSize - 1.0) / 2.0;

  /*  The objective of CC, NCC and ZNCC is to maxmize the */
  /*  correlation score, whereas other methods try to minimize */
  /*  it. */
  maximize = 0;
  if (b_strcmp(method) || c_strcmp(method)) {
    maximize = 1;
  }

  tic();

  /*  Initialize the timer to calculate the time consumed. */
  i0 = (int)(((double)leftImage->size[0] - win) + (1.0 - (1.0 + win)));
  emxInit_real_T(&tempCorrScore, 2);
  emxInit_real_T(&r0, 2);
  emxInit_real_T(&r1, 2);
  emxInit_real_T(&r2, 2);
  emxInit_real_T(&c_leftImage, 2);
  for (i = 0; i < i0; i++) {
    b_i = (1.0 + win) + (double)i;

    /*  For every row in Left Image */
    i1 = (int)((((double)leftImage->size[1] - win) - dMax) + (1.0 - (1.0 + win)));
    for (j = 0; j < i1; j++) {
      b_j = (1.0 + win) + (double)j;

      /*  For every column in Left Image */
      /*  Initialize the temporary variable to hold the previous */
      /*  correlation score */
      if (maximize != 0) {
        prevcorrScore = 0.0;
      } else {
        prevcorrScore = 65532.0;
      }

      /*  Initialize the temporary variable to store the best */
      /*  matched */
      /*  disparity score */
      dispMap->data[((int)b_i + dispMap->size[0] * ((int)b_j - 1)) - 1] = dMin;
      i2 = (int)(dMax + (1.0 - dMin));
      if (0 <= i2 - 1) {
        d0 = b_i - win;
        d1 = b_i + win;
        if (d0 > d1) {
          i3 = 0;
          i4 = 0;
        } else {
          i3 = (int)d0 - 1;
          i4 = (int)d1;
        }

        meanRight = b_j - win;
        meanLeft = b_j + win;
        if (meanRight > meanLeft) {
          i5 = 0;
          i6 = 0;
        } else {
          i5 = (int)meanRight - 1;
          i6 = (int)meanLeft;
        }

        if (d0 > d1) {
          i8 = 0;
          i10 = 0;
        } else {
          i8 = (int)d0 - 1;
          i10 = (int)d1;
        }

        loop_ub_tmp = i6 - i5;
        unnamed_idx_0 = (unsigned int)(i4 - i3);
        unnamed_idx_1 = (unsigned int)loop_ub_tmp;
        b_loop_ub = (int)unnamed_idx_0 * (int)unnamed_idx_1;
      }

      for (d = 0; d < i2; d++) {
        b_d = dMin + (double)d;

        /*  For every disparity value in x-direction */
        /*  Construct a region with window around */
        /*  central/selected pixel in left image */
        /*  Construct a region with window around */
        /*  central/selected pixel in right image */
        d0 = b_j + b_d;
        d1 = d0 - win;
        d0 += win;
        if (d1 > d0) {
          i7 = 0;
          i9 = 0;
        } else {
          i7 = (int)d1 - 1;
          i9 = (int)d0;
        }

        /*  Calculate the local mean in left region */
        i11 = c_leftImage->size[0] * c_leftImage->size[1];
        loop_ub = i4 - i3;
        c_leftImage->size[0] = loop_ub;
        c_loop_ub = i6 - i5;
        c_leftImage->size[1] = c_loop_ub;
        emxEnsureCapacity_real_T(c_leftImage, i11);
        for (i11 = 0; i11 < loop_ub_tmp; i11++) {
          for (kstr = 0; kstr < loop_ub; kstr++) {
            c_leftImage->data[kstr + c_leftImage->size[0] * i11] =
              b_leftImage->data[(i3 + kstr) + b_leftImage->size[0] * (i5 + i11)];
          }
        }

        meanLeft = mean2(c_leftImage);

        /*  Calculate the local mean in right region */
        i11 = c_leftImage->size[0] * c_leftImage->size[1];
        d_loop_ub = i10 - i8;
        c_leftImage->size[0] = d_loop_ub;
        e_loop_ub = i9 - i7;
        c_leftImage->size[1] = e_loop_ub;
        emxEnsureCapacity_real_T(c_leftImage, i11);
        for (i9 = 0; i9 < e_loop_ub; i9++) {
          for (i11 = 0; i11 < d_loop_ub; i11++) {
            c_leftImage->data[i11 + c_leftImage->size[0] * i9] =
              b_rightImage->data[(i8 + i11) + b_rightImage->size[0] * (i7 + i9)];
          }
        }

        meanRight = mean2(c_leftImage);

        /*  Initialize the variable to store temporarily the */
        /*  correlation scores */
        i9 = tempCorrScore->size[0] * tempCorrScore->size[1];
        tempCorrScore->size[0] = (int)unnamed_idx_0;
        tempCorrScore->size[1] = (int)unnamed_idx_1;
        emxEnsureCapacity_real_T(tempCorrScore, i9);
        for (i9 = 0; i9 < b_loop_ub; i9++) {
          tempCorrScore->data[i9] = 0.0;
        }

        /*  Calculate the correlation score */
        b_bool = false;
        if (method->size[1] == 3) {
          kstr = 0;
          do {
            exitg1 = 0;
            if (kstr < 3) {
              if (method->data[kstr] != cv0[kstr]) {
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

        if (b_bool) {
          i9 = c_leftImage->size[0] * c_leftImage->size[1];
          c_leftImage->size[0] = loop_ub;
          c_leftImage->size[1] = c_loop_ub;
          emxEnsureCapacity_real_T(c_leftImage, i9);
          for (i9 = 0; i9 < c_loop_ub; i9++) {
            for (i11 = 0; i11 < loop_ub; i11++) {
              c_leftImage->data[i11 + c_leftImage->size[0] * i9] =
                b_leftImage->data[(i3 + i11) + b_leftImage->size[0] * (i5 + i9)]
                - b_rightImage->data[(i8 + i11) + b_rightImage->size[0] * (i7 +
                i9)];
            }
          }

          b_abs(c_leftImage, tempCorrScore);
        } else {
          b_bool = false;
          if (method->size[1] == 4) {
            kstr = 0;
            do {
              exitg1 = 0;
              if (kstr < 4) {
                if (method->data[kstr] != cv1[kstr]) {
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

          if (b_bool) {
            i9 = c_leftImage->size[0] * c_leftImage->size[1];
            c_leftImage->size[0] = loop_ub;
            c_leftImage->size[1] = c_loop_ub;
            emxEnsureCapacity_real_T(c_leftImage, i9);
            for (i9 = 0; i9 < c_loop_ub; i9++) {
              for (i11 = 0; i11 < loop_ub; i11++) {
                c_leftImage->data[i11 + c_leftImage->size[0] * i9] =
                  ((b_leftImage->data[(i3 + i11) + b_leftImage->size[0] * (i5 +
                     i9)] - meanLeft) - b_rightImage->data[(i8 + i11) +
                   b_rightImage->size[0] * (i7 + i9)]) + meanRight;
              }
            }

            b_abs(c_leftImage, tempCorrScore);
          } else {
            b_bool = false;
            if (method->size[1] == 4) {
              kstr = 0;
              do {
                exitg1 = 0;
                if (kstr < 4) {
                  if (method->data[kstr] != cv2[kstr]) {
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

            if (b_bool) {
              meanRight = meanLeft / meanRight;
              i9 = c_leftImage->size[0] * c_leftImage->size[1];
              c_leftImage->size[0] = loop_ub;
              c_leftImage->size[1] = c_loop_ub;
              emxEnsureCapacity_real_T(c_leftImage, i9);
              for (i9 = 0; i9 < c_loop_ub; i9++) {
                for (i11 = 0; i11 < loop_ub; i11++) {
                  c_leftImage->data[i11 + c_leftImage->size[0] * i9] =
                    b_leftImage->data[(i3 + i11) + b_leftImage->size[0] * (i5 +
                    i9)] - meanRight * b_rightImage->data[(i8 + i11) +
                    b_rightImage->size[0] * (i7 + i9)];
                }
              }

              b_abs(c_leftImage, tempCorrScore);
            } else {
              b_bool = false;
              if (method->size[1] == 3) {
                kstr = 0;
                do {
                  exitg1 = 0;
                  if (kstr < 3) {
                    if (method->data[kstr] != cv3[kstr]) {
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

              if (b_bool) {
                i9 = c_leftImage->size[0] * c_leftImage->size[1];
                c_leftImage->size[0] = loop_ub;
                c_leftImage->size[1] = c_loop_ub;
                emxEnsureCapacity_real_T(c_leftImage, i9);
                for (i9 = 0; i9 < c_loop_ub; i9++) {
                  for (i11 = 0; i11 < loop_ub; i11++) {
                    c_leftImage->data[i11 + c_leftImage->size[0] * i9] =
                      b_leftImage->data[(i3 + i11) + b_leftImage->size[0] * (i5
                      + i9)] - b_rightImage->data[(i8 + i11) +
                      b_rightImage->size[0] * (i7 + i9)];
                  }
                }

                power(c_leftImage, tempCorrScore);
              } else {
                b_bool = false;
                if (method->size[1] == 4) {
                  kstr = 0;
                  do {
                    exitg1 = 0;
                    if (kstr < 4) {
                      if (method->data[kstr] != cv4[kstr]) {
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

                if (b_bool) {
                  i9 = c_leftImage->size[0] * c_leftImage->size[1];
                  c_leftImage->size[0] = loop_ub;
                  c_leftImage->size[1] = c_loop_ub;
                  emxEnsureCapacity_real_T(c_leftImage, i9);
                  for (i9 = 0; i9 < c_loop_ub; i9++) {
                    for (i11 = 0; i11 < loop_ub; i11++) {
                      c_leftImage->data[i11 + c_leftImage->size[0] * i9] =
                        ((b_leftImage->data[(i3 + i11) + b_leftImage->size[0] *
                          (i5 + i9)] - meanLeft) - b_rightImage->data[(i8 + i11)
                         + b_rightImage->size[0] * (i7 + i9)]) + meanRight;
                    }
                  }

                  power(c_leftImage, tempCorrScore);
                } else {
                  b_bool = false;
                  if (method->size[1] == 4) {
                    kstr = 0;
                    do {
                      exitg1 = 0;
                      if (kstr < 4) {
                        if (method->data[kstr] != cv5[kstr]) {
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

                  if (b_bool) {
                    meanRight = meanLeft / meanRight;
                    i9 = c_leftImage->size[0] * c_leftImage->size[1];
                    c_leftImage->size[0] = loop_ub;
                    c_leftImage->size[1] = c_loop_ub;
                    emxEnsureCapacity_real_T(c_leftImage, i9);
                    for (i9 = 0; i9 < c_loop_ub; i9++) {
                      for (i11 = 0; i11 < loop_ub; i11++) {
                        c_leftImage->data[i11 + c_leftImage->size[0] * i9] =
                          b_leftImage->data[(i3 + i11) + b_leftImage->size[0] *
                          (i5 + i9)] - meanRight * b_rightImage->data[(i8 + i11)
                          + b_rightImage->size[0] * (i7 + i9)];
                      }
                    }

                    power(c_leftImage, tempCorrScore);
                  } else if (b_strcmp(method)) {
                    /*  Calculate the term in the denominator (var: den) */
                    i9 = c_leftImage->size[0] * c_leftImage->size[1];
                    c_leftImage->size[0] = loop_ub;
                    c_leftImage->size[1] = c_loop_ub;
                    emxEnsureCapacity_real_T(c_leftImage, i9);
                    for (i9 = 0; i9 < c_loop_ub; i9++) {
                      for (i11 = 0; i11 < loop_ub; i11++) {
                        c_leftImage->data[i11 + c_leftImage->size[0] * i9] =
                          b_leftImage->data[(i3 + i11) + b_leftImage->size[0] *
                          (i5 + i9)];
                      }
                    }

                    power(c_leftImage, r0);
                    sum(r0, r1);
                    i9 = c_leftImage->size[0] * c_leftImage->size[1];
                    c_leftImage->size[0] = d_loop_ub;
                    c_leftImage->size[1] = e_loop_ub;
                    emxEnsureCapacity_real_T(c_leftImage, i9);
                    for (i9 = 0; i9 < e_loop_ub; i9++) {
                      for (i11 = 0; i11 < d_loop_ub; i11++) {
                        c_leftImage->data[i11 + c_leftImage->size[0] * i9] =
                          b_rightImage->data[(i8 + i11) + b_rightImage->size[0] *
                          (i7 + i9)];
                      }
                    }

                    power(c_leftImage, r0);
                    sum(r0, r2);
                    meanRight = sqrt(b_sum(r1) * b_sum(r2));
                    i9 = tempCorrScore->size[0] * tempCorrScore->size[1];
                    tempCorrScore->size[0] = loop_ub;
                    tempCorrScore->size[1] = c_loop_ub;
                    emxEnsureCapacity_real_T(tempCorrScore, i9);
                    for (i9 = 0; i9 < c_loop_ub; i9++) {
                      for (i11 = 0; i11 < loop_ub; i11++) {
                        tempCorrScore->data[i11 + tempCorrScore->size[0] * i9] =
                          b_leftImage->data[(i3 + i11) + b_leftImage->size[0] *
                          (i5 + i9)] * b_rightImage->data[(i8 + i11) +
                          b_rightImage->size[0] * (i7 + i9)] / meanRight;
                      }
                    }
                  } else {
                    if (c_strcmp(method)) {
                      /*  Calculate the term in the denominator (var: den) */
                      i9 = tempCorrScore->size[0] * tempCorrScore->size[1];
                      tempCorrScore->size[0] = d_loop_ub;
                      tempCorrScore->size[1] = e_loop_ub;
                      emxEnsureCapacity_real_T(tempCorrScore, i9);
                      for (i9 = 0; i9 < e_loop_ub; i9++) {
                        for (i11 = 0; i11 < d_loop_ub; i11++) {
                          tempCorrScore->data[i11 + tempCorrScore->size[0] * i9]
                            = b_rightImage->data[(i8 + i11) + b_rightImage->
                            size[0] * (i7 + i9)] - meanRight;
                        }
                      }

                      i7 = c_leftImage->size[0] * c_leftImage->size[1];
                      c_leftImage->size[0] = loop_ub;
                      c_leftImage->size[1] = c_loop_ub;
                      emxEnsureCapacity_real_T(c_leftImage, i7);
                      for (i7 = 0; i7 < c_loop_ub; i7++) {
                        for (i9 = 0; i9 < loop_ub; i9++) {
                          c_leftImage->data[i9 + c_leftImage->size[0] * i7] =
                            b_leftImage->data[(i3 + i9) + b_leftImage->size[0] *
                            (i5 + i7)] - meanLeft;
                        }
                      }

                      power(c_leftImage, r0);
                      sum(r0, r1);
                      power(tempCorrScore, r0);
                      sum(r0, r2);
                      meanRight = sqrt(b_sum(r1) * b_sum(r2));
                      i7 = tempCorrScore->size[0] * tempCorrScore->size[1];
                      tempCorrScore->size[0] = loop_ub;
                      tempCorrScore->size[1] = c_loop_ub;
                      emxEnsureCapacity_real_T(tempCorrScore, i7);
                      for (i7 = 0; i7 < c_loop_ub; i7++) {
                        for (i9 = 0; i9 < loop_ub; i9++) {
                          tempCorrScore->data[i9 + tempCorrScore->size[0] * i7] =
                            (b_leftImage->data[(i3 + i9) + b_leftImage->size[0] *
                             (i5 + i7)] - meanLeft) * tempCorrScore->data[i9 +
                            tempCorrScore->size[0] * i7] / meanRight;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }

        /*  Compute the final score by summing the values in */
        /*  tempCorrScore, */
        /*  and store it in a temporary variable signifying the */
        /*  distance */
        /*  (var: corrScore) */
        sum(tempCorrScore, r1);
        meanRight = b_sum(r1);
        if (maximize != 0) {
          if (meanRight > prevcorrScore) {
            /*  If the current disparity value is greater */
            /*  than */
            /*  previous one, then swap them */
            prevcorrScore = meanRight;
            dispMap->data[((int)b_i + dispMap->size[0] * ((int)b_j - 1)) - 1] =
              b_d;
          }
        } else {
          if (prevcorrScore > meanRight) {
            /*  If the current disparity value is less than */
            /*  previous one, then swap them */
            prevcorrScore = meanRight;
            dispMap->data[((int)b_i + dispMap->size[0] * ((int)b_j - 1)) - 1] =
              b_d;
          }
        }
      }

      /*  Store the final matched value in variable dispMap */
    }
  }

  emxFree_real_T(&c_leftImage);
  emxFree_real_T(&r2);
  emxFree_real_T(&r1);
  emxFree_real_T(&r0);
  emxFree_real_T(&b_rightImage);
  emxFree_real_T(&b_leftImage);
  emxFree_real_T(&tempCorrScore);

  /*  Stop the timer to calculate the time consumed. */
  *timeTaken = toc();
}

/* End of code generation (denseMatch.c) */
