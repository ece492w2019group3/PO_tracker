/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * quaternioncg.h
 *
 * Code generation for function 'quaternioncg'
 *
 */

#ifndef QUATERNIONCG_H
#define QUATERNIONCG_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "kal_tool_types.h"

/* Function Declarations */
extern void b_quaternioncg_quaternioncg(const double varargin_1[3], double
  *obj_a, double *obj_b, double *obj_c, double *obj_d);
extern void quaternioncg_parenAssign(double rhs_a, double rhs_b, double rhs_c,
  double rhs_d, double *o_a, double *o_b, double *o_c, double *o_d);
extern void quaternioncg_quaternioncg(const double varargin_1[9], double *obj_a,
  double *obj_b, double *obj_c, double *obj_d);

#endif

/* End of code generation (quaternioncg.h) */
