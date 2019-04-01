/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: kinematicTrajectory.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 30-Mar-2019 15:04:56
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
  varargin_1[6], const double varargin_2[6], double pos[6], double orient_a[2],
  double orient_b[2], double orient_c[2], double orient_d[2], double vel[6],
  double acc[6], double av[6]);

#endif

/*
 * File trailer for kinematicTrajectory.h
 *
 * [EOF]
 */
