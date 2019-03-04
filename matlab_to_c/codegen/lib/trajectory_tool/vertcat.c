/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: vertcat.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 26-Feb-2019 13:17:28
 */

/* Include Files */
#include <string.h>
#include "trajectory_tool.h"
#include "vertcat.h"
#include "quaternioncg.h"

/* Function Definitions */

/*
 * Arguments    : double obj_a
 *                double obj_b
 *                double obj_c
 *                double obj_d
 *                const double varargin_1_a[1599]
 *                const double varargin_1_b[1599]
 *                const double varargin_1_c[1599]
 *                const double varargin_1_d[1599]
 *                double y_a[1600]
 *                double y_b[1600]
 *                double y_c[1600]
 *                double y_d[1600]
 * Return Type  : void
 */
void quaternionBase_vertcat(double obj_a, double obj_b, double obj_c, double
  obj_d, const double varargin_1_a[1599], const double varargin_1_b[1599], const
  double varargin_1_c[1599], const double varargin_1_d[1599], double y_a[1600],
  double y_b[1600], double y_c[1600], double y_d[1600])
{
  double b_obj_a[1600];
  double b_obj_b[1600];
  double b_obj_c[1600];
  double b_obj_d[1600];
  b_obj_a[0] = obj_a;
  b_obj_b[0] = obj_b;
  b_obj_c[0] = obj_c;
  b_obj_d[0] = obj_d;
  memcpy(&b_obj_a[1], &varargin_1_a[0], 1599U * sizeof(double));
  memcpy(&b_obj_b[1], &varargin_1_b[0], 1599U * sizeof(double));
  memcpy(&b_obj_c[1], &varargin_1_c[0], 1599U * sizeof(double));
  memcpy(&b_obj_d[1], &varargin_1_d[0], 1599U * sizeof(double));
  c_quaternioncg_quaternioncg(b_obj_a, b_obj_b, b_obj_c, b_obj_d, y_a, y_b, y_c,
    y_d);
}

/*
 * File trailer for vertcat.c
 *
 * [EOF]
 */
