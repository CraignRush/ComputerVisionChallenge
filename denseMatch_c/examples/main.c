/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * main.c
 *
 * Code generation for function 'main'
 *
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include files */
#include "rt_nonfinite.h"
#include "denseMatch.h"
#include "main.h"
#include "denseMatch_terminate.h"
#include "denseMatch_emxAPI.h"
#include "denseMatch_initialize.h"

/* Function Declarations */
static emxArray_char_T *argInit_1xUnbounded_char_T(void);
static char argInit_char_T(void);
static double argInit_real_T(void);
static unsigned char argInit_uint8_T(void);
static emxArray_uint8_T *c_argInit_UnboundedxUnbounded_u(void);
static void main_denseMatch(void);

/* Function Definitions */
static emxArray_char_T *argInit_1xUnbounded_char_T(void)
{
  emxArray_char_T *result;
  int idx1;

  /* Set the size of the array.
     Change this size to the value that the application requires. */
  result = emxCreate_char_T(1, 2);

  /* Loop over the array to initialize each element. */
  for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result->data[idx1] = argInit_char_T();
  }

  return result;
}

static char argInit_char_T(void)
{
  return '?';
}

static double argInit_real_T(void)
{
  return 0.0;
}

static unsigned char argInit_uint8_T(void)
{
  return 0U;
}

static emxArray_uint8_T *c_argInit_UnboundedxUnbounded_u(void)
{
  emxArray_uint8_T *result;
  int idx0;
  int idx1;

  /* Set the size of the array.
     Change this size to the value that the application requires. */
  result = emxCreate_uint8_T(2, 2);

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result->data[idx0 + result->size[0] * idx1] = argInit_uint8_T();
    }
  }

  return result;
}

static void main_denseMatch(void)
{
  emxArray_real_T *dispMap;
  emxArray_uint8_T *rightImage;
  emxArray_uint8_T *leftImage;
  double corrWindowSize_tmp;
  double dMax;
  emxArray_char_T *method;
  double timeTaken;
  emxInitArray_real_T(&dispMap, 2);

  /* Initialize function 'denseMatch' input arguments. */
  /* Initialize function input argument 'rightImage'. */
  rightImage = c_argInit_UnboundedxUnbounded_u();

  /* Initialize function input argument 'leftImage'. */
  leftImage = c_argInit_UnboundedxUnbounded_u();
  corrWindowSize_tmp = argInit_real_T();
  dMax = argInit_real_T();

  /* Initialize function input argument 'method'. */
  method = argInit_1xUnbounded_char_T();

  /* Call the entry-point 'denseMatch'. */
  denseMatch(rightImage, leftImage, corrWindowSize_tmp, corrWindowSize_tmp, dMax,
             method, dispMap, &timeTaken);
  emxDestroyArray_real_T(dispMap);
  emxDestroyArray_char_T(method);
  emxDestroyArray_uint8_T(leftImage);
  emxDestroyArray_uint8_T(rightImage);
}

int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  denseMatch_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_denseMatch();

  /* Terminate the application.
     You do not need to do this more than one time. */
  denseMatch_terminate();
  return 0;
}

/* End of code generation (main.c) */
