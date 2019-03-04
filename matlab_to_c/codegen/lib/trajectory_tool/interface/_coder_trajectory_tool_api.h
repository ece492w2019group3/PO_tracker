/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_trajectory_tool_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 26-Feb-2019 13:17:28
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
extern void trajectory_tool(real_T accelerometerReadings[4800], real_T
  angularvelocity[4800], real_T position[4800]);
extern void trajectory_tool_api(const mxArray * const prhs[2], int32_T nlhs,
  const mxArray *plhs[1]);
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
