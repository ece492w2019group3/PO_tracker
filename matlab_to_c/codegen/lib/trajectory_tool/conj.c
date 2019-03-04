/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: conj.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 26-Feb-2019 13:17:28
 */

/* Include Files */
#include "trajectory_tool.h"
#include "conj.h"

/* Function Definitions */

/*
 * Arguments    : d_matlabshared_rotations_intern *q
 * Return Type  : void
 */
void quaternionBase_conj(d_matlabshared_rotations_intern *q)
{
  int i4;
  for (i4 = 0; i4 < 1600; i4++) {
    q->b[i4] = -q->b[i4];
    q->c[i4] = -q->c[i4];
    q->d[i4] = -q->d[i4];
  }
}

/*
 * File trailer for conj.c
 *
 * [EOF]
 */
