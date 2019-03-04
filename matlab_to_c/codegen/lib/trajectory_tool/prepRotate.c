/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: prepRotate.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 26-Feb-2019 13:17:28
 */

/* Include Files */
#include <string.h>
#include "trajectory_tool.h"
#include "prepRotate.h"
#include "normalize.h"
#include "quaternioncg.h"

/* Function Definitions */

/*
 * Arguments    : const double q_a[1600]
 *                const double q_b[1600]
 *                const double q_c[1600]
 *                const double q_d[1600]
 *                const double v[4800]
 *                d_matlabshared_rotations_intern *qo
 *                double qv_a[1600]
 *                double qv_b[1600]
 *                double qv_c[1600]
 *                double qv_d[1600]
 * Return Type  : void
 */
void quaternionBase_prepRotate(const double q_a[1600], const double q_b[1600],
  const double q_c[1600], const double q_d[1600], const double v[4800],
  d_matlabshared_rotations_intern *qo, double qv_a[1600], double qv_b[1600],
  double qv_c[1600], double qv_d[1600])
{
  static double varargin_1[6400];
  int i2;
  quaternioncg_reshape(q_a, q_b, q_c, q_d, qo->a, qo->b, qo->c, qo->d);
  quaternionBase_normalize(qo);
  memset(&varargin_1[0], 0, 1600U * sizeof(double));
  for (i2 = 0; i2 < 3; i2++) {
    memcpy(&varargin_1[i2 * 1600 + 1600], &v[i2 * 1600], 1600U * sizeof(double));
  }

  memcpy(&qv_a[0], &varargin_1[0], 1600U * sizeof(double));
  memcpy(&qv_b[0], &varargin_1[1600], 1600U * sizeof(double));
  memcpy(&qv_c[0], &varargin_1[3200], 1600U * sizeof(double));
  memcpy(&qv_d[0], &varargin_1[4800], 1600U * sizeof(double));
}

/*
 * File trailer for prepRotate.c
 *
 * [EOF]
 */
