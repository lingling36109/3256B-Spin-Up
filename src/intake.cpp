#include "main.h"

/**************************************************/
//motor + sensors declaration
pros::Motor intake (INTAKE, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Optical roller (ROLLER);
pros::Distance indexer (INDEXER);

/**************************************************/
//functions
void intakefwd(){
  intake.move_velocity(200);
}

void intakerev(){
  intake.move_velocity(-200);
}

void intakestop(){
	intake.move_velocity(0);
}

bool moveF = false;
bool moveB = false;
void intakeDControl(){
	if(!moveB && ((master.get_digital_new_press(DIGITAL_L1)) || (master.get_digital_new_press(DIGITAL_L2) && moveF))){
		moveF = !moveF; 
	} else if(!moveF && ((master.get_digital_new_press(DIGITAL_L2)) || (master.get_digital_new_press(DIGITAL_L1) && moveB))){
		moveB = !moveB;
	}

	if(moveF){
		intakefwd();
	} else if(moveB){
		intakerev();
	} else{
		intakestop();
	}
}

int rollerColor() {
	if (roller.get_proximity() < 200) {
		return 0;
	}
	double hue = colorFilter.filter(roller.get_hue());
	if (hue < 260 && hue > 230) {
		return 1; //blue
	} else if (hue < 30 && hue > 0) {
		return 2; //red
	} else {
		return 3; //neither
	}
}

void rollerRed() {
    if(rollerColor() == 0){
        return;
    }
	int rollerStartTime = sylib::millis();
	intake.move_velocity(200);
	while (rollerColor() != 2 && sylib::millis() - rollerStartTime < 1500) {
		sylib::delay(10);
	}
	intake.move_velocity(0);
}

void rollerBlue() {
    if(rollerColor() == 0){
        return;
    }
	int rollerStartTime = sylib::millis();
	intake.move_velocity(200);
	while (rollerColor() != 1 && sylib::millis() - rollerStartTime < 1500) {
		sylib::delay(10);
	}
	intake.move_velocity(0);
}

int diskCounter() {
	int sensorDistance = distanceFilter.filter(indexer.get());
	if (sensorDistance > 105) {
		return 0;
	} else if (sensorDistance > 90) {
		return 1;
	} else if (sensorDistance > 70) {
		return 2;
	} else {
		return 3;
	}
}