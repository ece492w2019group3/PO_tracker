/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: trajectory_tool.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 26-Feb-2019 13:17:28
 */

/* Include Files */
#include "trajectory_tool.h"
#include "kinematicTrajectory.h"

/* Function Definitions */

/*
 * TRAJECTORY_TOOL Summary of this function goes here
 *    Detailed explanation goes here
 * Arguments    : const double accelerometerReadings[4800]
 *                const double angularvelocity[4800]
 *                double position[4800]
 * Return Type  : void
 */
void trajectory_tool(const double accelerometerReadings[4800], const double
                     angularvelocity[4800], double position[4800])
{
  kinematicTrajectory trajectory;
  static double varargout_3[4800];
  static double varargout_4[4800];
  static double varargout_5[4800];
  c_kinematicTrajectory_kinematic(&trajectory);
  if (trajectory.isInitialized != 1) {
    trajectory.isInitialized = 1;
  }

  kinematicTrajectory_stepImpl(&trajectory, accelerometerReadings,
    angularvelocity, position, varargout_3, varargout_4, varargout_5);
}

/*
 * File trailer for trajectory_tool.c
 *
 * [EOF]
 */
