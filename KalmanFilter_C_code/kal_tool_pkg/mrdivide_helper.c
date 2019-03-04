/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mrdivide_helper.c
 *
 * Code generation for function 'mrdivide_helper'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "mrdivide_helper.h"

/* Function Definitions */
void mrdivide_helper(const double A[27], const double B[9], double y[27])
{
  double b_A[9];
  int r1;
  int r2;
  int r3;
  double maxval;
  double a21;
  int rtemp;
  int y_tmp;
  int b_y_tmp;
  int c_y_tmp;
  memcpy(&b_A[0], &B[0], 9U * sizeof(double));
  r1 = 0;
  r2 = 1;
  r3 = 2;
  maxval = fabs(B[0]);
  a21 = fabs(B[1]);
  if (a21 > maxval) {
    maxval = a21;
    r1 = 1;
    r2 = 0;
  }

  if (fabs(B[2]) > maxval) {
    r1 = 2;
    r2 = 1;
    r3 = 0;
  }

  b_A[r2] = B[r2] / B[r1];
  b_A[r3] /= b_A[r1];
  b_A[3 + r2] -= b_A[r2] * b_A[3 + r1];
  b_A[3 + r3] -= b_A[r3] * b_A[3 + r1];
  b_A[6 + r2] -= b_A[r2] * b_A[6 + r1];
  b_A[6 + r3] -= b_A[r3] * b_A[6 + r1];
  if (fabs(b_A[3 + r3]) > fabs(b_A[3 + r2])) {
    rtemp = r2;
    r2 = r3;
    r3 = rtemp;
  }

  b_A[3 + r3] /= b_A[3 + r2];
  b_A[6 + r3] -= b_A[3 + r3] * b_A[6 + r2];
  for (rtemp = 0; rtemp < 9; rtemp++) {
    y_tmp = rtemp + 9 * r1;
    y[y_tmp] = A[rtemp] / b_A[r1];
    b_y_tmp = rtemp + 9 * r2;
    y[b_y_tmp] = A[9 + rtemp] - y[y_tmp] * b_A[3 + r1];
    c_y_tmp = rtemp + 9 * r3;
    y[c_y_tmp] = A[18 + rtemp] - y[y_tmp] * b_A[6 + r1];
    y[b_y_tmp] /= b_A[3 + r2];
    y[c_y_tmp] -= y[b_y_tmp] * b_A[6 + r2];
    y[c_y_tmp] /= b_A[6 + r3];
    y[b_y_tmp] -= y[c_y_tmp] * b_A[3 + r3];
    y[y_tmp] -= y[c_y_tmp] * b_A[r3];
    y[y_tmp] -= y[b_y_tmp] * b_A[r2];
  }
}

/* End of code generation (mrdivide_helper.c) */
