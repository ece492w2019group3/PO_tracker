/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: main.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 01-Mar-2019 15:09:29
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
/* Include Files */
#include <string.h>
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "main.h"
#include "kal_tool_terminate.h"
#include "kal_tool_initialize.h"

/* Function Declarations */
static void argInit_1600x3_real_T(double result[4800]);
static double argInit_real_T(void);
static void main_kal_tool(void);

/* Function Definitions */

/*
 * Arguments    : double result[4800]
 * Return Type  : void
 */
static void argInit_1600x3_real_T(double result[4800])
{
  int idx0;
  double result_tmp;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 1600; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result_tmp = argInit_real_T();
    result[idx0] = result_tmp;

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 1600] = result_tmp;

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 3200] = argInit_real_T();
  }
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_kal_tool(void)
{
  static double acc_tmp_tmp[4800];
  static double b_acc_tmp_tmp[4800];
  static double c_acc_tmp_tmp[4800];
  static double d_acc_tmp_tmp[4800];
  static double angularVelocity_kal[4800];

  /* Initialize function 'kal_tool' input arguments. */
  /* Initialize function input argument 'acc'. */
  argInit_1600x3_real_T(acc_tmp_tmp);

  /* Initialize function input argument 'gyro'. */
  /* Initialize function input argument 'mag'. */
  /* Call the entry-point 'kal_tool'. */
  memcpy(&b_acc_tmp_tmp[0], &acc_tmp_tmp[0], 4800U * sizeof(double));
  memcpy(&c_acc_tmp_tmp[0], &acc_tmp_tmp[0], 4800U * sizeof(double));
  memcpy(&d_acc_tmp_tmp[0], &acc_tmp_tmp[0], 4800U * sizeof(double));
  kal_tool(b_acc_tmp_tmp, c_acc_tmp_tmp, d_acc_tmp_tmp, acc_tmp_tmp,
           angularVelocity_kal);
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  kal_tool_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_kal_tool();

  /* Terminate the application.
     You do not need to do this more than one time. */
  kal_tool_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
