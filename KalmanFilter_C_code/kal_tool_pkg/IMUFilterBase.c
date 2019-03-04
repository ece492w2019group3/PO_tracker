/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * IMUFilterBase.c
 *
 * Code generation for function 'IMUFilterBase'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "IMUFilterBase.h"
#include "quaternioncg.h"
#include "normalize.h"
#include "uminus.h"
#include "mtimes.h"
#include "conj.h"
#include "mrdivide_helper.h"
#include "IMUFusionCommon.h"
#include "rotmat.h"
#include "NED.h"

/* Function Definitions */
void IMUFilterBase_stepImpl(c_fusion_internal_coder_imufilt *obj, const double
  accelIn[4800], const double gyroIn[4800], d_matlabshared_rotations_intern
  *orientOut)
{
  int i;
  int iter;
  double b_accelIn[4800];
  double dv1[4800];
  int accelIn_tmp;
  c_fusion_internal_coder_imufilt *r0;
  double h1[9];
  double d0;
  double a;
  double accelIn_idx_0;
  double accelIn_idx_2;
  double b_obj[3];
  double Rprior[9];
  int i1;
  double H[27];
  static const signed char iv0[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  double Qw[81];
  int i2;
  double y_tmp[27];
  double b_Qw[27];
  double b_tmp[27];
  c_matlabshared_rotations_intern r1;
  double Ppost[81];
  for (i = 0; i < 1600; i++) {
    b_accelIn[3 * i] = accelIn[i];
    dv1[3 * i] = gyroIn[i];
    accelIn_tmp = 1 + 3 * i;
    b_accelIn[accelIn_tmp] = accelIn[i + 1600];
    dv1[accelIn_tmp] = gyroIn[i + 1600];
    accelIn_tmp = 2 + 3 * i;
    b_accelIn[accelIn_tmp] = accelIn[i + 3200];
    dv1[accelIn_tmp] = gyroIn[i + 3200];
    orientOut->a[i] = 0.0;
    orientOut->b[i] = 0.0;
    orientOut->c[i] = 0.0;
    orientOut->d[i] = 0.0;
  }

  for (iter = 0; iter < 1600; iter++) {
    if (obj->pFirstTime) {
      obj->pFirstTime = false;
      NED_ecompass(*(double (*)[3])&b_accelIn[3 * iter], h1);
      quaternioncg_quaternioncg(h1, &d0, &a, &accelIn_idx_0, &accelIn_idx_2);
      obj->pOrientPost.d = accelIn_idx_2;
      obj->pOrientPost.c = accelIn_idx_0;
      obj->pOrientPost.b = a;
      obj->pOrientPost.a = d0;
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
    IMUFusionCommon_buildHPart(*(double (*)[3])&Rprior[6], h1);
    for (i1 = 0; i1 < 3; i1++) {
      H[3 * i1] = h1[3 * i1];
      i = 1 + 3 * i1;
      H[i] = h1[i];
      i = 2 + 3 * i1;
      H[i] = h1[i];
    }

    for (i1 = 0; i1 < 3; i1++) {
      i = 3 * (i1 + 3);
      H[i] = -h1[3 * i1] * obj->pKalmanPeriod;
      H[1 + i] = -h1[1 + 3 * i1] * obj->pKalmanPeriod;
      H[2 + i] = -h1[2 + 3 * i1] * obj->pKalmanPeriod;
    }

    for (i1 = 0; i1 < 3; i1++) {
      i = 3 * (i1 + 6);
      H[i] = iv0[3 * i1];
      H[1 + i] = iv0[1 + 3 * i1];
      H[2 + i] = iv0[2 + 3 * i1];
    }

    for (i1 = 0; i1 < 81; i1++) {
      Qw[i1] = obj->pQw[i1];
    }

    for (i1 = 0; i1 < 3; i1++) {
      for (i2 = 0; i2 < 9; i2++) {
        i = i1 + 3 * i2;
        y_tmp[i] = 0.0;
        d0 = 0.0;
        for (accelIn_tmp = 0; accelIn_tmp < 9; accelIn_tmp++) {
          d0 += H[i1 + 3 * accelIn_tmp] * Qw[accelIn_tmp + 9 * i2];
        }

        y_tmp[i] = d0;
        b_tmp[i2 + 9 * i1] = H[i];
      }
    }

    for (i1 = 0; i1 < 9; i1++) {
      for (i2 = 0; i2 < 3; i2++) {
        i = i1 + 9 * i2;
        b_Qw[i] = 0.0;
        d0 = 0.0;
        for (accelIn_tmp = 0; accelIn_tmp < 9; accelIn_tmp++) {
          d0 += Qw[i1 + 9 * accelIn_tmp] * b_tmp[accelIn_tmp + 9 * i2];
        }

        b_Qw[i] = d0;
      }
    }

    for (i1 = 0; i1 < 3; i1++) {
      for (i2 = 0; i2 < 3; i2++) {
        d0 = 0.0;
        for (accelIn_tmp = 0; accelIn_tmp < 9; accelIn_tmp++) {
          d0 += y_tmp[i2 + 3 * accelIn_tmp] * b_tmp[accelIn_tmp + 9 * i1];
        }

        h1[i1 + 3 * i2] = d0 + obj->pQv[i2 + 3 * i1];
      }
    }

    mrdivide_helper(b_Qw, h1, H);
    accelIn_idx_0 = (b_accelIn[3 * iter] + obj->pLinAccelPrior[0]) - Rprior[6];
    a = (b_accelIn[1 + 3 * iter] + obj->pLinAccelPrior[1]) - Rprior[7];
    accelIn_idx_2 = (b_accelIn[2 + 3 * iter] + obj->pLinAccelPrior[2]) - Rprior
      [8];
    for (i1 = 0; i1 < 9; i1++) {
      h1[i1] = (H[i1] * accelIn_idx_0 + H[i1 + 9] * a) + H[i1 + 18] *
        accelIn_idx_2;
    }

    b_quaternioncg_quaternioncg(*(double (*)[3])&h1[0], &r1.a, &r1.b, &r1.c,
      &r1.d);
    quaternionBase_conj(&r1);
    quaternionBase_mtimes(obj->pOrientPrior.a, obj->pOrientPrior.b,
                          obj->pOrientPrior.c, obj->pOrientPrior.d, r1.a, r1.b,
                          r1.c, r1.d, &d0, &a, &accelIn_idx_0, &accelIn_idx_2);
    obj->pOrientPost.d = accelIn_idx_2;
    obj->pOrientPost.c = accelIn_idx_0;
    obj->pOrientPost.b = a;
    obj->pOrientPost.a = d0;
    if (obj->pOrientPost.a < 0.0) {
      quaternionBase_uminus(&obj->pOrientPost);
    }

    quaternionBase_normalize(&obj->pOrientPost);
    obj->pGyroOffset[0] -= h1[3];
    obj->pGyroOffset[1] -= h1[4];
    obj->pGyroOffset[2] -= h1[5];
    obj->pLinAccelPost[0] = obj->pLinAccelPrior[0] - h1[6];
    obj->pLinAccelPost[1] = obj->pLinAccelPrior[1] - h1[7];
    obj->pLinAccelPost[2] = obj->pLinAccelPrior[2] - h1[8];
    for (i1 = 0; i1 < 9; i1++) {
      for (i2 = 0; i2 < 9; i2++) {
        i = i1 + 9 * i2;
        Ppost[i] = Qw[i] - ((H[i1] * y_tmp[3 * i2] + H[i1 + 9] * y_tmp[1 + 3 *
                             i2]) + H[i1 + 18] * y_tmp[2 + 3 * i2]);
      }
    }

    memset(&Qw[0], 0, 81U * sizeof(double));
    a = obj->pKalmanPeriod;
    a *= a;
    accelIn_idx_0 = obj->GyroscopeDriftNoise + obj->GyroscopeNoise;
    Qw[0] = Ppost[0] + a * (Ppost[30] + accelIn_idx_0);
    Qw[10] = Ppost[10] + a * (Ppost[40] + accelIn_idx_0);
    Qw[20] = Ppost[20] + a * (Ppost[50] + accelIn_idx_0);
    Qw[30] = Ppost[30] + obj->GyroscopeDriftNoise;
    Qw[40] = Ppost[40] + obj->GyroscopeDriftNoise;
    Qw[50] = Ppost[50] + obj->GyroscopeDriftNoise;
    a = -obj->pKalmanPeriod;
    d0 = a * Qw[30];
    Qw[3] = d0;
    Qw[27] = d0;
    d0 = a * Qw[40];
    Qw[13] = d0;
    Qw[37] = d0;
    d0 = a * Qw[50];
    Qw[23] = d0;
    Qw[47] = d0;
    a = obj->LinearAccelerationDecayFactor;
    a *= a;
    Qw[60] = a * Ppost[60] + obj->LinearAccelerationNoise;
    Qw[70] = a * Ppost[70] + obj->LinearAccelerationNoise;
    Qw[80] = a * Ppost[80] + obj->LinearAccelerationNoise;
    for (i1 = 0; i1 < 81; i1++) {
      obj->pQw[i1] = Qw[i1];
    }

    quaternioncg_parenAssign(orientOut, obj->pOrientPost.a, obj->pOrientPost.b,
      obj->pOrientPost.c, obj->pOrientPost.d, 1.0 + (double)iter);
  }
}

/* End of code generation (IMUFilterBase.c) */
