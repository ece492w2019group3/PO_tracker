/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * eulerd.c
 *
 * Code generation for function 'eulerd'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "eulerd.h"
#include "atan2.h"
#include "power1.h"
#include "asin.h"
#include "normalize.h"

/* Function Definitions */
void quaternionBase_eulerd(const double q_a[1600], const double q_b[1600], const
  double q_c[1600], const double q_d[1600], double a[4800])
{
  static d_matlabshared_rotations_intern q;
  double a_tmp[1600];
  double dv2[1600];
  int i;
  double b_q[1600];
  double b_a_tmp[1600];
  double c_a_tmp;
  double tmp[1600];
  double dv3[1600];
  memcpy(&q.a[0], &q_a[0], 1600U * sizeof(double));
  memcpy(&q.b[0], &q_b[0], 1600U * sizeof(double));
  memcpy(&q.c[0], &q_c[0], 1600U * sizeof(double));
  memcpy(&q.d[0], &q_d[0], 1600U * sizeof(double));
  b_quaternionBase_normalize(&q);
  power(q.a, a_tmp);
  power(q.b, dv2);
  for (i = 0; i < 1600; i++) {
    c_a_tmp = q.b[i] * q.d[i] * 2.0 - q.a[i] * q.c[i] * 2.0;
    tmp[i] = c_a_tmp;
    if (c_a_tmp > 1.0) {
      c_a_tmp = 1.0;
      tmp[i] = 1.0;
    }

    if (c_a_tmp < -1.0) {
      tmp[i] = -1.0;
    }

    c_a_tmp = a_tmp[i] * 2.0 - 1.0;
    b_q[i] = q.a[i] * q.d[i] * 2.0 + q.b[i] * q.c[i] * 2.0;
    b_a_tmp[i] = c_a_tmp + dv2[i] * 2.0;
    a_tmp[i] = c_a_tmp;
  }

  b_atan2(b_q, b_a_tmp, dv2);
  b_asin(tmp);
  power(q.d, dv3);
  for (i = 0; i < 1600; i++) {
    b_q[i] = q.a[i] * q.b[i] * 2.0 + q.c[i] * q.d[i] * 2.0;
    b_a_tmp[i] = a_tmp[i] + dv3[i] * 2.0;
    a[i] = 57.295779513082323 * dv2[i];
    a[1600 + i] = 57.295779513082323 * -tmp[i];
  }

  b_atan2(b_q, b_a_tmp, dv3);
  for (i = 0; i < 1600; i++) {
    a[3200 + i] = 57.295779513082323 * dv3[i];
  }
}

/* End of code generation (eulerd.c) */
