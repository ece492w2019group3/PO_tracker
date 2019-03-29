/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: power1.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 01-Mar-2019 15:09:29
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "power1.h"

/* Function Definitions */

/*
 * Arguments    : const double a[1600]
 *                double y[1600]
 * Return Type  : void
 */
void power(const double a[1600], double y[1600])
{
  int k;
  for (k = 0; k < 1600; k++) {
    y[k] = a[k] * a[k];
  }
}

/*
 * File trailer for power1.c
 *
 * [EOF]
 */
