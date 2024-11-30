/*
 * slrt_ex_osc_ucf.c
 *
 * Code generation for model "slrt_ex_osc_ucf".
 *
 * Model version              : 2.1
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Sun Apr 23 19:10:56 2023
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "slrt_ex_osc_ucf.h"
#include "slrt_ex_osc_ucf_private.h"
#include "slrt_ex_osc_ucf_dt.h"

/* Block signals (default storage) */
B_slrt_ex_osc_ucf_T slrt_ex_osc_ucf_B;

/* Continuous states */
X_slrt_ex_osc_ucf_T slrt_ex_osc_ucf_X;

/* Block states (default storage) */
DW_slrt_ex_osc_ucf_T slrt_ex_osc_ucf_DW;

/* External outputs (root outports fed by signals with default storage) */
ExtY_slrt_ex_osc_ucf_T slrt_ex_osc_ucf_Y;

/* Real-time model */
static RT_MODEL_slrt_ex_osc_ucf_T slrt_ex_osc_ucf_M_;
RT_MODEL_slrt_ex_osc_ucf_T *const slrt_ex_osc_ucf_M = &slrt_ex_osc_ucf_M_;

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  slrt_ex_osc_ucf_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  slrt_ex_osc_ucf_step();
  slrt_ex_osc_ucf_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  slrt_ex_osc_ucf_step();
  slrt_ex_osc_ucf_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  slrt_ex_osc_ucf_step();
  slrt_ex_osc_ucf_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void slrt_ex_osc_ucf_step(void)
{
  real_T temp;
  if (rtmIsMajorTimeStep(slrt_ex_osc_ucf_M)) {
    /* set solver stop time */
    if (!(slrt_ex_osc_ucf_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&slrt_ex_osc_ucf_M->solverInfo,
                            ((slrt_ex_osc_ucf_M->Timing.clockTickH0 + 1) *
        slrt_ex_osc_ucf_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&slrt_ex_osc_ucf_M->solverInfo,
                            ((slrt_ex_osc_ucf_M->Timing.clockTick0 + 1) *
        slrt_ex_osc_ucf_M->Timing.stepSize0 +
        slrt_ex_osc_ucf_M->Timing.clockTickH0 *
        slrt_ex_osc_ucf_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(slrt_ex_osc_ucf_M)) {
    slrt_ex_osc_ucf_M->Timing.t[0] = rtsiGetT(&slrt_ex_osc_ucf_M->solverInfo);
  }

  /* TransferFcn: '<Root>/Transfer Fcn' */
  slrt_ex_osc_ucf_B.XfrFnc = 0.0;
  slrt_ex_osc_ucf_B.XfrFnc += slrt_ex_osc_ucf_P.TransferFcn_C[0] *
    slrt_ex_osc_ucf_X.TransferFcn_CSTATE[0];
  slrt_ex_osc_ucf_B.XfrFnc += slrt_ex_osc_ucf_P.TransferFcn_C[1] *
    slrt_ex_osc_ucf_X.TransferFcn_CSTATE[1];

  /* SignalGenerator: '<Root>/Signal Generator' */
  temp = slrt_ex_osc_ucf_P.SignalGenerator_Frequency *
    slrt_ex_osc_ucf_M->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    /* SignalGenerator: '<Root>/Signal Generator' */
    slrt_ex_osc_ucf_B.SigGen = slrt_ex_osc_ucf_P.SignalGenerator_Amplitude;
  } else {
    /* SignalGenerator: '<Root>/Signal Generator' */
    slrt_ex_osc_ucf_B.SigGen = -slrt_ex_osc_ucf_P.SignalGenerator_Amplitude;
  }

  /* End of SignalGenerator: '<Root>/Signal Generator' */

  /* Outport: '<Root>/Out1' */
  slrt_ex_osc_ucf_Y.Out1[0] = slrt_ex_osc_ucf_B.XfrFnc;
  slrt_ex_osc_ucf_Y.Out1[1] = slrt_ex_osc_ucf_B.SigGen;
  if (rtmIsMajorTimeStep(slrt_ex_osc_ucf_M)) {
  }

  if (rtmIsMajorTimeStep(slrt_ex_osc_ucf_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(slrt_ex_osc_ucf_M->rtwLogInfo,
                        (slrt_ex_osc_ucf_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(slrt_ex_osc_ucf_M)) {
    /* External mode */
    rtExtModeUploadCheckTrigger(2);

    {                                  /* Sample time: [0.0s, 0.0s] */
      rtExtModeUpload(0, (real_T)slrt_ex_osc_ucf_M->Timing.t[0]);
    }

    if (rtmIsMajorTimeStep(slrt_ex_osc_ucf_M)) {/* Sample time: [0.00025s, 0.0s] */
      rtExtModeUpload(1, (real_T)(((slrt_ex_osc_ucf_M->Timing.clockTick1+
        slrt_ex_osc_ucf_M->Timing.clockTickH1* 4294967296.0)) * 0.00025));
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(slrt_ex_osc_ucf_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(slrt_ex_osc_ucf_M)!=-1) &&
          !((rtmGetTFinal(slrt_ex_osc_ucf_M)-
             (((slrt_ex_osc_ucf_M->Timing.clockTick1+
                slrt_ex_osc_ucf_M->Timing.clockTickH1* 4294967296.0)) * 0.00025))
            > (((slrt_ex_osc_ucf_M->Timing.clockTick1+
                 slrt_ex_osc_ucf_M->Timing.clockTickH1* 4294967296.0)) * 0.00025)
            * (DBL_EPSILON))) {
        rtmSetErrorStatus(slrt_ex_osc_ucf_M, "Simulation finished");
      }

      if (rtmGetStopRequested(slrt_ex_osc_ucf_M)) {
        rtmSetErrorStatus(slrt_ex_osc_ucf_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&slrt_ex_osc_ucf_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++slrt_ex_osc_ucf_M->Timing.clockTick0)) {
      ++slrt_ex_osc_ucf_M->Timing.clockTickH0;
    }

    slrt_ex_osc_ucf_M->Timing.t[0] = rtsiGetSolverStopTime
      (&slrt_ex_osc_ucf_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.00025s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.00025, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      slrt_ex_osc_ucf_M->Timing.clockTick1++;
      if (!slrt_ex_osc_ucf_M->Timing.clockTick1) {
        slrt_ex_osc_ucf_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void slrt_ex_osc_ucf_derivatives(void)
{
  XDot_slrt_ex_osc_ucf_T *_rtXdot;
  _rtXdot = ((XDot_slrt_ex_osc_ucf_T *) slrt_ex_osc_ucf_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE[0] = 0.0;
  _rtXdot->TransferFcn_CSTATE[0] += slrt_ex_osc_ucf_P.TransferFcn_A[0] *
    slrt_ex_osc_ucf_X.TransferFcn_CSTATE[0];
  _rtXdot->TransferFcn_CSTATE[1] = 0.0;
  _rtXdot->TransferFcn_CSTATE[0] += slrt_ex_osc_ucf_P.TransferFcn_A[1] *
    slrt_ex_osc_ucf_X.TransferFcn_CSTATE[1];
  _rtXdot->TransferFcn_CSTATE[1] += slrt_ex_osc_ucf_X.TransferFcn_CSTATE[0];
  _rtXdot->TransferFcn_CSTATE[0] += slrt_ex_osc_ucf_B.SigGen;
}

/* Model initialize function */
void slrt_ex_osc_ucf_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)slrt_ex_osc_ucf_M, 0,
                sizeof(RT_MODEL_slrt_ex_osc_ucf_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&slrt_ex_osc_ucf_M->solverInfo,
                          &slrt_ex_osc_ucf_M->Timing.simTimeStep);
    rtsiSetTPtr(&slrt_ex_osc_ucf_M->solverInfo, &rtmGetTPtr(slrt_ex_osc_ucf_M));
    rtsiSetStepSizePtr(&slrt_ex_osc_ucf_M->solverInfo,
                       &slrt_ex_osc_ucf_M->Timing.stepSize0);
    rtsiSetdXPtr(&slrt_ex_osc_ucf_M->solverInfo, &slrt_ex_osc_ucf_M->derivs);
    rtsiSetContStatesPtr(&slrt_ex_osc_ucf_M->solverInfo, (real_T **)
                         &slrt_ex_osc_ucf_M->contStates);
    rtsiSetNumContStatesPtr(&slrt_ex_osc_ucf_M->solverInfo,
      &slrt_ex_osc_ucf_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&slrt_ex_osc_ucf_M->solverInfo,
      &slrt_ex_osc_ucf_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&slrt_ex_osc_ucf_M->solverInfo,
      &slrt_ex_osc_ucf_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&slrt_ex_osc_ucf_M->solverInfo,
      &slrt_ex_osc_ucf_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&slrt_ex_osc_ucf_M->solverInfo, (&rtmGetErrorStatus
      (slrt_ex_osc_ucf_M)));
    rtsiSetRTModelPtr(&slrt_ex_osc_ucf_M->solverInfo, slrt_ex_osc_ucf_M);
  }

  rtsiSetSimTimeStep(&slrt_ex_osc_ucf_M->solverInfo, MAJOR_TIME_STEP);
  slrt_ex_osc_ucf_M->intgData.y = slrt_ex_osc_ucf_M->odeY;
  slrt_ex_osc_ucf_M->intgData.f[0] = slrt_ex_osc_ucf_M->odeF[0];
  slrt_ex_osc_ucf_M->intgData.f[1] = slrt_ex_osc_ucf_M->odeF[1];
  slrt_ex_osc_ucf_M->intgData.f[2] = slrt_ex_osc_ucf_M->odeF[2];
  slrt_ex_osc_ucf_M->intgData.f[3] = slrt_ex_osc_ucf_M->odeF[3];
  slrt_ex_osc_ucf_M->contStates = ((X_slrt_ex_osc_ucf_T *) &slrt_ex_osc_ucf_X);
  rtsiSetSolverData(&slrt_ex_osc_ucf_M->solverInfo, (void *)
                    &slrt_ex_osc_ucf_M->intgData);
  rtsiSetSolverName(&slrt_ex_osc_ucf_M->solverInfo,"ode4");
  rtmSetTPtr(slrt_ex_osc_ucf_M, &slrt_ex_osc_ucf_M->Timing.tArray[0]);
  rtmSetTFinal(slrt_ex_osc_ucf_M, 1.0);
  slrt_ex_osc_ucf_M->Timing.stepSize0 = 0.00025;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    slrt_ex_osc_ucf_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    /*
     * Set pointers to the data and signal info each state
     */
    {
      static int_T rt_LoggedStateWidths[] = {
        2
      };

      static int_T rt_LoggedStateNumDimensions[] = {
        1
      };

      static int_T rt_LoggedStateDimensions[] = {
        2
      };

      static boolean_T rt_LoggedStateIsVarDims[] = {
        0
      };

      static BuiltInDTypeId rt_LoggedStateDataTypeIds[] = {
        SS_DOUBLE
      };

      static int_T rt_LoggedStateComplexSignals[] = {
        0
      };

      static RTWPreprocessingFcnPtr rt_LoggingStatePreprocessingFcnPtrs[] = {
        (NULL)
      };

      static const char_T *rt_LoggedStateLabels[] = {
        "CSTATE"
      };

      static const char_T *rt_LoggedStateBlockNames[] = {
        "slrt_ex_osc_ucf/Transfer Fcn"
      };

      static const char_T *rt_LoggedStateNames[] = {
        ""
      };

      static boolean_T rt_LoggedStateCrossMdlRef[] = {
        0
      };

      static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert[] = {
        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 }
      };

      static RTWLogSignalInfo rt_LoggedStateSignalInfo = {
        1,
        rt_LoggedStateWidths,
        rt_LoggedStateNumDimensions,
        rt_LoggedStateDimensions,
        rt_LoggedStateIsVarDims,
        (NULL),
        (NULL),
        rt_LoggedStateDataTypeIds,
        rt_LoggedStateComplexSignals,
        (NULL),
        rt_LoggingStatePreprocessingFcnPtrs,

        { rt_LoggedStateLabels },
        (NULL),
        (NULL),
        (NULL),

        { rt_LoggedStateBlockNames },

        { rt_LoggedStateNames },
        rt_LoggedStateCrossMdlRef,
        rt_RTWLogDataTypeConvert
      };

      static void * rt_LoggedStateSignalPtrs[1];
      rtliSetLogXSignalPtrs(slrt_ex_osc_ucf_M->rtwLogInfo, (LogSignalPtrsType)
                            rt_LoggedStateSignalPtrs);
      rtliSetLogXSignalInfo(slrt_ex_osc_ucf_M->rtwLogInfo,
                            &rt_LoggedStateSignalInfo);
      rt_LoggedStateSignalPtrs[0] = (void*)
        &slrt_ex_osc_ucf_X.TransferFcn_CSTATE[0];
    }

    rtliSetLogT(slrt_ex_osc_ucf_M->rtwLogInfo, "tout");
    rtliSetLogX(slrt_ex_osc_ucf_M->rtwLogInfo, "xout");
    rtliSetLogXFinal(slrt_ex_osc_ucf_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(slrt_ex_osc_ucf_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(slrt_ex_osc_ucf_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(slrt_ex_osc_ucf_M->rtwLogInfo, 0);
    rtliSetLogDecimation(slrt_ex_osc_ucf_M->rtwLogInfo, 1);

    /*
     * Set pointers to the data and signal info for each output
     */
    {
      static void * rt_LoggedOutputSignalPtrs[] = {
        &slrt_ex_osc_ucf_Y.Out1[0]
      };

      rtliSetLogYSignalPtrs(slrt_ex_osc_ucf_M->rtwLogInfo, ((LogSignalPtrsType)
        rt_LoggedOutputSignalPtrs));
    }

    {
      static int_T rt_LoggedOutputWidths[] = {
        2
      };

      static int_T rt_LoggedOutputNumDimensions[] = {
        1
      };

      static int_T rt_LoggedOutputDimensions[] = {
        2
      };

      static boolean_T rt_LoggedOutputIsVarDims[] = {
        0
      };

      static void* rt_LoggedCurrentSignalDimensions[] = {
        (NULL)
      };

      static int_T rt_LoggedCurrentSignalDimensionsSize[] = {
        4
      };

      static BuiltInDTypeId rt_LoggedOutputDataTypeIds[] = {
        SS_DOUBLE
      };

      static int_T rt_LoggedOutputComplexSignals[] = {
        0
      };

      static RTWPreprocessingFcnPtr rt_LoggingPreprocessingFcnPtrs[] = {
        (NULL)
      };

      static const char_T *rt_LoggedOutputLabels[] = {
        "MuxOut" };

      static const char_T *rt_LoggedOutputBlockNames[] = {
        "slrt_ex_osc_ucf/Out1" };

      static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert[] = {
        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 }
      };

      static RTWLogSignalInfo rt_LoggedOutputSignalInfo[] = {
        {
          1,
          rt_LoggedOutputWidths,
          rt_LoggedOutputNumDimensions,
          rt_LoggedOutputDimensions,
          rt_LoggedOutputIsVarDims,
          rt_LoggedCurrentSignalDimensions,
          rt_LoggedCurrentSignalDimensionsSize,
          rt_LoggedOutputDataTypeIds,
          rt_LoggedOutputComplexSignals,
          (NULL),
          rt_LoggingPreprocessingFcnPtrs,

          { rt_LoggedOutputLabels },
          (NULL),
          (NULL),
          (NULL),

          { rt_LoggedOutputBlockNames },

          { (NULL) },
          (NULL),
          rt_RTWLogDataTypeConvert
        }
      };

      rtliSetLogYSignalInfo(slrt_ex_osc_ucf_M->rtwLogInfo,
                            rt_LoggedOutputSignalInfo);

      /* set currSigDims field */
      rt_LoggedCurrentSignalDimensions[0] = &rt_LoggedOutputWidths[0];
    }

    rtliSetLogY(slrt_ex_osc_ucf_M->rtwLogInfo, "yout");
  }

  /* External mode info */
  slrt_ex_osc_ucf_M->Sizes.checksums[0] = (2470199659U);
  slrt_ex_osc_ucf_M->Sizes.checksums[1] = (3586245950U);
  slrt_ex_osc_ucf_M->Sizes.checksums[2] = (2199307218U);
  slrt_ex_osc_ucf_M->Sizes.checksums[3] = (3026185216U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    slrt_ex_osc_ucf_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(slrt_ex_osc_ucf_M->extModeInfo,
      &slrt_ex_osc_ucf_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(slrt_ex_osc_ucf_M->extModeInfo,
                        slrt_ex_osc_ucf_M->Sizes.checksums);
    rteiSetTPtr(slrt_ex_osc_ucf_M->extModeInfo, rtmGetTPtr(slrt_ex_osc_ucf_M));
  }

  /* block I/O */
  (void) memset(((void *) &slrt_ex_osc_ucf_B), 0,
                sizeof(B_slrt_ex_osc_ucf_T));

  /* states (continuous) */
  {
    (void) memset((void *)&slrt_ex_osc_ucf_X, 0,
                  sizeof(X_slrt_ex_osc_ucf_T));
  }

  /* states (dwork) */
  (void) memset((void *)&slrt_ex_osc_ucf_DW, 0,
                sizeof(DW_slrt_ex_osc_ucf_T));

  /* external outputs */
  (void) memset(&slrt_ex_osc_ucf_Y.Out1[0], 0,
                2U*sizeof(real_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    slrt_ex_osc_ucf_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(slrt_ex_osc_ucf_M->rtwLogInfo, 0.0,
    rtmGetTFinal(slrt_ex_osc_ucf_M), slrt_ex_osc_ucf_M->Timing.stepSize0,
    (&rtmGetErrorStatus(slrt_ex_osc_ucf_M)));

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  slrt_ex_osc_ucf_X.TransferFcn_CSTATE[0] = 0.0;
  slrt_ex_osc_ucf_X.TransferFcn_CSTATE[1] = 0.0;
}

/* Model terminate function */
void slrt_ex_osc_ucf_terminate(void)
{
  /* (no terminate code required) */
}
