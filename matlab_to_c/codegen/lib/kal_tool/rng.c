/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: rng.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 01-Mar-2019 15:09:29
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "rng.h"
#include "kal_tool_data.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void rng(void)
{
  unsigned int r;
  int mti;
  state[0] = 5489U;
  state[624] = 624U;
  r = 5489U;
  state[0] = 5489U;
  for (mti = 0; mti < 623; mti++) {
    r = ((r ^ r >> 30U) * 1812433253U + mti) + 1U;
    state[mti + 1] = r;
  }

  state[624] = 624U;
}

/*
 * File trailer for rng.c
 *
 * [EOF]
 */
