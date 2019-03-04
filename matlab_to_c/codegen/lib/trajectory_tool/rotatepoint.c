/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: rotatepoint.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 26-Feb-2019 13:17:28
 */

/* Include Files */
#include <string.h>
#include "trajectory_tool.h"
#include "rotatepoint.h"
#include "quaternioncg.h"
#include "conj.h"
#include "prepRotate.h"

/* Function Definitions */

/*
 * Arguments    : const double q_a[1600]
 *                const double q_b[1600]
 *                const double q_c[1600]
 *                const double q_d[1600]
 *                const double v[4800]
 *                double u[4800]
 * Return Type  : void
 */
void quaternionBase_rotatepoint(const double q_a[1600], const double q_b[1600],
  const double q_c[1600], const double q_d[1600], const double v[4800], double
  u[4800])
{
  static d_matlabshared_rotations_intern qo;
  double uq_a[1600];
  double uq_b[1600];
  double uq_c[1600];
  double uq_d[1600];
  double t0_a[1600];
  double t0_b[1600];
  double t0_c[1600];
  double t0_d[1600];
  int i1;
  static double b_uq_a[6400];
  quaternionBase_prepRotate(q_a, q_b, q_c, q_d, v, &qo, uq_a, uq_b, uq_c, uq_d);
  b_quaternioncg_times(qo.a, qo.b, qo.c, qo.d, uq_a, uq_b, uq_c, uq_d, t0_a,
                       t0_b, t0_c, t0_d);
  quaternionBase_conj(&qo);
  b_quaternioncg_times(t0_a, t0_b, t0_c, t0_d, qo.a, qo.b, qo.c, qo.d, uq_a,
                       uq_b, uq_c, uq_d);
  for (i1 = 0; i1 < 1600; i1++) {
    b_uq_a[i1] = uq_a[i1];
    b_uq_a[1600 + i1] = uq_b[i1];
    b_uq_a[3200 + i1] = uq_c[i1];
    b_uq_a[4800 + i1] = uq_d[i1];
  }

  for (i1 = 0; i1 < 3; i1++) {
    memcpy(&u[i1 * 1600], &b_uq_a[i1 * 1600 + 1600], 1600U * sizeof(double));
  }
}

/*
 * File trailer for rotatepoint.c
 *
 * [EOF]
 */
