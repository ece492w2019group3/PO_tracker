/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: atan2.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 01-Mar-2019 15:09:29
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "atan2.h"
#include "kal_tool_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : const double y[1600]
 *                const double x[1600]
 *                double r[1600]
 * Return Type  : void
 */
void b_atan2(const double y[1600], const double x[1600], double r[1600])
{
  int k;
  for (k = 0; k < 1600; k++) {
    r[k] = rt_atan2d_snf(y[k], x[k]);
  }
}

/*
 * File trailer for atan2.c
 *
 * [EOF]
 */
