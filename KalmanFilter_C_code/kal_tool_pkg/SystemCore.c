/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SystemCore.c
 *
 * Code generation for function 'SystemCore'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "SystemCore.h"
#include "IMUFilterBase.h"

/* Function Definitions */
void SystemCore_parenReference(c_fusion_internal_coder_imufilt *obj, const
  double varargin_1[4800], const double varargin_2[4800], double varargout_1_a
  [1600], double varargout_1_b[1600], double varargout_1_c[1600], double
  varargout_1_d[1600])
{
  int i0;
  static d_matlabshared_rotations_intern expl_temp;
  double accelMeasNoiseVar;
  signed char b_I[9];
  static const double dv0[81] = { 6.0923483957341713E-6, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 6.0923483957341713E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 6.0923483957341713E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    7.6154354946677142E-5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    7.6154354946677142E-5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    7.6154354946677142E-5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0096236100000000012, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0096236100000000012, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0096236100000000012 };

  if (obj->isInitialized != 1) {
    obj->isInitialized = 1;
    for (i0 = 0; i0 < 4800; i0++) {
      obj->pInputPrototype[i0] = varargin_1[i0];
    }

    obj->pSensorPeriod = 0.01;
    obj->pKalmanPeriod = obj->pSensorPeriod;
    obj->TunablePropsChanged = false;
    obj->pOrientPost.a = 1.0;
    obj->pOrientPost.b = 0.0;
    obj->pOrientPost.c = 0.0;
    obj->pOrientPost.d = 0.0;
    obj->pGyroOffset[0] = 0.0;
    obj->pGyroOffset[1] = 0.0;
    obj->pGyroOffset[2] = 0.0;
    accelMeasNoiseVar = obj->pKalmanPeriod;
    accelMeasNoiseVar = (obj->AccelerometerNoise + obj->LinearAccelerationNoise)
      + accelMeasNoiseVar * accelMeasNoiseVar * (obj->GyroscopeDriftNoise +
      obj->GyroscopeNoise);
    for (i0 = 0; i0 < 9; i0++) {
      b_I[i0] = 0;
    }

    b_I[0] = 1;
    b_I[4] = 1;
    b_I[8] = 1;
    for (i0 = 0; i0 < 9; i0++) {
      obj->pQv[i0] = accelMeasNoiseVar * (double)b_I[i0];
    }

    for (i0 = 0; i0 < 81; i0++) {
      obj->pQw[i0] = dv0[i0];
    }

    obj->pLinAccelPost[0] = 0.0;
    obj->pLinAccelPost[1] = 0.0;
    obj->pLinAccelPost[2] = 0.0;
    obj->pFirstTime = true;
  }

  if (obj->TunablePropsChanged) {
    obj->TunablePropsChanged = false;
    accelMeasNoiseVar = obj->pKalmanPeriod;
    accelMeasNoiseVar = (obj->AccelerometerNoise + obj->LinearAccelerationNoise)
      + accelMeasNoiseVar * accelMeasNoiseVar * (obj->GyroscopeDriftNoise +
      obj->GyroscopeNoise);
    for (i0 = 0; i0 < 9; i0++) {
      b_I[i0] = 0;
    }

    b_I[0] = 1;
    b_I[4] = 1;
    b_I[8] = 1;
    for (i0 = 0; i0 < 9; i0++) {
      obj->pQv[i0] = accelMeasNoiseVar * (double)b_I[i0];
    }
  }

  IMUFilterBase_stepImpl(obj, varargin_1, varargin_2, &expl_temp);
  memcpy(&varargout_1_a[0], &expl_temp.a[0], 1600U * sizeof(double));
  memcpy(&varargout_1_b[0], &expl_temp.b[0], 1600U * sizeof(double));
  memcpy(&varargout_1_c[0], &expl_temp.c[0], 1600U * sizeof(double));
  memcpy(&varargout_1_d[0], &expl_temp.d[0], 1600U * sizeof(double));
}

/* End of code generation (SystemCore.c) */
