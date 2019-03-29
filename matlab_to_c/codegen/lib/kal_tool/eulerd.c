/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: eulerd.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 01-Mar-2019 15:09:29
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "eulerd.h"
#include "atan2.h"
#include "power1.h"
#include "asin.h"
#include "normalize.h"

/* Function Definitions */

/*
 * Arguments    : const d_matlabshared_rotations_intern *q
 *                double a[4800]
 * Return Type  : void
 */
void quaternionBase_eulerd(const d_matlabshared_rotations_intern *q, double a
  [4800])
{
  static d_matlabshared_rotations_intern b_q;
  double a_tmp[1600];
  double dv2[1600];
  int i;
  double c_q[1600];
  double b_a_tmp[1600];
  double c_a_tmp;
  double tmp[1600];
  double dv3[1600];
  b_q = *q;
  b_quaternionBase_normalize(&b_q);
  power(b_q.a, a_tmp);
  power(b_q.b, dv2);
  for (i = 0; i < 1600; i++) {
    c_a_tmp = b_q.b[i] * b_q.d[i] * 2.0 - b_q.a[i] * b_q.c[i] * 2.0;
    tmp[i] = c_a_tmp;
    if (c_a_tmp > 1.0) {
      c_a_tmp = 1.0;
      tmp[i] = 1.0;
    }

    if (c_a_tmp < -1.0) {
      tmp[i] = -1.0;
    }

    c_a_tmp = a_tmp[i] * 2.0 - 1.0;
    c_q[i] = b_q.a[i] * b_q.d[i] * 2.0 + b_q.b[i] * b_q.c[i] * 2.0;
    b_a_tmp[i] = c_a_tmp + dv2[i] * 2.0;
    a_tmp[i] = c_a_tmp;
  }

  b_atan2(c_q, b_a_tmp, dv2);
  b_asin(tmp);
  power(b_q.d, dv3);
  for (i = 0; i < 1600; i++) {
    c_q[i] = b_q.a[i] * b_q.b[i] * 2.0 + b_q.c[i] * b_q.d[i] * 2.0;
    b_a_tmp[i] = a_tmp[i] + dv3[i] * 2.0;
    a[i] = 57.295779513082323 * dv2[i];
    a[1600 + i] = 57.295779513082323 * -tmp[i];
  }

  b_atan2(c_q, b_a_tmp, dv3);
  for (i = 0; i < 1600; i++) {
    a[3200 + i] = 57.295779513082323 * dv3[i];
  }
}

/*
 * File trailer for eulerd.c
 *
 * [EOF]
 */
