/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * RealTimeFilter.h
 *
 * Code generation for function 'RealTimeFilter'
 *
 */

#ifndef REALTIMEFILTER_H
#define REALTIMEFILTER_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "RealTimeFilter_types.h"

/* Function Declarations */
extern void RealTimeFilter(double x_data[], int x_size[1], const double z[120],
  double result_z[120]);

#endif

/* End of code generation (RealTimeFilter.h) */
