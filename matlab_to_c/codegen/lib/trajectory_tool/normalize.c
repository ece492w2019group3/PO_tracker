/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: normalize.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 26-Feb-2019 13:17:28
 */

/* Include Files */
#include "trajectory_tool.h"
#include "normalize.h"
#include "sqrt.h"

/* Function Definitions */

/*
 * Arguments    : d_matlabshared_rotations_intern *q
 * Return Type  : void
 */
void quaternionBase_normalize(d_matlabshared_rotations_intern *q)
{
  int i;
  double n[1600];
  for (i = 0; i < 1600; i++) {
    n[i] = ((q->a[i] * q->a[i] + q->b[i] * q->b[i]) + q->c[i] * q->c[i]) + q->
      d[i] * q->d[i];
  }

  b_sqrt(n);
  for (i = 0; i < 1600; i++) {
    q->a[i] /= n[i];
    q->b[i] /= n[i];
    q->c[i] /= n[i];
    q->d[i] /= n[i];
  }
}

/*
 * File trailer for normalize.c
 *
 * [EOF]
 */
