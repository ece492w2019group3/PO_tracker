/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: kal_tool.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 01-Mar-2019 15:09:29
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "eulerd.h"
#include "SystemCore.h"
#include "randn.h"
#include "rng.h"
#include "ahrsfiltercg.h"

/* Function Definitions */

/*
 * Arguments    : double acc[4800]
 *                double gyro[4800]
 *                double mag[4800]
 *                double orientationEuler_kal[4800]
 *                double angularVelocity_kal[4800]
 * Return Type  : void
 */
void kal_tool(double acc[4800], double gyro[4800], double mag[4800], double
              orientationEuler_kal[4800], double angularVelocity_kal[4800])
{
  static c_fusion_internal_coder_ahrsfil FUSE;
  static double r1[4800];
  int i0;
  double r2[4800];
  double r3[4800];
  static d_matlabshared_rotations_intern orientation_kal;
  double b_r3;
  ahrsfiltercg_ahrsfiltercg(&FUSE);
  rng();
  randn(r1);
  for (i0 = 0; i0 < 4800; i0++) {
    r1[i0] = 0.0 * r1[i0] + 0.001;
  }

  rng();
  randn(r2);
  for (i0 = 0; i0 < 4800; i0++) {
    r2[i0] = 0.0 * r2[i0] + 0.001;
  }

  rng();
  randn(r3);
  for (i0 = 0; i0 < 4800; i0++) {
    b_r3 = 0.0 * r3[i0] + 0.001;
    r3[i0] = b_r3;
    acc[i0] += r1[i0];
    gyro[i0] += r2[i0];
    mag[i0] += b_r3;
  }

  SystemCore_parenReference(&FUSE, acc, gyro, mag, &orientation_kal,
    angularVelocity_kal);
  quaternionBase_eulerd(&orientation_kal, orientationEuler_kal);
}

/*
 * File trailer for kal_tool.c
 *
 * [EOF]
 */
