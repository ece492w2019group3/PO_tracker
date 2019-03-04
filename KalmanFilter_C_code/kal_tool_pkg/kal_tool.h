/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * kal_tool.h
 *
 * Code generation for function 'kal_tool'
 *
 */

#ifndef KAL_TOOL_H
#define KAL_TOOL_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "kal_tool_types.h"

/* Function Declarations */
extern void kal_tool(const double acc[4800], const double gyro[4800], const
                     double mag[4800], double orientationEuler_kal[4800]);

#endif

/* End of code generation (kal_tool.h) */
