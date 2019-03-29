/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: trajectory_tool.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 27-Mar-2019 12:24:35
 */

/* Include Files */
#include "trajectory_tool.h"
#include "kinematicTrajectory.h"

/* Function Definitions */

/*
 * TRAJECTORY_TOOL Summary of this function goes here
 *    Detailed explanation goes here
 * Arguments    : const double accelerometerReadings[6]
 *                const double angularvelocity[6]
 *                const double prev_position[3]
 *                const double prev_velocity[3]
 *                double cur_position[3]
 *                double velocity[6]
 *                double acceleration[6]
 *                double angularVelocity[6]
 * Return Type  : void
 */
void trajectory_tool(const double accelerometerReadings[6], const double
                     angularvelocity[6], const double prev_position[3], const
                     double prev_velocity[3], double cur_position[3], double
                     velocity[6], double acceleration[6], double
                     angularVelocity[6])
{
  kinematicTrajectory trajectory;
  double varargout_1[6];
  trajectory.SampleRate = 10000.0;
  trajectory.Acceleration[0] = 0.0;
  trajectory.AngularVelocity[0] = 0.0;
  trajectory.Acceleration[1] = 0.0;
  trajectory.AngularVelocity[1] = 0.0;
  trajectory.Acceleration[2] = 0.0;
  trajectory.AngularVelocity[2] = 0.0;
  trajectory.isInitialized = 0;
  c_kinematicTrajectory_set_Posit(&trajectory, prev_position);
  c_kinematicTrajectory_set_Veloc(&trajectory, prev_velocity);
  trajectory.pOrientation.a = 1.0;
  trajectory.pOrientation.b = 0.0;
  trajectory.pOrientation.c = 0.0;
  trajectory.pOrientation.d = 0.0;
  if (trajectory.isInitialized != 1) {
    trajectory.isInitialized = 1;
  }

  kinematicTrajectory_stepImpl(&trajectory, accelerometerReadings,
    angularvelocity, varargout_1, velocity, acceleration, angularVelocity);
  cur_position[0] = varargout_1[1];
  cur_position[1] = varargout_1[3];
  cur_position[2] = varargout_1[5];
}

/*
 * File trailer for trajectory_tool.c
 *
 * [EOF]
 */
