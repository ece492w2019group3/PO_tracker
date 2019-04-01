/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: trajectory_tool.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 30-Mar-2019 15:04:56
 */

/* Include Files */
#include "trajectory_tool.h"
#include "kinematicTrajectory.h"

/* Function Definitions */

/*
 * TRAJECTORY_TOOL Summary of this function goes here
 *    Detailed explanation goes here
 *  trajectory = kinematicTrajectory('SampleRate',10, 'Position', prev_position, 'Orientation', prev_orientation, 'Velocity', prev_velocity);
 * Arguments    : const double accelerometerReadings[6]
 *                const double angularvelocity[6]
 *                const double prev_position[3]
 *                const c_matlabshared_rotations_intern prev_orientation
 *                const double prev_velocity[3]
 *                double fs
 *                double cur_position[3]
 *                d_matlabshared_rotations_intern *orientation
 *                double velocity[6]
 *                double acceleration[6]
 *                double angularVelocity[6]
 * Return Type  : void
 */
void trajectory_tool(const double accelerometerReadings[6], const double
                     angularvelocity[6], const double prev_position[3], const
                     c_matlabshared_rotations_intern prev_orientation, const
                     double prev_velocity[3], double fs, double cur_position[3],
                     d_matlabshared_rotations_intern *orientation, double
                     velocity[6], double acceleration[6], double
                     angularVelocity[6])
{
  kinematicTrajectory trajectory;
  double varargout_1[6];

  /*  accelerometerReadings(1,:) = rotateframe(pitchRotation,accelerometerReadings(1,:)); */
  /*  accelerometerReadings(2,:) = rotateframe(pitchRotation,accelerometerReadings(2,:)); */
  /*  angularvelocity(1,:) = rotateframe(pitchRotation,angularvelocity(1,:)); */
  /*  angularvelocity(2,:) = rotateframe(pitchRotation,angularvelocity(2,:)); */
  trajectory.Acceleration[0] = 0.0;
  trajectory.AngularVelocity[0] = 0.0;
  trajectory.Acceleration[1] = 0.0;
  trajectory.AngularVelocity[1] = 0.0;
  trajectory.Acceleration[2] = 0.0;
  trajectory.AngularVelocity[2] = 0.0;
  trajectory.isInitialized = 0;
  trajectory.SampleRate = fs;
  c_kinematicTrajectory_set_Posit(&trajectory, prev_position);
  trajectory.pOrientation = prev_orientation;
  c_kinematicTrajectory_set_Veloc(&trajectory, prev_velocity);
  if (trajectory.isInitialized != 1) {
    trajectory.isInitialized = 1;
  }

  kinematicTrajectory_stepImpl(&trajectory, accelerometerReadings,
    angularvelocity, varargout_1, orientation->a, orientation->b, orientation->c,
    orientation->d, velocity, acceleration, angularVelocity);
  cur_position[0] = varargout_1[1];
  cur_position[1] = varargout_1[3];
  cur_position[2] = varargout_1[5];
}

/*
 * File trailer for trajectory_tool.c
 *
 * [EOF]
 */
