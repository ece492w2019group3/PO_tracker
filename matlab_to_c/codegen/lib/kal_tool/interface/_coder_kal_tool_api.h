/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_kal_tool_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 01-Mar-2019 15:09:29
 */

#ifndef _CODER_KAL_TOOL_API_H
#define _CODER_KAL_TOOL_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_kal_tool_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void kal_tool(real_T acc[4800], real_T gyro[4800], real_T mag[4800],
                     real_T orientationEuler_kal[4800], real_T
                     angularVelocity_kal[4800]);
extern void kal_tool_api(const mxArray * const prhs[3], int32_T nlhs, const
  mxArray *plhs[2]);
extern void kal_tool_atexit(void);
extern void kal_tool_initialize(void);
extern void kal_tool_terminate(void);
extern void kal_tool_xil_terminate(void);

#endif

/*
 * File trailer for _coder_kal_tool_api.h
 *
 * [EOF]
 */
