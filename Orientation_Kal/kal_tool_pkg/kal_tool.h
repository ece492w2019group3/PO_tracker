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
extern void kal_tool(const double acc[3], const double gyro[3], const double
                     mag[3], double orientationEuler_kal[3], double
                     angularVelocity[3]);

#endif

/* End of code generation (kal_tool.h) */
