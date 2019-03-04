/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: conj.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 01-Mar-2019 15:09:29
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "conj.h"

/* Function Definitions */

/*
 * Arguments    : c_matlabshared_rotations_intern *q
 * Return Type  : void
 */
void quaternionBase_conj(c_matlabshared_rotations_intern *q)
{
  q->b = -q->b;
  q->c = -q->c;
  q->d = -q->d;
}

/*
 * File trailer for conj.c
 *
 * [EOF]
 */
