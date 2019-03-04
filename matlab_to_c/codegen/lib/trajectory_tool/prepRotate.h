/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: prepRotate.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 26-Feb-2019 13:17:28
 */

#ifndef PREPROTATE_H
#define PREPROTATE_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "trajectory_tool_types.h"

/* Function Declarations */
extern void quaternionBase_prepRotate(const double q_a[1600], const double q_b
  [1600], const double q_c[1600], const double q_d[1600], const double v[4800],
  d_matlabshared_rotations_intern *qo, double qv_a[1600], double qv_b[1600],
  double qv_c[1600], double qv_d[1600]);

#endif

/*
 * File trailer for prepRotate.h
 *
 * [EOF]
 */
