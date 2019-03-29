/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: uminus.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 01-Mar-2019 15:09:29
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "uminus.h"

/* Function Definitions */

/*
 * Arguments    : c_matlabshared_rotations_intern *obj
 * Return Type  : void
 */
void quaternionBase_uminus(c_matlabshared_rotations_intern *obj)
{
  obj->a = -obj->a;
  obj->b = -obj->b;
  obj->c = -obj->c;
  obj->d = -obj->d;
}

/*
 * File trailer for uminus.c
 *
 * [EOF]
 */
