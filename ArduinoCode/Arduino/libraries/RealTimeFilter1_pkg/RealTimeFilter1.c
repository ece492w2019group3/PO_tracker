/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * RealTimeFilter1.c
 *
 * Code generation for function 'RealTimeFilter1'
 *
 */

/* Include files */
#include <string.h>
#include "RealTimeFilter1.h"

/* Function Definitions */
void RealTimeFilter1(double x_data[], int x_size[1], const double z[40], double
                     result_z[40])
{
  signed char x_idx_0;
  int nx;
  double b_x_data[2];
  int niccp;
  int naxpy;
  int k;
  int j;
  static const double dv1[41] = { -1.5611107813163698E-18,
    -0.0014368267365517933, 2.0004464318155717E-18, 0.0024395782106173126,
    -3.2754481488108475E-18, -0.0045621139241154279, 5.2613098807833768E-18,
    0.008118263300045463, -7.76364164509541E-18, -0.013559800534203454,
    1.0537497773885494E-17, 0.021669221197992979, -1.3311353902675576E-17,
    -0.034091910536797672, 1.5813685666987609E-17, 0.055149817559288661,
    -1.7799547398960137E-17, -0.10090265569256014, 1.9074549115955417E-17,
    0.31688108866369069, 0.50059067698518711, 0.31688108866369069,
    1.9074549115955417E-17, -0.10090265569256014, -1.7799547398960137E-17,
    0.055149817559288661, 1.5813685666987609E-17, -0.034091910536797672,
    -1.3311353902675576E-17, 0.021669221197992979, 1.0537497773885494E-17,
    -0.013559800534203454, -7.76364164509541E-18, 0.008118263300045463,
    5.2613098807833768E-18, -0.0045621139241154279, -3.2754481488108475E-18,
    0.0024395782106173126, 2.0004464318155717E-18, -0.0014368267365517933,
    -1.5611107813163698E-18 };

  int boffset_tmp;
  x_idx_0 = (signed char)x_size[0];
  nx = x_size[0];
  memset(&result_z[0], 0, 40U * sizeof(double));
  if (0 <= nx - 1) {
    memcpy(&b_x_data[0], &z[0], (unsigned int)(nx * (int)sizeof(double)));
  }

  niccp = x_size[0] + 1;
  if (niccp <= nx) {
    memset(&b_x_data[niccp + -1], 0, (unsigned int)(((nx - niccp) + 1) * (int)
            sizeof(double)));
  }

  naxpy = x_size[0];
  for (k = 1; k <= nx; k++) {
    for (j = 0; j < naxpy; j++) {
      niccp = (k + j) - 1;
      b_x_data[niccp] += x_data[k - 1] * dv1[j];
    }

    naxpy--;
  }

  niccp = 39 - x_size[0];
  for (k = 0; k <= niccp; k++) {
    result_z[k] = z[k + nx];
  }

  niccp = x_size[0] - 1;
  for (k = 0; k <= niccp; k++) {
    boffset_tmp = nx - k;
    naxpy = 40 - boffset_tmp;
    for (j = 0; j <= naxpy; j++) {
      result_z[j] += x_data[k] * dv1[boffset_tmp + j];
    }
  }

  x_size[0] = x_idx_0;
  if (0 <= x_idx_0 - 1) {
    memcpy(&x_data[0], &b_x_data[0], (unsigned int)(x_idx_0 * (int)sizeof(double)));
  }
}

/* End of code generation (RealTimeFilter1.c) */
