/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: main.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 27-Mar-2019 12:24:35
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
#include "trajectory_tool.h"
#include "main.h"
#include "trajectory_tool_terminate.h"
#include "trajectory_tool_initialize.h"

/* Function Declarations */
static void argInit_1x3_real_T(double result[3]);
static void argInit_2x3_real_T(double result[6]);
static double argInit_real_T(void);
static void main_trajectory_tool(void);

/* Function Definitions */

/*
 * Arguments    : double result[3]
 * Return Type  : void
 */
static void argInit_1x3_real_T(double result[3])
{
  double result_tmp;

  /* Loop over the array to initialize each element. */
  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result_tmp = argInit_real_T();
  result[0] = result_tmp;

  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result[1] = result_tmp;

  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result[2] = argInit_real_T();
}

/*
 * Arguments    : double result[6]
 * Return Type  : void
 */
static void argInit_2x3_real_T(double result[6])
{
  int idx0;
  double result_tmp;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 2; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result_tmp = argInit_real_T();
    result[idx0] = result_tmp;

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 2] = result_tmp;

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 4] = argInit_real_T();
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
static void main_trajectory_tool(void)
{
  double accelerometerReadings_tmp[6];
  double angularVelocity_tmp[6];
  double prev_position_tmp[3];
  double cur_position[3];
  double velocity[6];
  double acceleration[6];
  double angularVelocity[6];

  /* Initialize function 'trajectory_tool' input arguments. */
  /* Initialize function input argument 'accelerometerReadings'. */
  argInit_2x3_real_T(accelerometerReadings_tmp);

  /* Initialize function input argument 'angularvelocity'. */
  /* Initialize function input argument 'prev_position'. */
  argInit_1x3_real_T(prev_position_tmp);

  /* Initialize function input argument 'prev_velocity'. */
  /* Call the entry-point 'trajectory_tool'. */
  trajectory_tool(accelerometerReadings_tmp, angularVelocity_tmp,
                  prev_position_tmp, prev_position_tmp, cur_position, velocity,
                  acceleration, angularVelocity);
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
  trajectory_tool_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_trajectory_tool();

  /* Terminate the application.
     You do not need to do this more than one time. */
  trajectory_tool_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
