/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * imufiltercg.c
 *
 * Code generation for function 'imufiltercg'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "imufiltercg.h"

/* Function Definitions */
c_fusion_internal_coder_imufilt *imufiltercg_imufiltercg
  (c_fusion_internal_coder_imufilt *obj)
{
  c_fusion_internal_coder_imufilt *b_obj;
  b_obj = obj;
  b_obj->AccelerometerNoise = 0.0001924722;
  b_obj->GyroscopeNoise = 9.1385E-5;
  b_obj->GyroscopeDriftNoise = 3.0462E-13;
  b_obj->LinearAccelerationNoise = 0.0096236100000000012;
  b_obj->LinearAccelerationDecayFactor = 0.5;
  b_obj->isInitialized = 0;
  return b_obj;
}

/* End of code generation (imufiltercg.c) */
