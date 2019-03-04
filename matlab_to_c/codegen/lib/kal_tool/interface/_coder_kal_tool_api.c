/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_kal_tool_api.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 01-Mar-2019 15:09:29
 */

/* Include Files */
#include "tmwtypes.h"
#include "_coder_kal_tool_api.h"
#include "_coder_kal_tool_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131467U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "kal_tool",                          /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[4800];
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[4800];
static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *acc, const
  char_T *identifier))[4800];
static const mxArray *emlrt_marshallOut(const real_T u[4800]);

/* Function Definitions */

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[4800]
 */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[4800]
{
  real_T (*y)[4800];
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[4800]
 */
  static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[4800]
{
  real_T (*ret)[4800];
  static const int32_T dims[2] = { 1600, 3 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims);
  ret = (real_T (*)[4800])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *acc
 *                const char_T *identifier
 * Return Type  : real_T (*)[4800]
 */
static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *acc, const
  char_T *identifier))[4800]
{
  real_T (*y)[4800];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(acc), &thisId);
  emlrtDestroyArray(&acc);
  return y;
}
/*
 * Arguments    : const real_T u[4800]
 * Return Type  : const mxArray *
 */
  static const mxArray *emlrt_marshallOut(const real_T u[4800])
{
  const mxArray *y;
  const mxArray *m0;
  static const int32_T iv0[2] = { 0, 0 };

  static const int32_T iv1[2] = { 1600, 3 };

  y = NULL;
  m0 = emlrtCreateNumericArray(2, iv0, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m0, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m0, iv1, 2);
  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : const mxArray * const prhs[3]
 *                int32_T nlhs
 *                const mxArray *plhs[2]
 * Return Type  : void
 */
void kal_tool_api(const mxArray * const prhs[3], int32_T nlhs, const mxArray
                  *plhs[2])
{
  real_T (*orientationEuler_kal)[4800];
  real_T (*angularVelocity_kal)[4800];
  const mxArray *prhs_copy_idx_0;
  const mxArray *prhs_copy_idx_1;
  const mxArray *prhs_copy_idx_2;
  real_T (*acc)[4800];
  real_T (*gyro)[4800];
  real_T (*mag)[4800];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  orientationEuler_kal = (real_T (*)[4800])mxMalloc(sizeof(real_T [4800]));
  angularVelocity_kal = (real_T (*)[4800])mxMalloc(sizeof(real_T [4800]));
  prhs_copy_idx_0 = emlrtProtectR2012b(prhs[0], 0, false, -1);
  prhs_copy_idx_1 = emlrtProtectR2012b(prhs[1], 1, false, -1);
  prhs_copy_idx_2 = emlrtProtectR2012b(prhs[2], 2, false, -1);

  /* Marshall function inputs */
  acc = emlrt_marshallIn(&st, emlrtAlias(prhs_copy_idx_0), "acc");
  gyro = emlrt_marshallIn(&st, emlrtAlias(prhs_copy_idx_1), "gyro");
  mag = emlrt_marshallIn(&st, emlrtAlias(prhs_copy_idx_2), "mag");

  /* Invoke the target function */
  kal_tool(*acc, *gyro, *mag, *orientationEuler_kal, *angularVelocity_kal);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(*orientationEuler_kal);
  if (nlhs > 1) {
    plhs[1] = emlrt_marshallOut(*angularVelocity_kal);
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void kal_tool_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  kal_tool_xil_terminate();
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void kal_tool_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void kal_tool_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_kal_tool_api.c
 *
 * [EOF]
 */
