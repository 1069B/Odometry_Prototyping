#include "tasks.hpp"
#include "robotClass.hpp"
#include "robot/graphical/components/alertClass.hpp"
#include "robot/devices/motorClass.hpp"

Robot robot;

void initialize(){
  pros::delay(5);
}

void disabled() {
  robot.disabled();
  while(true){
    robot.task();
    pros::delay(2);
  }
}

void competition_initialize() {
  robot.disabled();
  while(true){
    robot.task();
    pros::delay(2);
  }
}

void autonomous() {
  robot.m_autonTimer.resetTime();
  robot.resetOrientation();
  Motor::findMotor("FrontLeftMotor")->resetRotation();
  Motor::findMotor("FrontRightMotor")->resetRotation();
  Motor::findMotor("BackLeftMotor")->resetRotation();
  Motor::findMotor("BackRightMotor")->resetRotation();
  while(true){
    robot.task();
    robot.autonmous();
    pros::delay(2);
  }
}

void opcontrol(){
  pros::delay(5);
  while(true){
    robot.task();
    robot.driverControl();
    pros::delay(2);
  }
}
