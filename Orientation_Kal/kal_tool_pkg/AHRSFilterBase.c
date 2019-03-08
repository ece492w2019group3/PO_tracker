/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * AHRSFilterBase.c
 *
 * Code generation for function 'AHRSFilterBase'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "AHRSFilterBase.h"
#include "quaternioncg.h"
#include "rotmat.h"
#include "normalize.h"
#include "uminus.h"
#include "mtimes.h"
#include "conj.h"
#include "norm1.h"
#include "mrdivide_helper.h"
#include "IMUFusionCommon.h"
#include "NED.h"
#include "kal_tool_rtwutil.h"

/* Variable Definitions */
static const signed char iv0[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

/* Function Definitions */
void AHRSFilterBase_stepImpl(c_fusion_internal_coder_ahrsfil *obj, const double
  accelIn[3], const double gyroIn[3], const double magIn[3], double *orientOut_a,
  double *orientOut_b, double *orientOut_c, double *orientOut_d, double av[3])
{
  c_fusion_internal_coder_ahrsfil *r0;
  double dv1[9];
  double d1;
  double inclination;
  double a;
  double d2;
  double b_obj[3];
  double Rprior[9];
  double gravityAccelGyroDiff[3];
  double h1[9];
  int i2;
  double b_Rprior[3];
  double h2[9];
  double H[72];
  int H_tmp;
  int b_H_tmp;
  int c_H_tmp;
  double Qw[144];
  static const signed char iv1[9] = { -1, 0, 0, 0, -1, 0, 0, 0, -1 };

  int i3;
  double K[72];
  double b_H[36];
  double c_H[72];
  double ze[6];
  bool isJamming;
  double xe_post[12];
  double gyroOffsetErr_idx_0;
  double linAccelErr_idx_0;
  double gyroOffsetErr_idx_1;
  double linAccelErr_idx_1;
  double gyroOffsetErr_idx_2;
  double linAccelErr_idx_2;
  c_matlabshared_rotations_intern r1;
  double Ppost[144];
  c_IMUFusionCommon_computeAngula(gyroIn, obj->pGyroOffset, av);
  if (obj->pFirstTime) {
    obj->pFirstTime = false;
    NED_ecompass(accelIn, magIn, dv1);
    quaternioncg_quaternioncg(dv1, &d1, &inclination, &a, &d2);
    obj->pOrientPost.d = d2;
    obj->pOrientPost.c = a;
    obj->pOrientPost.b = inclination;
    obj->pOrientPost.a = d1;
  }

  r0 = obj;
  obj->pOrientPrior = obj->pOrientPost;
  b_obj[0] = obj->pGyroOffset[0];
  b_obj[1] = obj->pGyroOffset[1];
  b_obj[2] = obj->pGyroOffset[2];
  c_IMUFusionCommon_predictOrient(r0, gyroIn, b_obj, &obj->pOrientPrior);
  quaternionBase_rotmat(obj->pOrientPrior.a, obj->pOrientPrior.b,
                        obj->pOrientPrior.c, obj->pOrientPrior.d, Rprior);
  a = obj->LinearAccelerationDecayFactor;
  obj->pLinAccelPrior[0] = a * obj->pLinAccelPost[0];
  obj->pLinAccelPrior[1] = a * obj->pLinAccelPost[1];
  obj->pLinAccelPrior[2] = a * obj->pLinAccelPost[2];
  gravityAccelGyroDiff[0] = (accelIn[0] + obj->pLinAccelPrior[0]) - Rprior[6];
  gravityAccelGyroDiff[1] = (accelIn[1] + obj->pLinAccelPrior[1]) - Rprior[7];
  gravityAccelGyroDiff[2] = (accelIn[2] + obj->pLinAccelPrior[2]) - Rprior[8];
  IMUFusionCommon_buildHPart(*(double (*)[3])&Rprior[6], h1);
  for (i2 = 0; i2 < 3; i2++) {
    b_Rprior[i2] = 0.0;
    d1 = Rprior[i2] * obj->pMagVec[0];
    d1 += Rprior[i2 + 3] * obj->pMagVec[1];
    d1 += Rprior[i2 + 6] * obj->pMagVec[2];
    b_Rprior[i2] = d1;
  }

  for (i2 = 0; i2 < 3; i2++) {
    b_obj[i2] = b_Rprior[i2];
    H[6 * i2] = h1[3 * i2];
    H[1 + 6 * i2] = h1[1 + 3 * i2];
    H[2 + 6 * i2] = h1[2 + 3 * i2];
  }

  IMUFusionCommon_buildHPart(b_obj, h2);
  for (i2 = 0; i2 < 3; i2++) {
    H_tmp = 6 * (i2 + 3);
    H[H_tmp] = -h1[3 * i2] * obj->pKalmanPeriod;
    H[1 + H_tmp] = -h1[1 + 3 * i2] * obj->pKalmanPeriod;
    H[2 + H_tmp] = -h1[2 + 3 * i2] * obj->pKalmanPeriod;
  }

  for (i2 = 0; i2 < 3; i2++) {
    H_tmp = 6 * (i2 + 6);
    H[H_tmp] = iv0[3 * i2];
    b_H_tmp = 6 * (i2 + 9);
    H[b_H_tmp] = 0.0;
    H[6 * i2 + 3] = h2[3 * i2];
    c_H_tmp = 1 + 3 * i2;
    H[1 + H_tmp] = iv0[c_H_tmp];
    H[1 + b_H_tmp] = 0.0;
    H[6 * i2 + 4] = h2[c_H_tmp];
    c_H_tmp = 2 + 3 * i2;
    H[2 + H_tmp] = iv0[c_H_tmp];
    H[2 + b_H_tmp] = 0.0;
    H[6 * i2 + 5] = h2[c_H_tmp];
  }

  for (i2 = 0; i2 < 3; i2++) {
    H_tmp = 6 * (i2 + 3);
    H[H_tmp + 3] = -h2[3 * i2] * obj->pKalmanPeriod;
    H[H_tmp + 4] = -h2[1 + 3 * i2] * obj->pKalmanPeriod;
    H[H_tmp + 5] = -h2[2 + 3 * i2] * obj->pKalmanPeriod;
  }

  for (i2 = 0; i2 < 3; i2++) {
    H_tmp = 6 * (i2 + 6);
    H[H_tmp + 3] = 0.0;
    b_H_tmp = 6 * (i2 + 9);
    H[b_H_tmp + 3] = iv1[3 * i2];
    H[H_tmp + 4] = 0.0;
    H[b_H_tmp + 4] = iv1[1 + 3 * i2];
    H[H_tmp + 5] = 0.0;
    H[b_H_tmp + 5] = iv1[2 + 3 * i2];
  }

  for (i2 = 0; i2 < 144; i2++) {
    Qw[i2] = obj->pQw[i2];
  }

  for (i2 = 0; i2 < 12; i2++) {
    for (i3 = 0; i3 < 6; i3++) {
      b_H_tmp = i2 + 12 * i3;
      K[b_H_tmp] = 0.0;
      d1 = 0.0;
      for (c_H_tmp = 0; c_H_tmp < 12; c_H_tmp++) {
        d1 += Qw[i2 + 12 * c_H_tmp] * H[i3 + 6 * c_H_tmp];
      }

      K[b_H_tmp] = d1;
    }
  }

  for (i2 = 0; i2 < 6; i2++) {
    for (i3 = 0; i3 < 12; i3++) {
      H_tmp = i2 + 6 * i3;
      c_H[H_tmp] = 0.0;
      d1 = 0.0;
      for (c_H_tmp = 0; c_H_tmp < 12; c_H_tmp++) {
        d1 += H[i2 + 6 * c_H_tmp] * Qw[c_H_tmp + 12 * i3];
      }

      c_H[H_tmp] = d1;
    }
  }

  for (i2 = 0; i2 < 6; i2++) {
    for (i3 = 0; i3 < 6; i3++) {
      d1 = 0.0;
      for (c_H_tmp = 0; c_H_tmp < 12; c_H_tmp++) {
        d1 += c_H[i3 + 6 * c_H_tmp] * H[i2 + 6 * c_H_tmp];
      }

      b_H[i2 + 6 * i3] = d1 + obj->pQv[i3 + 6 * i2];
    }
  }

  mrdivide_helper(K, b_H);
  for (i2 = 0; i2 < 3; i2++) {
    b_Rprior[i2] = 0.0;
    d1 = Rprior[i2] * obj->pMagVec[0];
    d1 += Rprior[i2 + 3] * obj->pMagVec[1];
    d1 += Rprior[i2 + 6] * obj->pMagVec[2];
    b_Rprior[i2] = d1;
  }

  ze[0] = gravityAccelGyroDiff[0];
  ze[3] = magIn[0] - b_Rprior[0];
  ze[1] = gravityAccelGyroDiff[1];
  ze[4] = magIn[1] - b_Rprior[1];
  ze[2] = gravityAccelGyroDiff[2];
  ze[5] = magIn[2] - b_Rprior[2];
  for (i2 = 0; i2 < 3; i2++) {
    b_obj[i2] = 0.0;
    d1 = 0.0;
    for (i3 = 0; i3 < 6; i3++) {
      d1 += K[(i2 + 12 * i3) + 9] * ze[i3];
    }

    b_obj[i2] = d1;
  }

  a = b_norm(b_obj);
  inclination = obj->ExpectedMagneticFieldStrength;
  isJamming = (a * a > 4.0 * (inclination * inclination));
  if (isJamming) {
    for (i2 = 0; i2 < 9; i2++) {
      Rprior[i2] = (K[i2] * gravityAccelGyroDiff[0] + K[i2 + 12] *
                    gravityAccelGyroDiff[1]) + K[i2 + 24] *
        gravityAccelGyroDiff[2];
    }

    gravityAccelGyroDiff[0] = Rprior[0];
    gyroOffsetErr_idx_0 = Rprior[3];
    linAccelErr_idx_0 = Rprior[6];
    gravityAccelGyroDiff[1] = Rprior[1];
    gyroOffsetErr_idx_1 = Rprior[4];
    linAccelErr_idx_1 = Rprior[7];
    gravityAccelGyroDiff[2] = Rprior[2];
    gyroOffsetErr_idx_2 = Rprior[5];
    linAccelErr_idx_2 = Rprior[8];
  } else {
    for (i2 = 0; i2 < 12; i2++) {
      xe_post[i2] = 0.0;
      d1 = 0.0;
      for (i3 = 0; i3 < 6; i3++) {
        d1 += K[i2 + 12 * i3] * ze[i3];
      }

      xe_post[i2] = d1;
    }

    gravityAccelGyroDiff[0] = xe_post[0];
    gyroOffsetErr_idx_0 = xe_post[3];
    linAccelErr_idx_0 = xe_post[6];
    gravityAccelGyroDiff[1] = xe_post[1];
    gyroOffsetErr_idx_1 = xe_post[4];
    linAccelErr_idx_1 = xe_post[7];
    gravityAccelGyroDiff[2] = xe_post[2];
    gyroOffsetErr_idx_2 = xe_post[5];
    linAccelErr_idx_2 = xe_post[8];
  }

  b_quaternioncg_quaternioncg(gravityAccelGyroDiff, &r1.a, &r1.b, &r1.c, &r1.d);
  quaternionBase_conj(&r1);
  quaternionBase_mtimes(obj->pOrientPrior.a, obj->pOrientPrior.b,
                        obj->pOrientPrior.c, obj->pOrientPrior.d, r1.a, r1.b,
                        r1.c, r1.d, &d1, &inclination, &a, &d2);
  obj->pOrientPost.d = d2;
  obj->pOrientPost.c = a;
  obj->pOrientPost.b = inclination;
  obj->pOrientPost.a = d1;
  if (obj->pOrientPost.a < 0.0) {
    quaternionBase_uminus(&obj->pOrientPost);
  }

  quaternionBase_normalize(&obj->pOrientPost);
  quaternionBase_rotmat(obj->pOrientPost.a, obj->pOrientPost.b,
                        obj->pOrientPost.c, obj->pOrientPost.d, Rprior);
  obj->pGyroOffset[0] -= gyroOffsetErr_idx_0;
  obj->pGyroOffset[1] -= gyroOffsetErr_idx_1;
  obj->pGyroOffset[2] -= gyroOffsetErr_idx_2;
  obj->pLinAccelPost[0] = obj->pLinAccelPrior[0] - linAccelErr_idx_0;
  obj->pLinAccelPost[1] = obj->pLinAccelPrior[1] - linAccelErr_idx_1;
  obj->pLinAccelPost[2] = obj->pLinAccelPrior[2] - linAccelErr_idx_2;
  if (!isJamming) {
    for (i2 = 0; i2 < 3; i2++) {
      b_obj[i2] = 0.0;
      d1 = 0.0;
      for (i3 = 0; i3 < 6; i3++) {
        d1 += K[(i2 + 12 * i3) + 9] * ze[i3];
      }

      b_obj[i2] = d1;
    }

    for (i2 = 0; i2 < 3; i2++) {
      b_Rprior[i2] = 0.0;
      b_Rprior[i2] = (Rprior[3 * i2] * b_obj[0] + Rprior[1 + 3 * i2] * b_obj[1])
        + Rprior[2 + 3 * i2] * b_obj[2];
    }

    gravityAccelGyroDiff[0] = obj->pMagVec[0] - b_Rprior[0];
    gravityAccelGyroDiff[2] = obj->pMagVec[2] - b_Rprior[2];
    inclination = rt_atan2d_snf(gravityAccelGyroDiff[2], gravityAccelGyroDiff[0]);
    if (inclination < -1.5707963267948966) {
      inclination = -1.5707963267948966;
    }

    if (inclination > 1.5707963267948966) {
      inclination = 1.5707963267948966;
    }

    obj->pMagVec[0] = 0.0;
    obj->pMagVec[1] = 0.0;
    obj->pMagVec[2] = 0.0;
    obj->pMagVec[0] = cos(inclination);
    obj->pMagVec[2] = sin(inclination);
    obj->pMagVec[0] *= obj->ExpectedMagneticFieldStrength;
    obj->pMagVec[1] *= obj->ExpectedMagneticFieldStrength;
    obj->pMagVec[2] *= obj->ExpectedMagneticFieldStrength;
  }

  for (i2 = 0; i2 < 6; i2++) {
    for (i3 = 0; i3 < 12; i3++) {
      H_tmp = i2 + 6 * i3;
      c_H[H_tmp] = 0.0;
      d1 = 0.0;
      for (c_H_tmp = 0; c_H_tmp < 12; c_H_tmp++) {
        d1 += H[i2 + 6 * c_H_tmp] * Qw[c_H_tmp + 12 * i3];
      }

      c_H[H_tmp] = d1;
    }
  }

  for (i2 = 0; i2 < 12; i2++) {
    for (i3 = 0; i3 < 12; i3++) {
      d1 = 0.0;
      for (c_H_tmp = 0; c_H_tmp < 6; c_H_tmp++) {
        d1 += K[i2 + 12 * c_H_tmp] * c_H[c_H_tmp + 6 * i3];
      }

      b_H_tmp = i2 + 12 * i3;
      Ppost[b_H_tmp] = Qw[b_H_tmp] - d1;
    }
  }

  memset(&Qw[0], 0, 144U * sizeof(double));
  a = obj->pKalmanPeriod;
  a *= a;
  inclination = obj->GyroscopeDriftNoise + obj->GyroscopeNoise;
  Qw[0] = Ppost[0] + a * (Ppost[39] + inclination);
  Qw[13] = Ppost[13] + a * (Ppost[52] + inclination);
  Qw[26] = Ppost[26] + a * (Ppost[65] + inclination);
  Qw[39] = Ppost[39] + obj->GyroscopeDriftNoise;
  Qw[52] = Ppost[52] + obj->GyroscopeDriftNoise;
  Qw[65] = Ppost[65] + obj->GyroscopeDriftNoise;
  a = -obj->pKalmanPeriod;
  d1 = a * Qw[39];
  Qw[3] = d1;
  Qw[36] = d1;
  d1 = a * Qw[52];
  Qw[16] = d1;
  Qw[49] = d1;
  d1 = a * Qw[65];
  Qw[29] = d1;
  Qw[62] = d1;
  a = obj->LinearAccelerationDecayFactor;
  a *= a;
  Qw[78] = a * Ppost[78] + obj->LinearAccelerationNoise;
  Qw[91] = a * Ppost[91] + obj->LinearAccelerationNoise;
  Qw[104] = a * Ppost[104] + obj->LinearAccelerationNoise;
  a = obj->MagneticDisturbanceDecayFactor;
  a *= a;
  Qw[117] = a * Ppost[117] + obj->MagneticDisturbanceNoise;
  Qw[130] = a * Ppost[130] + obj->MagneticDisturbanceNoise;
  Qw[143] = a * Ppost[143] + obj->MagneticDisturbanceNoise;
  for (i2 = 0; i2 < 144; i2++) {
    obj->pQw[i2] = Qw[i2];
  }

  quaternioncg_parenAssign(obj->pOrientPost.a, obj->pOrientPost.b,
    obj->pOrientPost.c, obj->pOrientPost.d, orientOut_a, orientOut_b,
    orientOut_c, orientOut_d);
}

void c_AHRSFilterBase_updateMeasurem(c_fusion_internal_coder_ahrsfil *obj)
{
  double a;
  double b_a;
  int i0;
  double d0;
  int i1;
  a = obj->pKalmanPeriod;
  a = (obj->AccelerometerNoise + obj->LinearAccelerationNoise) + a * a *
    (obj->GyroscopeDriftNoise + obj->GyroscopeNoise);
  b_a = obj->pKalmanPeriod;
  b_a = (obj->MagnetometerNoise + obj->MagneticDisturbanceNoise) + b_a * b_a *
    (obj->GyroscopeDriftNoise + obj->GyroscopeNoise);
  memset(&obj->pQv[0], 0, 36U * sizeof(double));
  for (i0 = 0; i0 < 3; i0++) {
    d0 = iv0[3 * i0];
    obj->pQv[6 * i0] = a * d0;
    i1 = 6 * (3 + i0);
    obj->pQv[i1 + 3] = b_a * d0;
    d0 = iv0[1 + 3 * i0];
    obj->pQv[1 + 6 * i0] = a * d0;
    obj->pQv[i1 + 4] = b_a * d0;
    d0 = iv0[2 + 3 * i0];
    obj->pQv[2 + 6 * i0] = a * d0;
    obj->pQv[i1 + 5] = b_a * d0;
  }
}

/* End of code generation (AHRSFilterBase.c) */
