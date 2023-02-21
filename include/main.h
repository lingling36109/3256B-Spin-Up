#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

#define PROS_USE_SIMPLE_NAMES

#define PROS_USE_LITERALS

#include "api.h"
#include "sylib/sylib.hpp"
//include other header files with function definitions
#include "intake.hpp"
#include "shooter.hpp"
#include "drive.hpp"

//sylib filters
extern sylib::MedianFilter colorFilter;
extern sylib::MedianFilter distanceFilter;

//ports definitions
#define MOTORFL 1
#define MOTORFR 2 
#define MOTORBL 3 
#define MOTORBR 4
#define INTAKE 5
#define PUNCHER 6
#define SHOOTERU 7
#define SHOOTERL 8

#define END 1
#define LIMIT 2
#define XENCODER 3
#define YENCODER 4

#define INDEXER 9
#define FRONTDIST 10 
#define BACKDIST 11
#define RIGHTDIST 12
#define LEFTDIST 13
#define ROLLER 14
#define IMUSENSOR 15 

//extern motor + sensor declaration
extern pros::Controller master;

extern pros::Motor motorFL;
extern pros::Motor motorFR;
extern pros::Motor motorBL;
extern pros::Motor motorBR;
extern pros::Motor intake;
extern pros::Motor puncher;
extern pros::Motor shooterU;
extern pros::Motor shooterL;

extern pros::ADIDigitalOut endgame;
extern pros::ADIDigitalOut limit;

extern pros::Distance indexer;
extern pros::Distance frontDist;
extern pros::Distance backDist;
extern pros::Distance rightDist;
extern pros::Distance leftDist;
extern pros::Optical roller;
extern pros::Rotation xEncoder;
extern pros::Rotation yEncoder;
extern pros::IMU imu;

#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
//#include <iostream>
#endif

#endif  // _PROS_MAIN_H_
