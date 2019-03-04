/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: IMUFusionCommon.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 01-Mar-2019 15:09:29
 */

#ifndef IMUFUSIONCOMMON_H
#define IMUFUSIONCOMMON_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "kal_tool_types.h"

/* Function Declarations */
extern void IMUFusionCommon_buildHPart(const double v[3], double h[9]);
extern void c_IMUFusionCommon_computeAngula(const double gfast[3], const double
  offset[3], double av[3]);
extern void c_IMUFusionCommon_predictOrient(const
  c_fusion_internal_coder_ahrsfil *obj, const double gfast[3], const double
  offset[3], c_matlabshared_rotations_intern *qorient);

#endif

/*
 * File trailer for IMUFusionCommon.h
 *
 * [EOF]
 */
