/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: kinematicTrajectory.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 26-Feb-2019 13:17:28
 */

#ifndef KINEMATICTRAJECTORY_H
#define KINEMATICTRAJECTORY_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "trajectory_tool_types.h"

/* Function Declarations */
extern kinematicTrajectory *c_kinematicTrajectory_kinematic(kinematicTrajectory *
  obj);
extern void kinematicTrajectory_stepImpl(kinematicTrajectory *obj, const double
  varargin_1[4800], const double varargin_2[4800], double pos[4800], double vel
  [4800], double acc[4800], double av[4800]);

#endif

/*
 * File trailer for kinematicTrajectory.h
 *
 * [EOF]
 */
