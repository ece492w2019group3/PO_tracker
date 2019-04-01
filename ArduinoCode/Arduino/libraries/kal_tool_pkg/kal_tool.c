/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * kal_tool.c
 *
 * Code generation for function 'kal_tool'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "AHRSFilterBase.h"
#include "kal_tool_rtwutil.h"

/* Function Definitions */
void kal_tool(const double acc[3], const double gyro[3], const double mag[3],
              double orientationEuler_kal[3], double angularVelocity[3])
{
  c_fusion_internal_coder_ahrsfil FUSE;
  static const double dv0[144] = { 6.0923483957341713E-6, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6.0923483957341713E-6, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6.0923483957341713E-6, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 7.6154354946677142E-5, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 7.6154354946677142E-5,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    7.6154354946677142E-5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0096236100000000012, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0096236100000000012, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0096236100000000012, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.6 };

  double varargout_1_a;
  double varargout_1_b;
  double varargout_1_c;
  double varargout_1_d;
  double n;
  double orientationEuler_kal_tmp;

  /*  FUSE = ahrsfilter('AccelerometerNoise', 0.001, 'GyroscopeNoise', 0.001, 'MagnetometerNoise', 0.001); */
  FUSE.MagnetometerNoise = 0.1;
  FUSE.MagneticDisturbanceNoise = 0.5;
  FUSE.MagneticDisturbanceDecayFactor = 0.5;
  FUSE.ExpectedMagneticFieldStrength = 50.0;
  FUSE.AccelerometerNoise = 0.0001924722;
  FUSE.GyroscopeNoise = 9.1385E-5;
  FUSE.GyroscopeDriftNoise = 3.0462E-13;
  FUSE.LinearAccelerationNoise = 0.0096236100000000012;
  FUSE.LinearAccelerationDecayFactor = 0.5;

  /*  mu = [0 0 0]; */
  /*  sigma = [0.001 0 0; 0 0.001 0; 0 0 0.001]; */
  /*  R = chol(sigma); */
  /*  r1 = repmat(mu,1,1) + randn(1,3)*R;  */
  /*  r2 = repmat(mu,1,1) + randn(1,3)*R; */
  /*  r3 = repmat(mu,1,1) + randn(1,3)*R; */
  /*  acc = acc + r1; */
  /*  gyro = gyro + r2; */
  /*  mag = mag + r3; */
  /*  t = acc1 +1 */
  FUSE.isInitialized = 1;
  FUSE.pInputPrototype[0] = acc[0];
  FUSE.pInputPrototype[1] = acc[1];
  FUSE.pInputPrototype[2] = acc[2];
  FUSE.pSensorPeriod = 1/57600;
  FUSE.pKalmanPeriod = 1/57600;
  FUSE.TunablePropsChanged = false;
  FUSE.pOrientPost.a = 1.0;
  FUSE.pOrientPost.b = 0.0;
  FUSE.pOrientPost.c = 0.0;
  FUSE.pOrientPost.d = 0.0;
  FUSE.pGyroOffset[0] = 0.0;
  FUSE.pGyroOffset[1] = 0.0;
  FUSE.pGyroOffset[2] = 0.0;
  FUSE.pMagVec[0] = 0.0;
  FUSE.pMagVec[1] = 0.0;
  FUSE.pMagVec[2] = 0.0;
  FUSE.pMagVec[0] = 50.0;
  c_AHRSFilterBase_updateMeasurem(&FUSE);
  memcpy(&FUSE.pQw[0], &dv0[0], 144U * sizeof(double));
  FUSE.pLinAccelPost[0] = 0.0;
  FUSE.pLinAccelPost[1] = 0.0;
  FUSE.pLinAccelPost[2] = 0.0;
  FUSE.pFirstTime = true;
  if (FUSE.TunablePropsChanged) {
    FUSE.TunablePropsChanged = false;
    c_AHRSFilterBase_updateMeasurem(&FUSE);
  }

  AHRSFilterBase_stepImpl(&FUSE, acc, gyro, mag, &varargout_1_a, &varargout_1_b,
    &varargout_1_c, &varargout_1_d, angularVelocity);
  n = sqrt(((varargout_1_a * varargout_1_a + varargout_1_b * varargout_1_b) +
            varargout_1_c * varargout_1_c) + varargout_1_d * varargout_1_d);
  varargout_1_a /= n;
  varargout_1_b /= n;
  varargout_1_c /= n;
  varargout_1_d /= n;
  n = varargout_1_b * varargout_1_d * 2.0 - varargout_1_a * varargout_1_c * 2.0;
  if (n > 1.0) {
    n = 1.0;
  }

  if (n < -1.0) {
    n = -1.0;
  }

  orientationEuler_kal_tmp = varargout_1_a * varargout_1_a * 2.0 - 1.0;
  orientationEuler_kal[0] = 57.295779513082323 * rt_atan2d_snf(varargout_1_a *
    varargout_1_d * 2.0 + varargout_1_b * varargout_1_c * 2.0,
    orientationEuler_kal_tmp + varargout_1_b * varargout_1_b * 2.0);
  orientationEuler_kal[1] = 57.295779513082323 * -asin(n);
  orientationEuler_kal[2] = 57.295779513082323 * rt_atan2d_snf(varargout_1_a *
    varargout_1_b * 2.0 + varargout_1_c * varargout_1_d * 2.0,
    orientationEuler_kal_tmp + varargout_1_d * varargout_1_d * 2.0);
}

/* End of code generation (kal_tool.c) */
