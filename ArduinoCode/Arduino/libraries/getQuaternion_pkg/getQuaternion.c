/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: getQuaternion.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 30-Mar-2019 15:11:51
 */

/* Include Files */
#include <math.h>
#include "getQuaternion.h"

/* Function Definitions */

/*
 * Arguments    : double Yaw
 *                double Pitch
 *                double Roll
 *                c_matlabshared_rotations_intern *Quaternion
 * Return Type  : void
 */
void getQuaternion(double Yaw, double Pitch, double Roll,
                   c_matlabshared_rotations_intern *Quaternion)
{
  double arg1_idx_0;
  double arg1_idx_1;
  double arg1_idx_2;
  double Quaternion_tmp_tmp;
  double b_Quaternion_tmp_tmp;
  double Quaternion_tmp;
  double b_Quaternion_tmp;
  double c_Quaternion_tmp;
  arg1_idx_0 = 0.017453292519943295 * Yaw / 2.0;
  arg1_idx_1 = 0.017453292519943295 * Pitch / 2.0;
  arg1_idx_2 = 0.017453292519943295 * Roll / 2.0;
  Quaternion_tmp_tmp = cos(arg1_idx_0);
  b_Quaternion_tmp_tmp = cos(arg1_idx_1);
  Quaternion_tmp = Quaternion_tmp_tmp * b_Quaternion_tmp_tmp;
  b_Quaternion_tmp = sin(arg1_idx_2);
  c_Quaternion_tmp = cos(arg1_idx_2);
  arg1_idx_0 = sin(arg1_idx_0);
  arg1_idx_2 = sin(arg1_idx_1);
  Quaternion->a = Quaternion_tmp * c_Quaternion_tmp + arg1_idx_0 * arg1_idx_2 *
    b_Quaternion_tmp;
  Quaternion->b = Quaternion_tmp * b_Quaternion_tmp - c_Quaternion_tmp *
    arg1_idx_0 * arg1_idx_2;
  Quaternion->c = Quaternion_tmp_tmp * c_Quaternion_tmp * arg1_idx_2 +
    b_Quaternion_tmp_tmp * arg1_idx_0 * b_Quaternion_tmp;
  Quaternion->d = b_Quaternion_tmp_tmp * c_Quaternion_tmp * arg1_idx_0 -
    Quaternion_tmp_tmp * arg1_idx_2 * b_Quaternion_tmp;
}

/*
 * File trailer for getQuaternion.c
 *
 * [EOF]
 */
