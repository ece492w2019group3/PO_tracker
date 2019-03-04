/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * kal_tool.c
 *
 * Code generation for function 'kal_tool'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "eulerd.h"
#include "SystemCore.h"
#include "imufiltercg.h"

/* Function Definitions */
void kal_tool(const double acc[4800], const double gyro[4800], const double mag
              [4800], double orientationEuler_kal[4800])
{
  c_fusion_internal_coder_imufilt FUSE;
  double orientation_kal_a[1600];
  double orientation_kal_b[1600];
  double orientation_kal_c[1600];
  double orientation_kal_d[1600];
  (void)mag;

  /*  FUSE = ahrsfilter('AccelerometerNoise', 0.001, 'GyroscopeNoise', 0.001, 'MagnetometerNoise', 0.001); */
  imufiltercg_imufiltercg(&FUSE);

  /*  mu = [0 0 0]; */
  /*  sigma = [0.001 0 0; 0 0.001 0; 0 0 0.001]; */
  /*  R = chol(sigma); */
  /*  r1 = repmat(mu,1,1) + randn(1,3)*R;  */
  /*  r2 = repmat(mu,1,1) + randn(1,3)*R; */
  /*  r3 = repmat(mu,1,1) + randn(1,3)*R; */
  /*  acc = acc + r1; */
  /*  gyro = gyro + r2; */
  /*  mag = mag + r3; */
  /*  t = acc1 +1 */
  SystemCore_parenReference(&FUSE, acc, gyro, orientation_kal_a,
    orientation_kal_b, orientation_kal_c, orientation_kal_d);
  quaternionBase_eulerd(orientation_kal_a, orientation_kal_b, orientation_kal_c,
                        orientation_kal_d, orientationEuler_kal);
}

/* End of code generation (kal_tool.c) */
