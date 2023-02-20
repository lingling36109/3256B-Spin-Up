#include "main.h"

/**************************************************/
//motor + sensors declaration
pros::Motor shooterU (SHOOTERU, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);
pros::Motor shooterL (SHOOTERL, MOTOR_GEARSET_6, true, MOTOR_ENCODER_DEGREES);
pros::Motor_Group shooterGroup ({shooterU, shooterL});
pros::Motor puncher (PUNCHER, MOTOR_GEARSET_36, true, MOTOR_ENCODER_DEGREES);

pros::ADIDigitalOut limit (LIMIT);
/**************************************************/
//functions
void punching() {
    
}

double motorPower = 0.0; 
double lastError = 0.0; 
double tbh = 0.0; 
float FlywheelTarget = 0.0001; 

double gain = 0.05; 

double flywheelTBH(double target){
    double error = target - (0.5*(shooterU.get_actual_velocity()+shooterL.get_actual_velocity()));
    motorPower += gain * error;
    motorPower = motorPower/fabs(motorPower) * ((fabs(motorPower) > 127)? 127: motorPower);

    if ((lastError > 0) != (error>0)) {
        motorPower = 0.5 * (motorPower + tbh);
        tbh = motorPower;
        lastError = error;
    }
    return motorPower;
}

void velocitySet(double newRpm) {
    if(FlywheelTarget < newRpm) {
        lastError = 1;
    } else if(FlywheelTarget > newRpm) {
        lastError = -1;
    }
    tbh = (2 * (newRpm / 200)) - 1;
    FlywheelTarget = newRpm;
}

void flywheelControl(){
    if (master.get_digital(DIGITAL_A)) {
		velocitySet(230);
	}
	if (master.get_digital(DIGITAL_B)) {
		velocitySet(100);
	}
	if (master.get_digital(DIGITAL_X)) {
		velocitySet(50);
	}
	if (master.get_digital(DIGITAL_Y)) {
		velocitySet(0);
	}
	shooterGroup.move(flywheelTBH(FlywheelTarget));
}

void firingDisc(double vel) {
    int discs = diskCounter();
    velocitySet(vel);
    while(discs != 0){
        shooterGroup.move(flywheelTBH(FlywheelTarget));
        if(fabs(vel-(0.5*(shooterU.get_actual_velocity()+shooterL.get_actual_velocity()))) < 5){
            punching();
            discs--;
        }
        pros::delay(10);
    }
}