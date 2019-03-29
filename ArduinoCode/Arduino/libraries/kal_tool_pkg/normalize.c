/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * normalize.c
 *
 * Code generation for function 'normalize'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "normalize.h"

/* Function Definitions */
void quaternionBase_normalize(c_matlabshared_rotations_intern *q)
{
  double n;
  n = sqrt(((q->a * q->a + q->b * q->b) + q->c * q->c) + q->d * q->d);
  q->a /= n;
  q->b /= n;
  q->c /= n;
  q->d /= n;
}

/* End of code generation (normalize.c) */
