#include "robotClass.hpp"
#include "robot/devices/motorClass.hpp"
#include "robot/graphical/components/alertClass.hpp"
#include "robot/subsystems/baseComponents/holonomicClass.hpp"

int Robot::baseStop(){
  return 0;
}

int Robot::baseTo(double speed, double orientation, double turning, int duration){
  return 0;
}

int Robot::autoDefault(){
  m_base.goToVector(0,0,150);
  m_timer.addActionDelay(4075);
  while(!m_timer.preformAction()){
    robot.task();
    pros::delay(3);
  }
  m_base.goToVector(0,0,0);
  return 0;
}

int Robot::autoRed(){
  return 0;
}

int Robot::autoBlue(){
  return 0;
}

int Robot::autoSkills(){
  return 0;
}
