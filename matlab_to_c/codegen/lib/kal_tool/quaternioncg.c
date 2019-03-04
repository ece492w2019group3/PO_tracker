/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: quaternioncg.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 01-Mar-2019 15:09:29
 */

/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "quaternioncg.h"

/* Function Definitions */

/*
 * Arguments    : const double varargin_1[3]
 *                double *obj_a
 *                double *obj_b
 *                double *obj_c
 *                double *obj_d
 * Return Type  : void
 */
void b_quaternioncg_quaternioncg(const double varargin_1[3], double *obj_a,
  double *obj_b, double *obj_c, double *obj_d)
{
  double theta;
  double st;
  *obj_a = 1.0;
  *obj_b = 0.0;
  *obj_c = 0.0;
  *obj_d = 0.0;
  theta = sqrt((varargin_1[0] * varargin_1[0] + varargin_1[1] * varargin_1[1]) +
               varargin_1[2] * varargin_1[2]);
  st = sin(theta / 2.0);
  if (theta != 0.0) {
    *obj_a = cos(theta / 2.0);
    *obj_b = varargin_1[0] / theta * st;
    *obj_c = varargin_1[1] / theta * st;
    *obj_d = varargin_1[2] / theta * st;
  }
}

/*
 * Arguments    : d_matlabshared_rotations_intern *obj
 *                double rhs_a
 *                double rhs_b
 *                double rhs_c
 *                double rhs_d
 *                double varargin_1
 * Return Type  : void
 */
void quaternioncg_parenAssign(d_matlabshared_rotations_intern *obj, double rhs_a,
  double rhs_b, double rhs_c, double rhs_d, double varargin_1)
{
  int i9;
  i9 = (int)varargin_1 - 1;
  obj->a[i9] = rhs_a;
  obj->b[i9] = rhs_b;
  obj->c[i9] = rhs_c;
  obj->d[i9] = rhs_d;
}

/*
 * Arguments    : const double varargin_1[9]
 *                double *obj_a
 *                double *obj_b
 *                double *obj_c
 *                double *obj_d
 * Return Type  : void
 */
void quaternioncg_quaternioncg(const double varargin_1[9], double *obj_a, double
  *obj_b, double *obj_c, double *obj_d)
{
  double invpd;
  double psquared[4];
  int idx;
  int k;
  boolean_T exitg1;
  int i5;
  double d3;
  invpd = (varargin_1[0] + varargin_1[4]) + varargin_1[8];
  psquared[0] = (1.0 + 2.0 * ((varargin_1[0] + varargin_1[4]) + varargin_1[8]))
    - invpd;
  psquared[1] = (1.0 + 2.0 * varargin_1[0]) - invpd;
  psquared[2] = (1.0 + 2.0 * varargin_1[4]) - invpd;
  psquared[3] = (1.0 + 2.0 * varargin_1[8]) - invpd;
  if (!rtIsNaN(psquared[0])) {
    idx = 1;
  } else {
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 5)) {
      if (!rtIsNaN(psquared[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (idx == 0) {
    invpd = psquared[0];
    idx = 1;
  } else {
    invpd = psquared[idx - 1];
    i5 = idx + 1;
    for (k = i5; k < 5; k++) {
      d3 = psquared[k - 1];
      if (invpd < d3) {
        invpd = d3;
        idx = k;
      }
    }
  }

  switch (idx) {
   case 1:
    d3 = sqrt(invpd);
    *obj_a = 0.5 * d3;
    invpd = 0.5 / d3;
    *obj_b = invpd * (varargin_1[7] - varargin_1[5]);
    *obj_c = invpd * (varargin_1[2] - varargin_1[6]);
    *obj_d = invpd * (varargin_1[3] - varargin_1[1]);
    break;

   case 2:
    d3 = sqrt(invpd);
    *obj_b = 0.5 * d3;
    invpd = 0.5 / d3;
    *obj_a = invpd * (varargin_1[7] - varargin_1[5]);
    *obj_c = invpd * (varargin_1[3] + varargin_1[1]);
    *obj_d = invpd * (varargin_1[2] + varargin_1[6]);
    break;

   case 3:
    d3 = sqrt(invpd);
    *obj_c = 0.5 * d3;
    invpd = 0.5 / d3;
    *obj_a = invpd * (varargin_1[2] - varargin_1[6]);
    *obj_b = invpd * (varargin_1[3] + varargin_1[1]);
    *obj_d = invpd * (varargin_1[7] + varargin_1[5]);
    break;

   default:
    invpd = sqrt(invpd);
    *obj_d = 0.5 * invpd;
    invpd = 0.5 / invpd;
    *obj_a = invpd * (varargin_1[3] - varargin_1[1]);
    *obj_b = invpd * (varargin_1[2] + varargin_1[6]);
    *obj_c = invpd * (varargin_1[7] + varargin_1[5]);
    break;
  }

  if (*obj_a < 0.0) {
    *obj_a = -*obj_a;
    *obj_b = -*obj_b;
    *obj_c = -*obj_c;
    *obj_d = -*obj_d;
  }
}

/*
 * File trailer for quaternioncg.c
 *
 * [EOF]
 */
