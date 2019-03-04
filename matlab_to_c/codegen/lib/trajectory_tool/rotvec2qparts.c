/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: rotvec2qparts.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 26-Feb-2019 13:17:28
 */

/* Include Files */
#include <math.h>
#include "trajectory_tool.h"
#include "rotvec2qparts.h"
#include "sqrt.h"
#include "sum.h"
#include "power1.h"

/* Function Definitions */

/*
 * Arguments    : const double r[4800]
 *                double a[1600]
 *                double b[1600]
 *                double c[1600]
 *                double d[1600]
 * Return Type  : void
 */
void rotvec2qparts(const double r[4800], double a[1600], double b[1600], double
                   c[1600], double d[1600])
{
  int i;
  double dv1[4800];
  double theta[1600];
  double ct[1600];
  double st;
  for (i = 0; i < 1600; i++) {
    a[i] = 1.0;
    b[i] = 0.0;
    c[i] = 0.0;
    d[i] = 0.0;
  }

  power(r, dv1);
  sum(dv1, theta);
  b_sqrt(theta);
  for (i = 0; i < 1600; i++) {
    ct[i] = cos(theta[i] / 2.0);
    st = sin(theta[i] / 2.0);
    if (theta[i] != 0.0) {
      a[i] = ct[i];
      b[i] = r[i] / theta[i] * st;
      c[i] = r[i + 1600] / theta[i] * st;
      d[i] = r[i + 3200] / theta[i] * st;
    }
  }
}

/*
 * File trailer for rotvec2qparts.c
 *
 * [EOF]
 */
