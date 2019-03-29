/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: kinematicTrajectory.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 27-Mar-2019 12:24:35
 */

/* Include Files */
#include <math.h>
#include "trajectory_tool.h"
#include "kinematicTrajectory.h"
#include "rotatepoint.h"
#include "vertcat.h"
#include "quaternioncg.h"

/* Function Definitions */

/*
 * Arguments    : kinematicTrajectory *obj
 *                const double val[3]
 * Return Type  : void
 */
void c_kinematicTrajectory_set_Posit(kinematicTrajectory *obj, const double val
  [3])
{
  obj->Position[0] = val[0];
  obj->Position[1] = val[1];
  obj->Position[2] = val[2];
}

/*
 * Arguments    : kinematicTrajectory *obj
 *                const double val[3]
 * Return Type  : void
 */
void c_kinematicTrajectory_set_Veloc(kinematicTrajectory *obj, const double val
  [3])
{
  obj->Velocity[0] = val[0];
  obj->Velocity[1] = val[1];
  obj->Velocity[2] = val[2];
}

/*
 * Arguments    : kinematicTrajectory *obj
 *                const double varargin_1[6]
 *                const double varargin_2[6]
 *                double pos[6]
 *                double vel[6]
 *                double acc[6]
 *                double av[6]
 * Return Type  : void
 */
void kinematicTrajectory_stepImpl(kinematicTrajectory *obj, const double
  varargin_1[6], const double varargin_2[6], double pos[6], double vel[6],
  double acc[6], double av[6])
{
  double dt;
  int k;
  double q_a[2];
  double b_varargin_1[6];
  double qb[2];
  double q_c[2];
  double q_d[2];
  double theta[2];
  double z1[6];
  double qimag_idx_0;
  double qimag_idx_1;
  double qimag_idx_2;
  double ct[2];
  double prevQ_d;
  double rhs_a;
  double rhs_b;
  double rhs_c;
  double rhs_d;
  double q_b[2];
  double b_vel[3];
  dt = 1.0 / obj->SampleRate;
  for (k = 0; k < 6; k++) {
    b_varargin_1[k] = varargin_2[k] * dt;
  }

  q_a[0] = 1.0;
  qb[0] = 0.0;
  q_c[0] = 0.0;
  q_d[0] = 0.0;
  q_a[1] = 1.0;
  qb[1] = 0.0;
  q_c[1] = 0.0;
  q_d[1] = 0.0;
  for (k = 0; k < 6; k++) {
    z1[k] = b_varargin_1[k] * b_varargin_1[k];
  }

  theta[0] = z1[0] + z1[2];
  theta[1] = z1[1] + z1[3];
  theta[0] += z1[4];
  theta[1] += z1[5];
  for (k = 0; k < 2; k++) {
    qimag_idx_0 = sqrt(theta[k]);
    theta[k] = qimag_idx_0;
    ct[k] = cos(qimag_idx_0 / 2.0);
    qimag_idx_1 = sin(qimag_idx_0 / 2.0);
    if (qimag_idx_0 != 0.0) {
      q_a[k] = ct[k];
      qb[k] = b_varargin_1[k] / qimag_idx_0 * qimag_idx_1;
      q_c[k] = b_varargin_1[k + 2] / qimag_idx_0 * qimag_idx_1;
      q_d[k] = b_varargin_1[k + 4] / qimag_idx_0 * qimag_idx_1;
    }
  }

  qimag_idx_0 = obj->pOrientation.a;
  qimag_idx_1 = obj->pOrientation.b;
  qimag_idx_2 = obj->pOrientation.c;
  prevQ_d = obj->pOrientation.d;
  quaternioncg_times(qimag_idx_0, qimag_idx_1, qimag_idx_2, prevQ_d, q_a[0], qb
                     [0], q_c[0], q_d[0], &rhs_a, &rhs_b, &rhs_c, &rhs_d);
  q_a[0] = rhs_a;
  q_b[0] = rhs_b;
  q_c[0] = rhs_c;
  q_d[0] = rhs_d;
  quaternioncg_times(rhs_a, rhs_b, rhs_c, rhs_d, q_a[1], qb[1], q_c[1], q_d[1],
                     &rhs_a, &rhs_b, &rhs_c, &rhs_d);
  obj->pOrientation.a = rhs_a;
  obj->pOrientation.b = rhs_b;
  obj->pOrientation.c = rhs_c;
  obj->pOrientation.d = rhs_d;
  quaternionBase_vertcat(qimag_idx_0, qimag_idx_1, qimag_idx_2, prevQ_d, q_a[0],
    q_b[0], q_c[0], q_d[0], q_a, q_b, q_c, q_d);
  quaternionBase_rotatepoint(q_a, q_b, q_c, q_d, varargin_2, av);
  quaternionBase_rotatepoint(q_a, q_b, q_c, q_d, varargin_1, acc);
  qimag_idx_0 = obj->Velocity[0];
  qimag_idx_1 = obj->Velocity[1];
  qimag_idx_2 = obj->Velocity[2];
  for (k = 0; k < 6; k++) {
    vel[k] = acc[k] * dt;
  }

  vel[0] += qimag_idx_0;
  vel[2] += qimag_idx_1;
  vel[4] += qimag_idx_2;
  vel[1] += vel[0];
  vel[3] += vel[2];
  vel[5] += vel[4];
  b_vel[0] = vel[1];
  b_vel[1] = vel[3];
  b_vel[2] = vel[5];
  c_kinematicTrajectory_set_Veloc(obj, b_vel);
  b_varargin_1[0] = qimag_idx_0;
  b_varargin_1[1] = vel[0];
  b_varargin_1[2] = qimag_idx_1;
  b_varargin_1[3] = vel[2];
  b_varargin_1[4] = qimag_idx_2;
  b_varargin_1[5] = vel[4];
  for (k = 0; k < 6; k++) {
    vel[k] = b_varargin_1[k];
  }

  qimag_idx_0 = obj->Position[0];
  qimag_idx_1 = obj->Position[1];
  qimag_idx_2 = obj->Position[2];
  prevQ_d = dt * dt;
  for (k = 0; k < 6; k++) {
    pos[k] = vel[k] * dt + 0.5 * acc[k] * prevQ_d;
  }

  pos[0] += qimag_idx_0;
  pos[2] += qimag_idx_1;
  pos[4] += qimag_idx_2;
  pos[1] += pos[0];
  pos[3] += pos[2];
  pos[5] += pos[4];
  b_vel[0] = pos[1];
  b_vel[1] = pos[3];
  b_vel[2] = pos[5];
  c_kinematicTrajectory_set_Posit(obj, b_vel);
  b_varargin_1[0] = qimag_idx_0;
  b_varargin_1[1] = pos[0];
  b_varargin_1[2] = qimag_idx_1;
  b_varargin_1[3] = pos[2];
  b_varargin_1[4] = qimag_idx_2;
  b_varargin_1[5] = pos[4];
  for (k = 0; k < 6; k++) {
    pos[k] = b_varargin_1[k];
  }
}

/*
 * File trailer for kinematicTrajectory.c
 *
 * [EOF]
 */
