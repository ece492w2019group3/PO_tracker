/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: quaternioncg.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 26-Feb-2019 13:17:28
 */

/* Include Files */
#include <string.h>
#include "trajectory_tool.h"
#include "quaternioncg.h"
#include "rotvec2qparts.h"

/* Function Declarations */
static void b_quaternioncg_quaternioncg(const double varargin_1[1599], const
  double varargin_2[1599], const double varargin_3[1599], const double
  varargin_4[1599], double obj_a[1599], double obj_b[1599], double obj_c[1599],
  double obj_d[1599]);

/* Function Definitions */

/*
 * Arguments    : const double varargin_1[1599]
 *                const double varargin_2[1599]
 *                const double varargin_3[1599]
 *                const double varargin_4[1599]
 *                double obj_a[1599]
 *                double obj_b[1599]
 *                double obj_c[1599]
 *                double obj_d[1599]
 * Return Type  : void
 */
static void b_quaternioncg_quaternioncg(const double varargin_1[1599], const
  double varargin_2[1599], const double varargin_3[1599], const double
  varargin_4[1599], double obj_a[1599], double obj_b[1599], double obj_c[1599],
  double obj_d[1599])
{
  memcpy(&obj_a[0], &varargin_1[0], 1599U * sizeof(double));
  memcpy(&obj_b[0], &varargin_2[0], 1599U * sizeof(double));
  memcpy(&obj_c[0], &varargin_3[0], 1599U * sizeof(double));
  memcpy(&obj_d[0], &varargin_4[0], 1599U * sizeof(double));
}

/*
 * Arguments    : const double obj_a[1600]
 *                const double obj_b[1600]
 *                const double obj_c[1600]
 *                const double obj_d[1600]
 *                const double varargin_1[1599]
 *                double o_a[1599]
 *                double o_b[1599]
 *                double o_c[1599]
 *                double o_d[1599]
 * Return Type  : void
 */
void b_quaternioncg_parenReference(const double obj_a[1600], const double obj_b
  [1600], const double obj_c[1600], const double obj_d[1600], const double
  varargin_1[1599], double o_a[1599], double o_b[1599], double o_c[1599], double
  o_d[1599])
{
  int i0;
  double b_obj_a[1599];
  double b_obj_b[1599];
  double b_obj_c[1599];
  double b_obj_d[1599];
  int obj_a_tmp;
  for (i0 = 0; i0 < 1599; i0++) {
    obj_a_tmp = (int)varargin_1[i0] - 1;
    b_obj_a[i0] = obj_a[obj_a_tmp];
    b_obj_b[i0] = obj_b[obj_a_tmp];
    b_obj_c[i0] = obj_c[obj_a_tmp];
    b_obj_d[i0] = obj_d[obj_a_tmp];
  }

  b_quaternioncg_quaternioncg(b_obj_a, b_obj_b, b_obj_c, b_obj_d, o_a, o_b, o_c,
    o_d);
}

/*
 * Arguments    : const double x_a[1600]
 *                const double x_b[1600]
 *                const double x_c[1600]
 *                const double x_d[1600]
 *                const double y_a[1600]
 *                const double y_b[1600]
 *                const double y_c[1600]
 *                const double y_d[1600]
 *                double o_a[1600]
 *                double o_b[1600]
 *                double o_c[1600]
 *                double o_d[1600]
 * Return Type  : void
 */
void b_quaternioncg_times(const double x_a[1600], const double x_b[1600], const
  double x_c[1600], const double x_d[1600], const double y_a[1600], const double
  y_b[1600], const double y_c[1600], const double y_d[1600], double o_a[1600],
  double o_b[1600], double o_c[1600], double o_d[1600])
{
  int i;
  double b_x_a[1600];
  double c_x_a[1600];
  double d_x_a[1600];
  double e_x_a[1600];
  for (i = 0; i < 1600; i++) {
    b_x_a[i] = ((x_a[i] * y_a[i] - x_b[i] * y_b[i]) - x_c[i] * y_c[i]) - x_d[i] *
      y_d[i];
    c_x_a[i] = ((x_a[i] * y_b[i] + x_b[i] * y_a[i]) + x_c[i] * y_d[i]) - x_d[i] *
      y_c[i];
    d_x_a[i] = ((x_a[i] * y_c[i] - x_b[i] * y_d[i]) + x_c[i] * y_a[i]) + x_d[i] *
      y_b[i];
    e_x_a[i] = ((x_a[i] * y_d[i] + x_b[i] * y_c[i]) - x_c[i] * y_b[i]) + x_d[i] *
      y_a[i];
  }

  c_quaternioncg_quaternioncg(b_x_a, c_x_a, d_x_a, e_x_a, o_a, o_b, o_c, o_d);
}

