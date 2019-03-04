/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: quaternioncg.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 01-Mar-2019 15:09:29
 */

#ifndef QUATERNIONCG_H
#define QUATERNIONCG_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "kal_tool_types.h"

/* Function Declarations */
extern void b_quaternioncg_quaternioncg(const double varargin_1[3], double
  *obj_a, double *obj_b, double *obj_c, double *obj_d);
extern void quaternioncg_parenAssign(d_matlabshared_rotations_intern *obj,
  double rhs_a, double rhs_b, double rhs_c, double rhs_d, double varargin_1);
extern void quaternioncg_quaternioncg(const double varargin_1[9], double *obj_a,
  double *obj_b, double *obj_c, double *obj_d);

#endif

/*
 * File trailer for quaternioncg.h
 *
 * [EOF]
 */
