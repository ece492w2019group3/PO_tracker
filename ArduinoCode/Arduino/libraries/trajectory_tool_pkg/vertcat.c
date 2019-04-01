/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: vertcat.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 30-Mar-2019 15:04:56
 */

/* Include Files */
#include "trajectory_tool.h"
#include "vertcat.h"

/* Function Definitions */

/*
 * Arguments    : double obj_a
 *                double obj_b
 *                double obj_c
 *                double obj_d
 *                double varargin_1_a
 *                double varargin_1_b
 *                double varargin_1_c
 *                double varargin_1_d
 *                double y_a[2]
 *                double y_b[2]
 *                double y_c[2]
 *                double y_d[2]
 * Return Type  : void
 */
void quaternionBase_vertcat(double obj_a, double obj_b, double obj_c, double
  obj_d, double varargin_1_a, double varargin_1_b, double varargin_1_c, double
  varargin_1_d, double y_a[2], double y_b[2], double y_c[2], double y_d[2])
{
  y_a[0] = obj_a;
  y_a[1] = varargin_1_a;
  y_b[0] = obj_b;
  y_b[1] = varargin_1_b;
  y_c[0] = obj_c;
  y_c[1] = varargin_1_c;
  y_d[0] = obj_d;
  y_d[1] = varargin_1_d;
}

/*
 * File trailer for vertcat.c
 *
 * [EOF]
 */
