/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * AHRSFilterBase.h
 *
 * Code generation for function 'AHRSFilterBase'
 *
 */

#ifndef AHRSFILTERBASE_H
#define AHRSFILTERBASE_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "kal_tool_types.h"

/* Function Declarations */
extern void AHRSFilterBase_stepImpl(c_fusion_internal_coder_ahrsfil *obj, const
  double accelIn[3], const double gyroIn[3], const double magIn[3], double
  *orientOut_a, double *orientOut_b, double *orientOut_c, double *orientOut_d,
  double av[3]);
extern void c_AHRSFilterBase_updateMeasurem(c_fusion_internal_coder_ahrsfil *obj);

#endif

/* End of code generation (AHRSFilterBase.h) */
