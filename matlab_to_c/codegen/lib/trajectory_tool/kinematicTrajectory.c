/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: kinematicTrajectory.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 26-Feb-2019 13:17:28
 */

/* Include Files */
#include <string.h>
#include "trajectory_tool.h"
#include "kinematicTrajectory.h"
#include "rotatepoint.h"
#include "vertcat.h"
#include "quaternioncg.h"

/* Function Declarations */
static void c_kinematicTrajectory_set_Posit(kinematicTrajectory *obj, const
  double val[3]);
static void c_kinematicTrajectory_set_Veloc(kinematicTrajectory *obj, const
  double val[3]);

/* Function Definitions */

/*
 * Arguments    : kinematicTrajectory *obj
 *                const double val[3]
 * Return Type  : void
 */
static void c_kinematicTrajectory_set_Posit(kinematicTrajectory *obj, const
  double val[3])
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
static void c_kinematicTrajectory_set_Veloc(kinematicTrajectory *obj, const
  double val[3])
{
  obj->Velocity[0] = val[0];
  obj->Velocity[1] = val[1];
  obj->Velocity[2] = val[2];
}

/*
 * Arguments    : kinematicTrajectory *obj
 * Return Type  : kinematicTrajectory *
 */
kinematicTrajectory *c_kinematicTrajectory_kinematic(kinematicTrajectory *obj)
{
  kinematicTrajectory *b_obj;
  b_obj = obj;
  b_obj->SampleRate = 100.0;
  b_obj->Position[0] = 0.0;
  b_obj->Position[1] = 0.0;
  b_obj->Position[2] = 0.0;
  b_obj->Velocity[0] = 0.0;
  b_obj->Velocity[1] = 0.0;
  b_obj->Velocity[2] = 0.0;
  b_obj->Acceleration[0] = 0.0;
  b_obj->Acceleration[1] = 0.0;
  b_obj->Acceleration[2] = 0.0;
  b_obj->AngularVelocity[0] = 0.0;
  b_obj->AngularVelocity[1] = 0.0;
  b_obj->AngularVelocity[2] = 0.0;
  b_obj->isInitialized = 0;
  b_obj->pOrientation.a = 1.0;
  b_obj->pOrientation.b = 0.0;
  b_obj->pOrientation.c = 0.0;
  b_obj->pOrientation.d = 0.0;
  return b_obj;
}

/*
 * Arguments    : kinematicTrajectory *obj
 *                const double varargin_1[4800]
 *                const double varargin_2[4800]
 *                double pos[4800]
 *                double vel[4800]
 *                double acc[4800]
 *                double av[4800]
 * Return Type  : void
 */
