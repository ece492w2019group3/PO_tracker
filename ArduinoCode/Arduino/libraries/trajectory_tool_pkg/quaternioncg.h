/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: quaternioncg.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 30-Mar-2019 15:04:56
 */

#ifndef QUATERNIONCG_H
#define QUATERNIONCG_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "trajectory_tool_types.h"

/* Function Declarations */
extern void b_quaternioncg_times(const double x_a[2], const double x_b[2], const
  double x_c[2], const double x_d[2], const double y_a[2], const double y_b[2],
  const double y_c[2], const double y_d[2], double o_a[2], double o_b[2], double
  o_c[2], double o_d[2]);
extern void quaternioncg_times(double x_a, double x_b, double x_c, double x_d,
  double y_a, double y_b, double y_c, double y_d, double *o_a, double *o_b,
  double *o_c, double *o_d);

#endif

/*
 * File trailer for quaternioncg.h
 *
 * [EOF]
 */
