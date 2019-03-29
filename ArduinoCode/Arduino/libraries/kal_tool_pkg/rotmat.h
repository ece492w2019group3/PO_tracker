/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * rotmat.h
 *
 * Code generation for function 'rotmat'
 *
 */

#ifndef ROTMAT_H
#define ROTMAT_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "kal_tool_types.h"

/* Function Declarations */
extern void quaternionBase_rotmat(double q_a, double q_b, double q_c, double q_d,
  double r[9]);

#endif

/* End of code generation (rotmat.h) */
