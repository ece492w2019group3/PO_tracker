/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * uminus.c
 *
 * Code generation for function 'uminus'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "uminus.h"

/* Function Definitions */
void quaternionBase_uminus(c_matlabshared_rotations_intern *obj)
{
  obj->a = -obj->a;
  obj->b = -obj->b;
  obj->c = -obj->c;
  obj->d = -obj->d;
}

/* End of code generation (uminus.c) */
