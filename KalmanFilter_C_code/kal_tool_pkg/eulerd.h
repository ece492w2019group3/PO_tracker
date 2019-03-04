/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * eulerd.h
 *
 * Code generation for function 'eulerd'
 *
 */

#ifndef EULERD_H
#define EULERD_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "kal_tool_types.h"

/* Function Declarations */
extern void quaternionBase_eulerd(const double q_a[1600], const double q_b[1600],
  const double q_c[1600], const double q_d[1600], double a[4800]);

#endif

/* End of code generation (eulerd.h) */
