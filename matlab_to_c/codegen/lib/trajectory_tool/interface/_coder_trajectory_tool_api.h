/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_trajectory_tool_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 27-Mar-2019 12:24:35
 */

#ifndef _CODER_TRAJECTORY_TOOL_API_H
#define _CODER_TRAJECTORY_TOOL_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_trajectory_tool_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void trajectory_tool(real_T accelerometerReadings[6], real_T
  angularvelocity[6], real_T prev_position[3], real_T prev_velocity[3], real_T
  cur_position[3], real_T velocity[6], real_T acceleration[6], real_T
  angularVelocity[6]);
extern void trajectory_tool_api(const mxArray * const prhs[4], int32_T nlhs,
  const mxArray *plhs[4]);
extern void trajectory_tool_atexit(void);
extern void trajectory_tool_initialize(void);
extern void trajectory_tool_terminate(void);
extern void trajectory_tool_xil_terminate(void);

#endif

/*
 * File trailer for _coder_trajectory_tool_api.h
 *
 * [EOF]
 */
