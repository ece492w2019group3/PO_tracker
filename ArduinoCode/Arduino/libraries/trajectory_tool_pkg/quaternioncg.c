/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: quaternioncg.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 30-Mar-2019 15:04:56
 */

/* Include Files */
#include "trajectory_tool.h"
#include "quaternioncg.h"

/* Function Definitions */

/*
 * Arguments    : const double x_a[2]
 *                const double x_b[2]
 *                const double x_c[2]
 *                const double x_d[2]
 *                const double y_a[2]
 *                const double y_b[2]
 *                const double y_c[2]
 *                const double y_d[2]
 *                double o_a[2]
 *                double o_b[2]
 *                double o_c[2]
 *                double o_d[2]
 * Return Type  : void
 */
void b_quaternioncg_times(const double x_a[2], const double x_b[2], const double
  x_c[2], const double x_d[2], const double y_a[2], const double y_b[2], const
  double y_c[2], const double y_d[2], double o_a[2], double o_b[2], double o_c[2],
  double o_d[2])
{
  o_a[0] = ((x_a[0] * y_a[0] - x_b[0] * y_b[0]) - x_c[0] * y_c[0]) - x_d[0] *
    y_d[0];
  o_b[0] = ((x_a[0] * y_b[0] + x_b[0] * y_a[0]) + x_c[0] * y_d[0]) - x_d[0] *
    y_c[0];
  o_c[0] = ((x_a[0] * y_c[0] - x_b[0] * y_d[0]) + x_c[0] * y_a[0]) + x_d[0] *
    y_b[0];
  o_d[0] = ((x_a[0] * y_d[0] + x_b[0] * y_c[0]) - x_c[0] * y_b[0]) + x_d[0] *
    y_a[0];
  o_a[1] = ((x_a[1] * y_a[1] - x_b[1] * y_b[1]) - x_c[1] * y_c[1]) - x_d[1] *
    y_d[1];
  o_b[1] = ((x_a[1] * y_b[1] + x_b[1] * y_a[1]) + x_c[1] * y_d[1]) - x_d[1] *
    y_c[1];
  o_c[1] = ((x_a[1] * y_c[1] - x_b[1] * y_d[1]) + x_c[1] * y_a[1]) + x_d[1] *
    y_b[1];
  o_d[1] = ((x_a[1] * y_d[1] + x_b[1] * y_c[1]) - x_c[1] * y_b[1]) + x_d[1] *
    y_a[1];
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
