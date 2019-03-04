/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * power1.c
 *
 * Code generation for function 'power1'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "power1.h"

/* Function Definitions */
void power(const double a[1600], double y[1600])
{
  int k;
  for (k = 0; k < 1600; k++) {
    y[k] = a[k] * a[k];
  }
}

/* End of code generation (power1.c) */
