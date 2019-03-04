/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: AHRSFilterBase.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 01-Mar-2019 15:09:29
 */

/* Include Files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "AHRSFilterBase.h"
#include "quaternioncg.h"
#include "atan2.h"
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

/*
 * Arguments    : c_fusion_internal_coder_ahrsfil *obj
 *                const double accelIn[4800]
 *                const double gyroIn[4800]
 *                const double magIn[4800]
 *                d_matlabshared_rotations_intern *orientOut
 *                double av[4800]
 * Return Type  : void
 */
void AHRSFilterBase_stepImpl(c_fusion_internal_coder_ahrsfil *obj, const double
  accelIn[4800], const double gyroIn[4800], const double magIn[4800],
  d_matlabshared_rotations_intern *orientOut, double av[4800])
{
  int i;
  int iter;
  double afastmat[4800];
  double mfastmat[4800];
  double dv1[4800];
  double b_obj[3];
  int afastmat_tmp;
  c_fusion_internal_coder_ahrsfil *r0;
  double Rprior[9];
  double d1;
  double inclination;
  double a;
  double d2;
  double gravityAccelGyroDiff[3];
  int gravityAccelGyroDiff_tmp;
  int b_gravityAccelGyroDiff_tmp;
  double h1[9];
  int i3;
  double b_Rprior[3];
  double h2[9];
  double H[72];
  int H_tmp;
  double Qw[144];
  static const signed char iv1[9] = { -1, 0, 0, 0, -1, 0, 0, 0, -1 };

  int i4;
  double K[72];
  double b_H[36];
  double c_H[72];
  double ze[6];
  boolean_T isJamming;
  double xe_post[12];
  double gyroOffsetErr_idx_0;
  double linAccelErr_idx_0;
  double gyroOffsetErr_idx_1;
  double linAccelErr_idx_1;
  double gyroOffsetErr_idx_2;
  double linAccelErr_idx_2;
  c_matlabshared_rotations_intern r1;
  double Ppost[144];
  for (i = 0; i < 1600; i++) {
    afastmat[3 * i] = accelIn[i];
    mfastmat[3 * i] = magIn[i];
    dv1[3 * i] = gyroIn[i];
    afastmat_tmp = 1 + 3 * i;
    afastmat[afastmat_tmp] = accelIn[i + 1600];
    mfastmat[afastmat_tmp] = magIn[i + 1600];
    dv1[afastmat_tmp] = gyroIn[i + 1600];
    afastmat_tmp = 2 + 3 * i;
    afastmat[afastmat_tmp] = accelIn[i + 3200];
    mfastmat[afastmat_tmp] = magIn[i + 3200];
    dv1[afastmat_tmp] = gyroIn[i + 3200];
    orientOut->a[i] = 0.0;
    orientOut->b[i] = 0.0;
    orientOut->c[i] = 0.0;
    orientOut->d[i] = 0.0;
  }

  for (iter = 0; iter < 1600; iter++) {
    c_IMUFusionCommon_computeAngula(*(double (*)[3])&dv1[3 * iter],
      obj->pGyroOffset, b_obj);
    av[iter] = b_obj[0];
    av[iter + 1600] = b_obj[1];
    av[iter + 3200] = b_obj[2];
    if (obj->pFirstTime) {
      obj->pFirstTime = false;
      NED_ecompass(*(double (*)[3])&afastmat[3 * iter], *(double (*)[3])&
                   mfastmat[3 * iter], Rprior);
      quaternioncg_quaternioncg(Rprior, &d1, &inclination, &a, &d2);
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
    c_IMUFusionCommon_predictOrient(r0, *(double (*)[3])&dv1[3 * iter], b_obj,
      &obj->pOrientPrior);
    quaternionBase_rotmat(obj->pOrientPrior.a, obj->pOrientPrior.b,
                          obj->pOrientPrior.c, obj->pOrientPrior.d, Rprior);
    a = obj->LinearAccelerationDecayFactor;
    obj->pLinAccelPrior[0] = a * obj->pLinAccelPost[0];
    obj->pLinAccelPrior[1] = a * obj->pLinAccelPost[1];
    obj->pLinAccelPrior[2] = a * obj->pLinAccelPost[2];
    gravityAccelGyroDiff[0] = (afastmat[3 * iter] + obj->pLinAccelPrior[0]) -
      Rprior[6];
    gravityAccelGyroDiff_tmp = 1 + 3 * iter;
    gravityAccelGyroDiff[1] = (afastmat[gravityAccelGyroDiff_tmp] +
      obj->pLinAccelPrior[1]) - Rprior[7];
    b_gravityAccelGyroDiff_tmp = 2 + 3 * iter;
    gravityAccelGyroDiff[2] = (afastmat[b_gravityAccelGyroDiff_tmp] +
      obj->pLinAccelPrior[2]) - Rprior[8];
    IMUFusionCommon_buildHPart(*(double (*)[3])&Rprior[6], h1);
    for (i3 = 0; i3 < 3; i3++) {
      b_Rprior[i3] = 0.0;
      d1 = Rprior[i3] * obj->pMagVec[0];
      d1 += Rprior[i3 + 3] * obj->pMagVec[1];
      d1 += Rprior[i3 + 6] * obj->pMagVec[2];
      b_Rprior[i3] = d1;
    }

    for (i3 = 0; i3 < 3; i3++) {
      b_obj[i3] = b_Rprior[i3];
      H[6 * i3] = h1[3 * i3];
      H[1 + 6 * i3] = h1[1 + 3 * i3];
      H[2 + 6 * i3] = h1[2 + 3 * i3];
    }

    IMUFusionCommon_buildHPart(b_obj, h2);
    for (i3 = 0; i3 < 3; i3++) {
      H_tmp = 6 * (i3 + 3);
      H[H_tmp] = -h1[3 * i3] * obj->pKalmanPeriod;
      H[1 + H_tmp] = -h1[1 + 3 * i3] * obj->pKalmanPeriod;
      H[2 + H_tmp] = -h1[2 + 3 * i3] * obj->pKalmanPeriod;
    }

    for (i3 = 0; i3 < 3; i3++) {
      H_tmp = 6 * (i3 + 6);
      H[H_tmp] = iv0[3 * i3];
      i = 6 * (i3 + 9);
      H[i] = 0.0;
      H[6 * i3 + 3] = h2[3 * i3];
      afastmat_tmp = 1 + 3 * i3;
      H[1 + H_tmp] = iv0[afastmat_tmp];
      H[1 + i] = 0.0;
      H[6 * i3 + 4] = h2[afastmat_tmp];
      afastmat_tmp = 2 + 3 * i3;
      H[2 + H_tmp] = iv0[afastmat_tmp];
      H[2 + i] = 0.0;
      H[6 * i3 + 5] = h2[afastmat_tmp];
    }

    for (i3 = 0; i3 < 3; i3++) {
      H_tmp = 6 * (i3 + 3);
      H[H_tmp + 3] = -h2[3 * i3] * obj->pKalmanPeriod;
      H[H_tmp + 4] = -h2[1 + 3 * i3] * obj->pKalmanPeriod;
      H[H_tmp + 5] = -h2[2 + 3 * i3] * obj->pKalmanPeriod;
    }

    for (i3 = 0; i3 < 3; i3++) {
      H_tmp = 6 * (i3 + 6);
      H[H_tmp + 3] = 0.0;
      i = 6 * (i3 + 9);
      H[i + 3] = iv1[3 * i3];
      H[H_tmp + 4] = 0.0;
      H[i + 4] = iv1[1 + 3 * i3];
      H[H_tmp + 5] = 0.0;
      H[i + 5] = iv1[2 + 3 * i3];
    }

    for (i3 = 0; i3 < 144; i3++) {
      Qw[i3] = obj->pQw[i3];
    }

    for (i3 = 0; i3 < 12; i3++) {
      for (i4 = 0; i4 < 6; i4++) {
        i = i3 + 12 * i4;
        K[i] = 0.0;
        d1 = 0.0;
        for (afastmat_tmp = 0; afastmat_tmp < 12; afastmat_tmp++) {
          d1 += Qw[i3 + 12 * afastmat_tmp] * H[i4 + 6 * afastmat_tmp];
        }

        K[i] = d1;
      }
    }

    for (i3 = 0; i3 < 6; i3++) {
      for (i4 = 0; i4 < 12; i4++) {
        H_tmp = i3 + 6 * i4;
        c_H[H_tmp] = 0.0;
        d1 = 0.0;
        for (afastmat_tmp = 0; afastmat_tmp < 12; afastmat_tmp++) {
          d1 += H[i3 + 6 * afastmat_tmp] * Qw[afastmat_tmp + 12 * i4];
        }

        c_H[H_tmp] = d1;
      }
    }

    for (i3 = 0; i3 < 6; i3++) {
      for (i4 = 0; i4 < 6; i4++) {
        d1 = 0.0;
        for (afastmat_tmp = 0; afastmat_tmp < 12; afastmat_tmp++) {
          d1 += c_H[i4 + 6 * afastmat_tmp] * H[i3 + 6 * afastmat_tmp];
        }

        b_H[i3 + 6 * i4] = d1 + obj->pQv[i4 + 6 * i3];
      }
    }

    mrdivide_helper(K, b_H);
    for (i3 = 0; i3 < 3; i3++) {
      b_Rprior[i3] = 0.0;
      d1 = Rprior[i3] * obj->pMagVec[0];
      d1 += Rprior[i3 + 3] * obj->pMagVec[1];
      d1 += Rprior[i3 + 6] * obj->pMagVec[2];
      b_Rprior[i3] = d1;
    }

    ze[0] = gravityAccelGyroDiff[0];
    ze[3] = mfastmat[3 * iter] - b_Rprior[0];
    ze[1] = gravityAccelGyroDiff[1];
    ze[4] = mfastmat[gravityAccelGyroDiff_tmp] - b_Rprior[1];
    ze[2] = gravityAccelGyroDiff[2];
    ze[5] = mfastmat[b_gravityAccelGyroDiff_tmp] - b_Rprior[2];
    for (i3 = 0; i3 < 3; i3++) {
      b_obj[i3] = 0.0;
      d1 = 0.0;
      for (i4 = 0; i4 < 6; i4++) {
        d1 += K[(i3 + 12 * i4) + 9] * ze[i4];
      }

      b_obj[i3] = d1;
    }

    a = b_norm(b_obj);
    inclination = obj->ExpectedMagneticFieldStrength;
    isJamming = (a * a > 4.0 * (inclination * inclination));
    if (isJamming) {
      for (i3 = 0; i3 < 9; i3++) {
        Rprior[i3] = (K[i3] * gravityAccelGyroDiff[0] + K[i3 + 12] *
                      gravityAccelGyroDiff[1]) + K[i3 + 24] *
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
      for (i3 = 0; i3 < 12; i3++) {
        xe_post[i3] = 0.0;
        d1 = 0.0;
        for (i4 = 0; i4 < 6; i4++) {
          d1 += K[i3 + 12 * i4] * ze[i4];
        }

        xe_post[i3] = d1;
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
      for (i3 = 0; i3 < 3; i3++) {
        b_obj[i3] = 0.0;
        d1 = 0.0;
        for (i4 = 0; i4 < 6; i4++) {
          d1 += K[(i3 + 12 * i4) + 9] * ze[i4];
        }

        b_obj[i3] = d1;
      }

      for (i3 = 0; i3 < 3; i3++) {
        b_Rprior[i3] = 0.0;
        b_Rprior[i3] = (Rprior[3 * i3] * b_obj[0] + Rprior[1 + 3 * i3] * b_obj[1])
          + Rprior[2 + 3 * i3] * b_obj[2];
      }

      gravityAccelGyroDiff[0] = obj->pMagVec[0] - b_Rprior[0];
      gravityAccelGyroDiff[2] = obj->pMagVec[2] - b_Rprior[2];
      inclination = rt_atan2d_snf(gravityAccelGyroDiff[2], gravityAccelGyroDiff
        [0]);
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

    for (i3 = 0; i3 < 6; i3++) {
      for (i4 = 0; i4 < 12; i4++) {
        H_tmp = i3 + 6 * i4;
        c_H[H_tmp] = 0.0;
        d1 = 0.0;
        for (afastmat_tmp = 0; afastmat_tmp < 12; afastmat_tmp++) {
          d1 += H[i3 + 6 * afastmat_tmp] * Qw[afastmat_tmp + 12 * i4];
        }

        c_H[H_tmp] = d1;
      }
    }

    for (i3 = 0; i3 < 12; i3++) {
      for (i4 = 0; i4 < 12; i4++) {
        d1 = 0.0;
        for (afastmat_tmp = 0; afastmat_tmp < 6; afastmat_tmp++) {
          d1 += K[i3 + 12 * afastmat_tmp] * c_H[afastmat_tmp + 6 * i4];
        }

        i = i3 + 12 * i4;
        Ppost[i] = Qw[i] - d1;
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
    for (i3 = 0; i3 < 144; i3++) {
      obj->pQw[i3] = Qw[i3];
    }

    quaternioncg_parenAssign(orientOut, obj->pOrientPost.a, obj->pOrientPost.b,
      obj->pOrientPost.c, obj->pOrientPost.d, 1.0 + (double)iter);
  }
}

/*
 * Arguments    : c_fusion_internal_coder_ahrsfil *obj
 * Return Type  : void
 */
void c_AHRSFilterBase_updateMeasurem(c_fusion_internal_coder_ahrsfil *obj)
{
  double a;
  double b_a;
  int i1;
  double d0;
  int i2;
  a = obj->pKalmanPeriod;
  a = (obj->AccelerometerNoise + obj->LinearAccelerationNoise) + a * a *
    (obj->GyroscopeDriftNoise + obj->GyroscopeNoise);
  b_a = obj->pKalmanPeriod;
  b_a = (obj->MagnetometerNoise + obj->MagneticDisturbanceNoise) + b_a * b_a *
    (obj->GyroscopeDriftNoise + obj->GyroscopeNoise);
  memset(&obj->pQv[0], 0, 36U * sizeof(double));
  for (i1 = 0; i1 < 3; i1++) {
    d0 = iv0[3 * i1];
    obj->pQv[6 * i1] = a * d0;
    i2 = 6 * (3 + i1);
    obj->pQv[i2 + 3] = b_a * d0;
    d0 = iv0[1 + 3 * i1];
    obj->pQv[1 + 6 * i1] = a * d0;
    obj->pQv[i2 + 4] = b_a * d0;
    d0 = iv0[2 + 3 * i1];
    obj->pQv[2 + 6 * i1] = a * d0;
    obj->pQv[i2 + 5] = b_a * d0;
  }
}

/*
 * File trailer for AHRSFilterBase.c
 *
 * [EOF]
 */
