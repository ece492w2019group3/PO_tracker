/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: ahrsfiltercg.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 01-Mar-2019 15:09:29
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "ahrsfiltercg.h"

/* Function Definitions */

/*
 * Arguments    : c_fusion_internal_coder_ahrsfil *obj
 * Return Type  : c_fusion_internal_coder_ahrsfil *
 */
c_fusion_internal_coder_ahrsfil *ahrsfiltercg_ahrsfiltercg
  (c_fusion_internal_coder_ahrsfil *obj)
{
  c_fusion_internal_coder_ahrsfil *b_obj;
  boolean_T flag;
  b_obj = obj;
  b_obj->MagneticDisturbanceNoise = 0.5;
  b_obj->MagneticDisturbanceDecayFactor = 0.5;
  b_obj->ExpectedMagneticFieldStrength = 50.0;
  b_obj->GyroscopeDriftNoise = 3.0462E-13;
  b_obj->LinearAccelerationNoise = 0.0096236100000000012;
  b_obj->LinearAccelerationDecayFactor = 0.5;
  b_obj->isInitialized = 0;
  flag = (b_obj->isInitialized == 1);
  if (flag) {
    b_obj->TunablePropsChanged = true;
  }

  b_obj->AccelerometerNoise = 0.001;
  flag = (b_obj->isInitialized == 1);
  if (flag) {
    b_obj->TunablePropsChanged = true;
  }

  b_obj->GyroscopeNoise = 0.001;
  flag = (b_obj->isInitialized == 1);
  if (flag) {
    b_obj->TunablePropsChanged = true;
  }

  b_obj->MagnetometerNoise = 0.001;
  return b_obj;
}

/*
 * File trailer for ahrsfiltercg.c
 *
 * [EOF]
 */
