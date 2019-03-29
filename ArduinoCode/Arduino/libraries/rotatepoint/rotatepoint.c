/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: rotatepoint.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 27-Mar-2019 12:24:35
 */

/* Include Files */
#include <math.h>
#include "trajectory_tool.h"
#include "rotatepoint.h"
#include "quaternioncg.h"

/* Function Definitions */

/*
 * Arguments    : const double q_a[2]
 *                const double q_b[2]
 *                const double q_c[2]
 *                const double q_d[2]
 *                const double v[6]
 *                double u[6]
 * Return Type  : void
 */
void quaternionBase_rotatepoint(const double q_a[2], const double q_b[2], const
  double q_c[2], const double q_d[2], const double v[6], double u[6])
{
  double d0;
  double uq_a[2];
  double uq_b[2];
  double uq_c[2];
  double uq_d[2];
  int i0;
  double n[2];
  int varargin_1_tmp;
  double qv_b[2];
  double varargin_1[8];
  int b_varargin_1_tmp;
  double qv_c[2];
  double qv_d[2];
  double b_q_a[2];
  double b_q_b[2];
  double b_q_c[2];
  double b_q_d[2];
  double b_uq_a[2];
  double b_uq_b[2];
  double b_uq_c[2];
  double b_uq_d[2];
  d0 = sqrt(((q_a[0] * q_a[0] + q_b[0] * q_b[0]) + q_c[0] * q_c[0]) + q_d[0] *
            q_d[0]);
  uq_a[0] = q_a[0] / d0;
  uq_b[0] = q_b[0] / d0;
  uq_c[0] = q_c[0] / d0;
  uq_d[0] = q_d[0] / d0;
  d0 = sqrt(((q_a[1] * q_a[1] + q_b[1] * q_b[1]) + q_c[1] * q_c[1]) + q_d[1] *
            q_d[1]);
  uq_a[1] = q_a[1] / d0;
  uq_b[1] = q_b[1] / d0;
  uq_c[1] = q_c[1] / d0;
  uq_d[1] = q_d[1] / d0;
  for (i0 = 0; i0 < 3; i0++) {
    varargin_1_tmp = i0 << 1;
    b_varargin_1_tmp = (i0 + 1) << 1;
    varargin_1[b_varargin_1_tmp] = v[varargin_1_tmp];
    varargin_1[1 + b_varargin_1_tmp] = v[1 + varargin_1_tmp];
  }

  n[0] = 0.0;
  qv_b[0] = varargin_1[2];
  qv_c[0] = varargin_1[4];
  qv_d[0] = varargin_1[6];
  b_q_a[0] = uq_a[0];
  b_q_b[0] = -uq_b[0];
  b_q_c[0] = -uq_c[0];
  b_q_d[0] = -uq_d[0];
  b_uq_a[0] = uq_a[0];
  b_uq_b[0] = uq_b[0];
  b_uq_c[0] = uq_c[0];
  b_uq_d[0] = uq_d[0];
  n[1] = 0.0;
  qv_b[1] = varargin_1[3];
  qv_c[1] = varargin_1[5];
  qv_d[1] = varargin_1[7];
  b_q_a[1] = uq_a[1];
  b_q_b[1] = -uq_b[1];
  b_q_c[1] = -uq_c[1];
  b_q_d[1] = -uq_d[1];
  b_uq_a[1] = uq_a[1];
  b_uq_b[1] = uq_b[1];
  b_uq_c[1] = uq_c[1];
  b_uq_d[1] = uq_d[1];
  b_quaternioncg_times(b_uq_a, b_uq_b, b_uq_c, b_uq_d, n, qv_b, qv_c, qv_d, uq_a,
                       uq_b, uq_c, uq_d);
  b_uq_a[0] = uq_a[0];
  b_uq_b[0] = uq_b[0];
  b_uq_c[0] = uq_c[0];
  b_uq_d[0] = uq_d[0];
  b_uq_a[1] = uq_a[1];
  b_uq_b[1] = uq_b[1];
  b_uq_c[1] = uq_c[1];
  b_uq_d[1] = uq_d[1];
  b_quaternioncg_times(b_uq_a, b_uq_b, b_uq_c, b_uq_d, b_q_a, b_q_b, b_q_c,
                       b_q_d, uq_a, uq_b, uq_c, uq_d);
  varargin_1[0] = uq_a[0];
  varargin_1[2] = uq_b[0];
  varargin_1[4] = uq_c[0];
  varargin_1[6] = uq_d[0];
  varargin_1[1] = uq_a[1];
  varargin_1[3] = uq_b[1];
  varargin_1[5] = uq_c[1];
  varargin_1[7] = uq_d[1];
  for (i0 = 0; i0 < 3; i0++) {
    varargin_1_tmp = (1 + i0) << 1;
    b_varargin_1_tmp = i0 << 1;
    u[b_varargin_1_tmp] = varargin_1[varargin_1_tmp];
    u[1 + b_varargin_1_tmp] = varargin_1[1 + varargin_1_tmp];
  }
}

/*
 * File trailer for rotatepoint.c
 *
 * [EOF]
 */
