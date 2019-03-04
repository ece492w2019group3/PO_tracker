/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: power1.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 26-Feb-2019 13:17:28
 */

/* Include Files */
#include "trajectory_tool.h"
#include "power1.h"

/* Function Definitions */

/*
 * Arguments    : const double a[4800]
 *                double y[4800]
 * Return Type  : void
 */
void power(const double a[4800], double y[4800])
{
  int k;
  for (k = 0; k < 4800; k++) {
    y[k] = a[k] * a[k];
  }
}

/*
 * File trailer for power1.c
 *
 * [EOF]
 */
