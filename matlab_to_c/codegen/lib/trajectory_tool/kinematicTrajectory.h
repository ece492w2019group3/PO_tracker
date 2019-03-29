/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: kinematicTrajectory.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 27-Mar-2019 12:24:35
 */

#ifndef KINEMATICTRAJECTORY_H
#define KINEMATICTRAJECTORY_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "trajectory_tool_types.h"

/* Function Declarations */
extern void c_kinematicTrajectory_set_Posit(kinematicTrajectory *obj, const
  double val[3]);
extern void c_kinematicTrajectory_set_Veloc(kinematicTrajectory *obj, const
  double val[3]);
extern void kinematicTrajectory_stepImpl(kinematicTrajectory *obj, const double
  varargin_1[6], const double varargin_2[6], double pos[6], double vel[6],
  double acc[6], double av[6]);

#endif

/*
 * File trailer for kinematicTrajectory.h
 *
 * [EOF]
 */
