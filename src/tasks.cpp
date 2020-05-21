#include "tasks.hpp"
#include "robotClass.hpp"
#include "robot/graphical/components/alertClass.hpp"

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
  robot.autonmous();
  while(true){
    robot.task();
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
