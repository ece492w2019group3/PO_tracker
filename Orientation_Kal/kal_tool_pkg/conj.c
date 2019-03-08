/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * conj.c
 *
 * Code generation for function 'conj'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "conj.h"

/* Function Definitions */
void quaternionBase_conj(c_matlabshared_rotations_intern *q)
{
  q->b = -q->b;
  q->c = -q->c;
  q->d = -q->d;
}

/* End of code generation (conj.c) */
