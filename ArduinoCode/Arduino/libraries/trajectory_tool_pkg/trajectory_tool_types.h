/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: trajectory_tool_types.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 30-Mar-2019 15:04:56
 */

#ifndef TRAJECTORY_TOOL_TYPES_H
#define TRAJECTORY_TOOL_TYPES_H

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

#ifndef typedef_d_matlabshared_rotations_intern
#define typedef_d_matlabshared_rotations_intern

typedef struct {
  double a[2];
  double b[2];
  double c[2];
  double d[2];
} d_matlabshared_rotations_intern;

#endif                                 /*typedef_d_matlabshared_rotations_intern*/

#ifndef typedef_kinematicTrajectory
#define typedef_kinematicTrajectory

typedef struct {
  int isInitialized;
  cell_wrap_3 inputVarSize[2];
  double SampleRate;
  double Position[3];
  double Velocity[3];
  double Acceleration[3];
  double AngularVelocity[3];
  c_matlabshared_rotations_intern pOrientation;
} kinematicTrajectory;

#endif                                 /*typedef_kinematicTrajectory*/
#endif

/*
 * File trailer for trajectory_tool_types.h
 *
 * [EOF]
 */