void kinematicTrajectory_stepImpl(kinematicTrajectory *obj, const double
  varargin_1[4800], const double varargin_2[4800], double pos[4800], double vel
  [4800], double acc[4800], double av[4800])
{
  double dt;
  int i;
  static double b_varargin_2[4800];
  static d_matlabshared_rotations_intern q;
  double prevQ_a;
  double prevQ_b;
  double prevQ_c;
  double prevQ_d;
  double t1_a;
  double t1_b;
  double t1_c;
  double t1_d;
  double t2_a;
  double t2_b;
  double t2_c;
  double t2_d;
  static double dv0[1599];
  static double t3_a[1599];
  double t3_b[1599];
  double t3_c[1599];
  double t3_d[1599];
  double prevVel[3];
  int k;
  double b_vel[3];
  int b_k;
  int vel_tmp;
  dt = 1.0 / obj->SampleRate;
  for (i = 0; i < 4800; i++) {
    b_varargin_2[i] = varargin_2[i] * dt;
  }

  quaternioncg_quaternioncg(b_varargin_2, q.a, q.b, q.c, q.d);
  prevQ_a = obj->pOrientation.a;
  prevQ_b = obj->pOrientation.b;
  prevQ_c = obj->pOrientation.c;
  prevQ_d = obj->pOrientation.d;
  quaternioncg_parenReference(q.a, q.b, q.c, q.d, 1.0, &t1_a, &t1_b, &t1_c,
    &t1_d);
  quaternioncg_times(prevQ_a, prevQ_b, prevQ_c, prevQ_d, t1_a, t1_b, t1_c, t1_d,
                     &t1_a, &t1_b, &t1_c, &t1_d);
  quaternioncg_parenAssign(&q, t1_a, t1_b, t1_c, t1_d, 1.0);
  for (i = 0; i < 1599; i++) {
    quaternioncg_parenReference(q.a, q.b, q.c, q.d, (2.0 + (double)i) - 1.0,
      &t1_a, &t1_b, &t1_c, &t1_d);
    quaternioncg_parenReference(q.a, q.b, q.c, q.d, 2.0 + (double)i, &t2_a,
      &t2_b, &t2_c, &t2_d);
    quaternioncg_times(t1_a, t1_b, t1_c, t1_d, t2_a, t2_b, t2_c, t2_d, &t1_a,
                       &t1_b, &t1_c, &t1_d);
    quaternioncg_parenAssign(&q, t1_a, t1_b, t1_c, t1_d, 2.0 + (double)i);
  }

  quaternioncg_parenReference(q.a, q.b, q.c, q.d, 1600.0, &obj->pOrientation.a,
    &obj->pOrientation.b, &obj->pOrientation.c, &obj->pOrientation.d);
  for (i = 0; i < 1599; i++) {
    dv0[i] = 1.0 + (double)i;
  }

  b_quaternioncg_parenReference(q.a, q.b, q.c, q.d, dv0, t3_a, t3_b, t3_c, t3_d);
  quaternionBase_vertcat(prevQ_a, prevQ_b, prevQ_c, prevQ_d, t3_a, t3_b, t3_c,
    t3_d, q.a, q.b, q.c, q.d);
  quaternionBase_rotatepoint(q.a, q.b, q.c, q.d, varargin_2, av);
  quaternionBase_rotatepoint(q.a, q.b, q.c, q.d, varargin_1, acc);
  prevVel[0] = obj->Velocity[0];
  prevVel[1] = obj->Velocity[1];
  prevVel[2] = obj->Velocity[2];
  for (i = 0; i < 4800; i++) {
    vel[i] = acc[i] * dt;
  }

  vel[0] += prevVel[0];
  vel[1600] += prevVel[1];
  vel[3200] += prevVel[2];
  for (k = 0; k < 3; k++) {
    for (b_k = 0; b_k < 1599; b_k++) {
      i = b_k + 1600 * k;
      vel_tmp = i + 1;
      vel[vel_tmp] += vel[i];
    }
  }

  b_vel[0] = vel[1599];
  b_vel[1] = vel[3199];
  b_vel[2] = vel[4799];
  c_kinematicTrajectory_set_Veloc(obj, b_vel);
  for (i = 0; i < 3; i++) {
    b_varargin_2[1600 * i] = prevVel[i];
    memcpy(&b_varargin_2[i * 1600 + 1], &vel[i * 1600], 1599U * sizeof(double));
  }

  memcpy(&vel[0], &b_varargin_2[0], 4800U * sizeof(double));
  prevVel[0] = obj->Position[0];
  prevVel[1] = obj->Position[1];
  prevVel[2] = obj->Position[2];
  prevQ_a = dt * dt;
  for (i = 0; i < 4800; i++) {
    pos[i] = vel[i] * dt + 0.5 * acc[i] * prevQ_a;
  }

  pos[0] += prevVel[0];
  pos[1600] += prevVel[1];
  pos[3200] += prevVel[2];
  for (k = 0; k < 3; k++) {
    for (b_k = 0; b_k < 1599; b_k++) {
      i = b_k + 1600 * k;
      vel_tmp = i + 1;
      pos[vel_tmp] += pos[i];
    }
  }

  b_vel[0] = pos[1599];
  b_vel[1] = pos[3199];
  b_vel[2] = pos[4799];
  c_kinematicTrajectory_set_Posit(obj, b_vel);
  for (i = 0; i < 3; i++) {
    b_varargin_2[1600 * i] = prevVel[i];
    memcpy(&b_varargin_2[i * 1600 + 1], &pos[i * 1600], 1599U * sizeof(double));
  }

  memcpy(&pos[0], &b_varargin_2[0], 4800U * sizeof(double));
}

/*
 * File trailer for kinematicTrajectory.c
 *
 * [EOF]
 */
