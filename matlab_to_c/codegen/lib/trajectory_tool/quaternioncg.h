/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: quaternioncg.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 26-Feb-2019 13:17:28
 */

#ifndef QUATERNIONCG_H
#define QUATERNIONCG_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "trajectory_tool_types.h"

/* Function Declarations */
extern void b_quaternioncg_parenReference(const double obj_a[1600], const double
  obj_b[1600], const double obj_c[1600], const double obj_d[1600], const double
  varargin_1[1599], double o_a[1599], double o_b[1599], double o_c[1599], double
  o_d[1599]);
extern void b_quaternioncg_times(const double x_a[1600], const double x_b[1600],
  const double x_c[1600], const double x_d[1600], const double y_a[1600], const
  double y_b[1600], const double y_c[1600], const double y_d[1600], double o_a
  [1600], double o_b[1600], double o_c[1600], double o_d[1600]);
extern void c_quaternioncg_quaternioncg(const double varargin_1[1600], const
  double varargin_2[1600], const double varargin_3[1600], const double
  varargin_4[1600], double obj_a[1600], double obj_b[1600], double obj_c[1600],
  double obj_d[1600]);
extern void quaternioncg_parenAssign(d_matlabshared_rotations_intern *obj,
  double rhs_a, double rhs_b, double rhs_c, double rhs_d, double varargin_1);
extern void quaternioncg_parenReference(const double obj_a[1600], const double
  obj_b[1600], const double obj_c[1600], const double obj_d[1600], double
  varargin_1, double *o_a, double *o_b, double *o_c, double *o_d);
extern void quaternioncg_quaternioncg(const double varargin_1[4800], double
  obj_a[1600], double obj_b[1600], double obj_c[1600], double obj_d[1600]);
extern void quaternioncg_reshape(const double obj_a[1600], const double obj_b
  [1600], const double obj_c[1600], const double obj_d[1600], double x_a[1600],
  double x_b[1600], double x_c[1600], double x_d[1600]);
extern void quaternioncg_times(double x_a, double x_b, double x_c, double x_d,
  double y_a, double y_b, double y_c, double y_d, double *o_a, double *o_b,
  double *o_c, double *o_d);

#endif

/*
 * File trailer for quaternioncg.h
 *
 * [EOF]
 */
