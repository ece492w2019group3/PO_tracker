/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: AHRSFilterBase.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 01-Mar-2019 15:09:29
 */

#ifndef AHRSFILTERBASE_H
#define AHRSFILTERBASE_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "kal_tool_types.h"

/* Function Declarations */
extern void AHRSFilterBase_stepImpl(c_fusion_internal_coder_ahrsfil *obj, const
  double accelIn[4800], const double gyroIn[4800], const double magIn[4800],
  d_matlabshared_rotations_intern *orientOut, double av[4800]);
extern void c_AHRSFilterBase_updateMeasurem(c_fusion_internal_coder_ahrsfil *obj);

#endif

/*
 * File trailer for AHRSFilterBase.h
 *
 * [EOF]
 */
