/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: SystemCore.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 01-Mar-2019 15:09:29
 */

/* Include Files */
#include <string.h>
#include "rt_nonfinite.h"
#include "kal_tool.h"
#include "SystemCore.h"
#include "AHRSFilterBase.h"

/* Function Declarations */
static void SystemCore_checkTunableProps(c_fusion_internal_coder_ahrsfil *obj);
static void SystemCore_setupAndReset(c_fusion_internal_coder_ahrsfil *obj, const
  double varargin_1[4800]);

/* Function Definitions */

/*
 * Arguments    : c_fusion_internal_coder_ahrsfil *obj
 * Return Type  : void
 */
static void SystemCore_checkTunableProps(c_fusion_internal_coder_ahrsfil *obj)
{
  if (obj->TunablePropsChanged) {
    obj->TunablePropsChanged = false;
    c_AHRSFilterBase_updateMeasurem(obj);
  }
}

/*
 * Arguments    : c_fusion_internal_coder_ahrsfil *obj
 *                const double varargin_1[4800]
 * Return Type  : void
 */
static void SystemCore_setupAndReset(c_fusion_internal_coder_ahrsfil *obj, const
  double varargin_1[4800])
{
  static const double dv0[144] = { 6.0923483957341713E-6, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6.0923483957341713E-6, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6.0923483957341713E-6, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 7.6154354946677142E-5, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 7.6154354946677142E-5,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    7.6154354946677142E-5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0096236100000000012, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0096236100000000012, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0096236100000000012, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.6 };

  obj->isInitialized = 1;
  memcpy(&obj->pInputPrototype[0], &varargin_1[0], 4800U * sizeof(double));
  obj->pSensorPeriod = 0.01;
  obj->pKalmanPeriod = obj->pSensorPeriod;
  obj->TunablePropsChanged = false;
  obj->pOrientPost.a = 1.0;
  obj->pOrientPost.b = 0.0;
  obj->pOrientPost.c = 0.0;
  obj->pOrientPost.d = 0.0;
  obj->pGyroOffset[0] = 0.0;
  obj->pMagVec[0] = 0.0;
  obj->pGyroOffset[1] = 0.0;
  obj->pMagVec[1] = 0.0;
  obj->pGyroOffset[2] = 0.0;
  obj->pMagVec[2] = 0.0;
  obj->pMagVec[0] = obj->ExpectedMagneticFieldStrength;
  c_AHRSFilterBase_updateMeasurem(obj);
  memcpy(&obj->pQw[0], &dv0[0], 144U * sizeof(double));
  obj->pLinAccelPost[0] = 0.0;
  obj->pLinAccelPost[1] = 0.0;
  obj->pLinAccelPost[2] = 0.0;
  obj->pFirstTime = true;
}

/*
 * Arguments    : c_fusion_internal_coder_ahrsfil *obj
 *                const double varargin_1[4800]
 *                const double varargin_2[4800]
 *                const double varargin_3[4800]
 *                d_matlabshared_rotations_intern *varargout_1
 *                double varargout_2[4800]
 * Return Type  : void
 */
void SystemCore_parenReference(c_fusion_internal_coder_ahrsfil *obj, const
  double varargin_1[4800], const double varargin_2[4800], const double
  varargin_3[4800], d_matlabshared_rotations_intern *varargout_1, double
  varargout_2[4800])
{
  if (obj->isInitialized != 1) {
    SystemCore_setupAndReset(obj, varargin_1);
  }

  SystemCore_checkTunableProps(obj);
  AHRSFilterBase_stepImpl(obj, varargin_1, varargin_2, varargin_3, varargout_1,
    varargout_2);
}

/*
 * File trailer for SystemCore.c
 *
 * [EOF]
 */
