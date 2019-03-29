/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mrdivide_helper.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 01-Mar-2019 15:09:29
 */

/* Include Files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "mrdivide_helper.h"

/* Function Definitions */

/*
 * Arguments    : double A[72]
 *                const double B[36]
 * Return Type  : void
 */
void mrdivide_helper(double A[72], const double B[36])
{
  double b_A[36];
  int i7;
  int j;
  signed char ipiv[6];
  int jA;
  int jj;
  int jp1j;
  int iy;
  int n;
  int k;
  int kBcol;
  int ix;
  double smax;
  double s;
  int i8;
  memcpy(&b_A[0], &B[0], 36U * sizeof(double));
  for (i7 = 0; i7 < 6; i7++) {
    ipiv[i7] = (signed char)(1 + i7);
  }

  for (j = 0; j < 5; j++) {
    jA = j * 7;
    jj = j * 7;
    jp1j = jA + 2;
    n = 6 - j;
    kBcol = 0;
    ix = jA;
    smax = fabs(b_A[jA]);
    for (k = 2; k <= n; k++) {
      ix++;
      s = fabs(b_A[ix]);
      if (s > smax) {
        kBcol = k - 1;
        smax = s;
      }
    }

    if (b_A[jj + kBcol] != 0.0) {
      if (kBcol != 0) {
        iy = j + kBcol;
        ipiv[j] = (signed char)(iy + 1);
        ix = j;
        for (k = 0; k < 6; k++) {
          smax = b_A[ix];
          b_A[ix] = b_A[iy];
          b_A[iy] = smax;
          ix += 6;
          iy += 6;
        }
      }

      i7 = jj - j;
      for (n = jp1j; n <= i7 + 6; n++) {
        b_A[n - 1] /= b_A[jj];
      }
    }

    n = 4 - j;
    iy = jA + 6;
    jA = jj + 7;
    for (kBcol = 0; kBcol <= n; kBcol++) {
      smax = b_A[iy];
      if (b_A[iy] != 0.0) {
        ix = jj + 1;
        i7 = jA + 1;
        i8 = (jA - j) + 5;
        for (jp1j = i7; jp1j <= i8; jp1j++) {
          b_A[jp1j - 1] += b_A[ix] * -smax;
          ix++;
        }
      }

      iy += 6;
      jA += 6;
    }
  }

  for (j = 0; j < 6; j++) {
    jA = 12 * j - 1;
    iy = 6 * j;
    for (k = 0; k < j; k++) {
      kBcol = 12 * k;
      smax = b_A[k + iy];
      if (smax != 0.0) {
        for (n = 0; n < 12; n++) {
          i7 = (n + jA) + 1;
          A[i7] -= smax * A[n + kBcol];
        }
      }
    }

    smax = 1.0 / b_A[j + iy];
    for (n = 0; n < 12; n++) {
      i7 = (n + jA) + 1;
      A[i7] *= smax;
    }
  }

  for (j = 5; j >= 0; j--) {
    jA = 12 * j - 1;
    iy = 6 * j - 1;
    i7 = j + 2;
    for (k = i7; k < 7; k++) {
      kBcol = 12 * (k - 1);
      smax = b_A[k + iy];
      if (smax != 0.0) {
        for (n = 0; n < 12; n++) {
          i8 = (n + jA) + 1;
          A[i8] -= smax * A[n + kBcol];
        }
      }
    }
  }

  for (iy = 4; iy >= 0; iy--) {
    if (ipiv[iy] != iy + 1) {
      for (kBcol = 0; kBcol < 12; kBcol++) {
        jA = kBcol + 12 * iy;
        smax = A[jA];
        i7 = kBcol + 12 * (ipiv[iy] - 1);
        A[jA] = A[i7];
        A[i7] = smax;
      }
    }
  }
}

/*
 * File trailer for mrdivide_helper.c
 *
 * [EOF]
 */
