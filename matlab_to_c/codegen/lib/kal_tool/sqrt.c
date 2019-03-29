/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: sqrt.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 01-Mar-2019 15:09:29
 */

/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "sqrt.h"

/* Function Definitions */

/*
 * Arguments    : double x[1600]
 * Return Type  : void
 */
void b_sqrt(double x[1600])
{
  int k;
  for (k = 0; k < 1600; k++) {
    x[k] = sqrt(x[k]);
  }
}

/*
 * File trailer for sqrt.c
 *
 * [EOF]
 */
