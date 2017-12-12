/*
  @file servo360.h

  @author Parallax Inc

  @copyright
  Copyright (C) Parallax Inc. 2017. All Rights MIT Licensed.  See end of file.
 
  @brief 
*/



//#define _servo360_monitor_



#ifndef SERVO360_H
#define SERVO360_H

#if defined(__cplusplus)
extern "C" {
#endif


#include "simpletools.h"  
//#include "patch.h"

#ifdef _servo360_monitor_
  #include "fdserial.h"
#endif



#ifndef DOXYGEN_SHOULD_SKIP_THIS



#define S360_UNITS_FULL_CIRCLE 360
#define S360_MAX_SPEED 2 * 4096 

#define S360_VM 180
//#define S360_VB_POS 200
//#define S360_VB_NEG -200
#define S360_VM_CCW S360_VM
#define S360_VM_CW S360_VM

#define S360_VM_CCW S360_VM
#define S360_VM_CW S360_VM
#define S360_VB_CCW 200
#define S360_VB_CW -200

#define S360_DUTY_CYCLE_MIN 290
#define S360_DUTY_CYCLE_MAX 9710

#define S360_CCW_POS 1
#define S360_CCW_NEG -1

#define S360_SPEED 1
#define S360_POSITION 2
#define S360_GOTO 3
#define S360_MONITOR 4
#define S360_FREQ_CTRL_SIG 50
#define S360_DEVS_MAX 4

//#define S360_RAMP_STEP 10 * 4096 / 360;
#define S360_RAMP_STEP 72 * 4096 / 360;

// Rename to indicate encoder
#define S360_M 4348
#define S360_B -129
#define S360_ENC_RES 4096

/*
#define S360_KPA 5000
#define S360_KIA 150
#define S360_KDA 0
#define S360_POS_INTGRL_MAX 150
#define S360_SCALE_DEN_A 1000
*/

//
#define S360_KPA 12000
#define S360_KIA 600
#define S360_KDA 6000
#define S360_POS_INTGRL_MAX 600
#define S360_SCALE_DEN_A 1000
//

/*
#define S360_KPV 3000
#define S360_KIV 500
#define S360_KDV 1600
#define S360_VEL_INTGRL_MAX 325
*/
#define S360_KPV 500
#define S360_KIV 0
#define S360_KDV 0
#define S360_VEL_INTGRL_MAX 0
#define S360_SCALE_DEN_V 1000

#define S360_PW_CENTER 15000
#define S360_CS_HZ 50
#define S360_UNITS_ENCODER 4096
#define S360_UNITS_REV 360

#define S360_SETTING_KPV 1
#define S360_SETTING_KIV 2
#define S360_SETTING_KDV 3
#define S360_SETTING_IV_MAX 4
#define S360_SETTING_KPA 5
#define S360_SETTING_KIA 6
#define S360_SETTING_KDA 7
#define S360_SETTING_IA_MAX 8
#define S360_SETTING_VB_CCW 9
#define S360_SETTING_VB_CW 10
#define S360_SETTING_VM_CCW 11    
#define S360_SETTING_VM_CW 12

//#define S360_A_MAX (((1 << 31) - 1)) / S360_UNITS_FULL_CIRCLE  // 524287 degrees
#define S360_A_MAX 524287  

#define S360_SCALE_DEN_COUPLE 1000        
#define S360_SCALE_COUPLE 2000   

#define S360_LATENCY 3  

#define S360_PWMAX 2400 
#define S360_PWMIN -2400 


/*

// WIP servo calibration updates
//40564

#ifndef _AB360_EE_Start_
#define _AB360_EE_Start_ 63418
#endif

#ifndef _AB360_EE_Pins_
#define _AB360_EE_Pins_ 12
#endif

#ifndef _AB360_EE_mVccwL_
#define _AB360_EE_mVccwL_ 28
#endif

#ifndef _AB360_EE_bVccwL_
#define _AB360_EE_bVccwL_ 32
#endif

#ifndef _AB360_EE_mVcwL_
#define _AB360_EE_mVcwL_ 36
#endif

#ifndef _AB360_EE_bVcwL_
#define _AB360_EE_bVcwL_ 40
#endif

#ifndef _AB360_EE_mVccwR_
#define _AB360_EE_mVccwR_ 44
#endif

#ifndef _AB360_EE_bVccwR_
#define _AB360_EE_bVccwR_ 48
#endif

#ifndef _AB360_EE_mVcwR_
#define _AB360_EE_mVcwR_ 52
#endif

#ifndef _AB360_EE_bVcwR_
#define _AB360_EE_bVcwR_ 56
#endif

#ifndef _AB360_EE_End_

#define _AB360_EE_End_ _AB360_EE_Start_ + 60
#endif

*/



                           ////// ALL SERVOS //////
//
typedef volatile struct servo360_cog_s 
{
  int *servoCog;
  volatile int lock360;
  volatile int t360;
  volatile int t360slice;
  volatile int fbSlice;
  volatile int spSlice;
  volatile int devCount;
  volatile int pulseCount;
  volatile int cntPrev;
  volatile int dt360;
  volatile int dt360a[2];
} servo360_cog_t;

extern volatile servo360_cog_t _fb360c;
//
                            ////// PER SERVO ///  ///
  
typedef volatile struct servo360_s 
{
  // settings
  volatile int pinCtrl;                       // pinControl
  volatile int pinFb;                       // pinFeedback
  volatile int angleSign;
  volatile int rampStep;
  volatile int speedLimit;
  volatile int feedback;
  volatile int angleMax;
  volatile int angleMin;
  volatile int unitsRev;
  volatile int couple;
  volatile int coupleScale;
  volatile int enable;
  
  volatile int vmCcw;
  volatile int vmCw;
  volatile int vbCcw;    
  volatile int vbCw;

  // admin
  volatile int csop;
  volatile int speedReq;
  
  // encoders
  volatile int dc, dcp;
  volatile int theta, thetaP;
  volatile int turns;
  volatile int angleFixed, angleFixedP; 
  volatile int angle, angleP, pvOffset;
  //volatile int stalled, noSignal;
  volatile int opMax;
  
  // pulse control
  volatile int speedOut;
  volatile int pw;
  
  // velocity control system
  volatile int opPidV;
  volatile int approachFlag;
  volatile int ticksDiff;
  volatile int ticksGuard;
  volatile int angleCalc;
  volatile int angleDeltaCalc;
  volatile int angleError;
  volatile int erDist, erDistP;
  volatile int speedTarget;
  volatile int speedTargetP;
  volatile int integralV; 
  volatile int derivativeV;
  volatile int opV;
  volatile int iMaxV;
  volatile int iMinV;
  volatile int KpV;
  volatile int KiV;
  volatile int KdV;
  volatile int pV, iV, dV;
  volatile int speedMeasured;
  volatile int drive;
  volatile int stepDir;
  volatile int lag;
  volatile int accelerating;
  volatile int speedTargetTemp;
  
  /*
  // This could remedy the overshoot problem, but it seems to reduce
  // drive_goto accuracy.
  
  #define FB360_OFFSET_MAX 5
  #define FB360_V_ARRAY 8

  volatile int vT[FB360_V_ARRAY];
  volatile int offset;
  */
  
  // position control system
  volatile int Kp;
  volatile int Ki;
  volatile int Kd;
  volatile int er, erP;
  volatile int sp, integral, derivative;
  volatile int op, iMax, iMin;
  volatile int p, i, d;
  
  // goto system
  volatile int angleTarget;
} 
servo360_t;

extern volatile servo360_t _fs[S360_DEVS_MAX];

// console
#ifdef _servo360_monitor_
  fdserial *term;
  extern volatile int suppressFbDisplay;
#endif



#endif // DOXYGEN_SHOULD_SKIP_THIS



/**
  @brief Initializes a connection to a Parallax Feedback 360 servo.
  
  @param pinControl I/O pin connected to the servo's white control signal line.
  
  @param pinFeedback I/O pin connected to the servo's yellow feedback line.
*/  
int servo360_connect(int pinControl, int pinFeedback);



/**
  @brief Set an angle for servo to move to and hold in degrees (360ths 
  of a full circle).   
  
  @param 
  
  @returns
*/ 
int servo360_angle(int pin, int position);


/**
  @brief 
  
  @param 
  
  @returns
*/ int servo360_getAngle(int pin);



/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_speed(int pin, int speed);


/**
  @brief 
  
  @param 
  
  @returns
*/ int servo360_getSpeed(int pin);


/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_goto(int pin, int position);


/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_getCsop(int pin);



/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_stop(int pin);



/**
  @name Settings - Speed Control
  @{ 
*/



/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_setAcceleration(int pin, int unitsPerSecSquared);


/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_getAcceleration(int pin);



/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_setMaxSpeed(int pin, int speed);


/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_getMaxSpeed(int pin);



/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_setRampStep(int pin, int stepSize);


/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_getRampStep(int pin);



/**
  @}
 
  @name Settings - Angle Control
  @{ 
*/





/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_setAngleLimits(int pin, int ccwMax, int cwMax);


/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_getAngleLimits(int pin, int *ccwMax, int *cwMax);



/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_setAngleCtrlSpeedMax(int pin, int speed);


/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_getAngleCtrlSpeedMax(int pin);



/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_setAngleOffset(int pin, int angle);


/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_getAngleOffset(int pin);



/**
  @}
 
  @name Settings - General
  @{ 
*/





/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_setUnitsFullCircle(int pin, int units);


/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_getUnitsFullCircle(int pin);



/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_setControlSys(int pin, int constant, int value);


/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_getControlSys(int pin, int constant);



/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_setTurns(int pin, int turns);


/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_getTurns(int pin);



/**
  @}
 
  @name Settings - Differential Drive
  @{ 
*/





/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_couple(int pinA, int pinB);


/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_setCoupleScale(int pinA, int pinB, int scale);



/**
  @}
 
  @name Settings - Advanced
  @{ 
*/





/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_enable(int pin, int state);


/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_feedback(int pin, int state);


/**
  @brief 
  
  @param 
  
  @returns
*/ 
int servo360_set(int pinControl, int time);



/**
  @}
*/



#ifndef DOXYGEN_SHOULD_SKIP_THIS



/* Private */
void servo360_run(void);
void servo360_end();
void servo360_setup(void);
void servo360_mainLoop();
void servo360_outputSelector(int p);

void servo360_servoPulse(int p, int q);
void servo360_waitServoCtrllEdgeNeg(int p);
int servo360_dutyCycle(int p, int scale);
int servo360_crossing(int current, int previous, int units);
int servo360_getTheta(int p);
void servo360_checkAngle(int p);
void servo360_captureOffset(int p);
void servo360_setPositiveDirection(int p, int direction);

int servo360_setRampStep(int p, int stepSize);

int servo360_upsToPulseFromTransferFunction(int unitsPerSec, int p);
void servo360_pulseControl(int p, int speedUps);

void servo360_speedControl(int p);
int servo360_pidA(int p);
int servo360_pidV(int p);  

int servo360_findServoIndex(int pin);

int servo360_unitsAngleToEncoder(int value, int unitsRev);
int servo360_unitsEncoderToAngle(int value, int unitsRev); 
int servo360_checkDistanceRemaining(int pin, int speed, int finalAngle);

int servo360_setMaxSpeedEncoded(int pin, int speed);

void servo360_monitorRun(void);
void servo360_monitorEnd(void);

int servo360_setTransferFunction(int pin, int constant, int value);


int servo360_getAngle12Bit(int pin);
int servo360_getAngleFixedOrigin(int pin);
int servo360_getAngleCalc(int pin);

/*
__attribute__((constructor))
void servo360_patch(void);
*/

#ifdef _servo360_monitor_
void console();
void servo360_monitor_start(void);
void servo360_monitor_stop();
int terminal_checkForValue(fdserial *connection, int *value);
#endif



#endif // DOXYGEN_SHOULD_SKIP_THIS



#if defined(__cplusplus)
}
#endif
/* __cplusplus */ 
#endif
/* SERVO360_H */ 


/**
 * TERMS OF USE: MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

                                                                                //
