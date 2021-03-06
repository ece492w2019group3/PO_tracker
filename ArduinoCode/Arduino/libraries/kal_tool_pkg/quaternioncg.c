/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * quaternioncg.c
 *
 * Code generation for function 'quaternioncg'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "quaternioncg.h"

/* Function Definitions */
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

void quaternioncg_parenAssign(double rhs_a, double rhs_b, double rhs_c, double
  rhs_d, double *o_a, double *o_b, double *o_c, double *o_d)
{
  *o_a = rhs_a;
  *o_b = rhs_b;
  *o_c = rhs_c;
  *o_d = rhs_d;
}

void quaternioncg_quaternioncg(const double varargin_1[9], double *obj_a, double
  *obj_b, double *obj_c, double *obj_d)
{
  double invpd;
  double psquared[4];
  int idx;
  int k;
  bool exitg1;
  int i4;
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
    i4 = idx + 1;
    for (k = i4; k < 5; k++) {
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

/* End of code generation (quaternioncg.c) */
