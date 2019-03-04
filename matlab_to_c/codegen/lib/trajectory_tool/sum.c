/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: sum.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 26-Feb-2019 13:17:28
 */

/* Include Files */
#include <string.h>
#include "trajectory_tool.h"
#include "sum.h"

/* Function Definitions */

/*
 * Arguments    : const double x[4800]
 *                double y[1600]
 * Return Type  : void
 */
void sum(const double x[4800], double y[1600])
{
  int k;
  int xoffset;
  int j;
  memcpy(&y[0], &x[0], 1600U * sizeof(double));
  for (k = 0; k < 2; k++) {
    xoffset = (k + 1) * 1600;
    for (j = 0; j < 1600; j++) {
      y[j] += x[xoffset + j];
    }
  }
}

/*
 * File trailer for sum.c
 *
 * [EOF]
 */
