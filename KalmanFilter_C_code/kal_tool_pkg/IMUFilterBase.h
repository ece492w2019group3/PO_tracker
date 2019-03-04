/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * IMUFilterBase.h
 *
 * Code generation for function 'IMUFilterBase'
 *
 */

#ifndef IMUFILTERBASE_H
#define IMUFILTERBASE_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "kal_tool_types.h"

/* Function Declarations */
extern void IMUFilterBase_stepImpl(c_fusion_internal_coder_imufilt *obj, const
  double accelIn[4800], const double gyroIn[4800],
  d_matlabshared_rotations_intern *orientOut);

#endif

/* End of code generation (IMUFilterBase.h) */
