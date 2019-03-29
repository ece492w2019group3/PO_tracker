/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: kal_tool_types.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 01-Mar-2019 15:09:29
 */

#ifndef KAL_TOOL_TYPES_H
#define KAL_TOOL_TYPES_H

/* Include Files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_c_matlabshared_rotations_intern
#define typedef_c_matlabshared_rotations_intern

typedef struct {
  double a;
  double b;
  double c;
  double d;
} c_matlabshared_rotations_intern;

#endif                                 /*typedef_c_matlabshared_rotations_intern*/

#ifndef typedef_cell_wrap_3
#define typedef_cell_wrap_3

typedef struct {
  unsigned int f1[8];
} cell_wrap_3;

#endif                                 /*typedef_cell_wrap_3*/

#ifndef typedef_c_fusion_internal_coder_ahrsfil
#define typedef_c_fusion_internal_coder_ahrsfil

typedef struct {
  int isInitialized;
  boolean_T TunablePropsChanged;
  cell_wrap_3 inputVarSize[3];
  double AccelerometerNoise;
  double GyroscopeNoise;
  double GyroscopeDriftNoise;
  double LinearAccelerationNoise;
  double LinearAccelerationDecayFactor;
  double pQw[144];
  double pQv[36];
  c_matlabshared_rotations_intern pOrientPost;
  c_matlabshared_rotations_intern pOrientPrior;
  boolean_T pFirstTime;
  double pSensorPeriod;
  double pKalmanPeriod;
  double pGyroOffset[3];
  double pLinAccelPrior[3];
  double pLinAccelPost[3];
  double pInputPrototype[4800];
  double MagnetometerNoise;
  double MagneticDisturbanceNoise;
  double MagneticDisturbanceDecayFactor;
  double ExpectedMagneticFieldStrength;
  double pMagVec[3];
} c_fusion_internal_coder_ahrsfil;

#endif                                 /*typedef_c_fusion_internal_coder_ahrsfil*/

#ifndef typedef_d_matlabshared_rotations_intern
#define typedef_d_matlabshared_rotations_intern

typedef struct {
  double a[1600];
  double b[1600];
  double c[1600];
  double d[1600];
} d_matlabshared_rotations_intern;

#endif                                 /*typedef_d_matlabshared_rotations_intern*/
#endif

/*
 * File trailer for kal_tool_types.h
 *
 * [EOF]
 */
