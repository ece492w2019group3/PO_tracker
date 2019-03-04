/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * kal_tool_types.h
 *
 * Code generation for function 'kal_tool'
 *
 */

#ifndef KAL_TOOL_TYPES_H
#define KAL_TOOL_TYPES_H

/* Include files */
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

#ifndef typedef_c_fusion_internal_coder_imufilt
#define typedef_c_fusion_internal_coder_imufilt

typedef struct {
  int isInitialized;
  bool TunablePropsChanged;
  cell_wrap_3 inputVarSize[2];
  double AccelerometerNoise;
  double GyroscopeNoise;
  double GyroscopeDriftNoise;
  double LinearAccelerationNoise;
  double LinearAccelerationDecayFactor;
  double pQw[81];
  double pQv[9];
  c_matlabshared_rotations_intern pOrientPost;
  c_matlabshared_rotations_intern pOrientPrior;
  bool pFirstTime;
  double pSensorPeriod;
  double pKalmanPeriod;
  double pGyroOffset[3];
  double pLinAccelPrior[3];
  double pLinAccelPost[3];
  double pInputPrototype[4800];
} c_fusion_internal_coder_imufilt;

#endif                                 /*typedef_c_fusion_internal_coder_imufilt*/

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

/* End of code generation (kal_tool_types.h) */
