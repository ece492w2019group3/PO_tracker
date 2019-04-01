/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: trajectory_tool.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 30-Mar-2019 15:04:56
 */

#ifndef TRAJECTORY_TOOL_H
#define TRAJECTORY_TOOL_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "trajectory_tool_types.h"

/* Function Declarations */
extern void trajectory_tool(const double accelerometerReadings[6], const double
  angularvelocity[6], const double prev_position[3], const
  c_matlabshared_rotations_intern prev_orientation, const double prev_velocity[3],
  double fs, double cur_position[3], d_matlabshared_rotations_intern
  *orientation, double velocity[6], double acceleration[6], double
  angularVelocity[6]);

#endif

/*
 * File trailer for trajectory_tool.h
 *
 * [EOF]
 */