/*
 * Arguments    : const double varargin_1[1600]
 *                const double varargin_2[1600]
 *                const double varargin_3[1600]
 *                const double varargin_4[1600]
 *                double obj_a[1600]
 *                double obj_b[1600]
 *                double obj_c[1600]
 *                double obj_d[1600]
 * Return Type  : void
 */
void c_quaternioncg_quaternioncg(const double varargin_1[1600], const double
  varargin_2[1600], const double varargin_3[1600], const double varargin_4[1600],
  double obj_a[1600], double obj_b[1600], double obj_c[1600], double obj_d[1600])
{
  memcpy(&obj_a[0], &varargin_1[0], 1600U * sizeof(double));
  memcpy(&obj_b[0], &varargin_2[0], 1600U * sizeof(double));
  memcpy(&obj_c[0], &varargin_3[0], 1600U * sizeof(double));
  memcpy(&obj_d[0], &varargin_4[0], 1600U * sizeof(double));
}

/*
 * Arguments    : d_matlabshared_rotations_intern *obj
 *                double rhs_a
 *                double rhs_b
 *                double rhs_c
 *                double rhs_d
 *                double varargin_1
 * Return Type  : void
 */
void quaternioncg_parenAssign(d_matlabshared_rotations_intern *obj, double rhs_a,
  double rhs_b, double rhs_c, double rhs_d, double varargin_1)
{
  int i3;
  i3 = (int)varargin_1 - 1;
  obj->a[i3] = rhs_a;
  obj->b[i3] = rhs_b;
  obj->c[i3] = rhs_c;
  obj->d[i3] = rhs_d;
}

/*
 * Arguments    : const double obj_a[1600]
 *                const double obj_b[1600]
 *                const double obj_c[1600]
 *                const double obj_d[1600]
 *                double varargin_1
 *                double *o_a
 *                double *o_b
 *                double *o_c
 *                double *o_d
 * Return Type  : void
 */
void quaternioncg_parenReference(const double obj_a[1600], const double obj_b
  [1600], const double obj_c[1600], const double obj_d[1600], double varargin_1,
  double *o_a, double *o_b, double *o_c, double *o_d)
{
  int o_a_tmp;
  o_a_tmp = (int)varargin_1 - 1;
  *o_a = obj_a[o_a_tmp];
  *o_b = obj_b[o_a_tmp];
  *o_c = obj_c[o_a_tmp];
  *o_d = obj_d[o_a_tmp];
}

/*
 * Arguments    : const double varargin_1[4800]
 *                double obj_a[1600]
 *                double obj_b[1600]
 *                double obj_c[1600]
 *                double obj_d[1600]
 * Return Type  : void
 */
void quaternioncg_quaternioncg(const double varargin_1[4800], double obj_a[1600],
  double obj_b[1600], double obj_c[1600], double obj_d[1600])
{
  rotvec2qparts(varargin_1, obj_a, obj_b, obj_c, obj_d);
}

/*
 * Arguments    : const double obj_a[1600]
 *                const double obj_b[1600]
 *                const double obj_c[1600]
 *                const double obj_d[1600]
 *                double x_a[1600]
 *                double x_b[1600]
 *                double x_c[1600]
 *                double x_d[1600]
 * Return Type  : void
 */
void quaternioncg_reshape(const double obj_a[1600], const double obj_b[1600],
  const double obj_c[1600], const double obj_d[1600], double x_a[1600], double
  x_b[1600], double x_c[1600], double x_d[1600])
{
  c_quaternioncg_quaternioncg(obj_a, obj_b, obj_c, obj_d, x_a, x_b, x_c, x_d);
}

/*
 * Arguments    : double x_a
 *                double x_b
 *                double x_c
 *                double x_d
 *                double y_a
 *                double y_b
 *                double y_c
 *                double y_d
 *                double *o_a
 *                double *o_b
 *                double *o_c
 *                double *o_d
 * Return Type  : void
 */
void quaternioncg_times(double x_a, double x_b, double x_c, double x_d, double
  y_a, double y_b, double y_c, double y_d, double *o_a, double *o_b, double *o_c,
  double *o_d)
{
  *o_a = ((x_a * y_a - x_b * y_b) - x_c * y_c) - x_d * y_d;
  *o_b = ((x_a * y_b + x_b * y_a) + x_c * y_d) - x_d * y_c;
  *o_c = ((x_a * y_c - x_b * y_d) + x_c * y_a) + x_d * y_b;
  *o_d = ((x_a * y_d + x_b * y_c) - x_c * y_b) + x_d * y_a;
}

/*
 * File trailer for quaternioncg.c
 *
 * [EOF]
 */
