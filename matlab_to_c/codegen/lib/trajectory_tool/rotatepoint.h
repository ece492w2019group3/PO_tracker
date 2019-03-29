/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: rotatepoint.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 27-Mar-2019 12:24:35
 */

#ifndef ROTATEPOINT_H
#define ROTATEPOINT_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "trajectory_tool_types.h"

/* Function Declarations */
extern void quaternionBase_rotatepoint(const double q_a[2], const double q_b[2],
  const double q_c[2], const double q_d[2], const double v[6], double u[6]);

#endif

/*
 * File trailer for rotatepoint.h
 *
 * [EOF]
 */
