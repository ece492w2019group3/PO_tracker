/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mtimes.c
 *
 * Code generation for function 'mtimes'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "mtimes.h"

/* Function Definitions */
void quaternionBase_mtimes(double x_a, double x_b, double x_c, double x_d,
  double y_a, double y_b, double y_c, double y_d, double *o_a, double *o_b,
  double *o_c, double *o_d)
{
  *o_a = ((x_a * y_a - x_b * y_b) - x_c * y_c) - x_d * y_d;
  *o_b = ((x_a * y_b + x_b * y_a) + x_c * y_d) - x_d * y_c;
  *o_c = ((x_a * y_c - x_b * y_d) + x_c * y_a) + x_d * y_b;
  *o_d = ((x_a * y_d + x_b * y_c) - x_c * y_b) + x_d * y_a;
}

/* End of code generation (mtimes.c) */
