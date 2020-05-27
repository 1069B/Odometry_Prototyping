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
  int l_FLM_Postion = -Motor::findMotor("FrontLeftMotor")->getRotation();
  int l_FRM_Postion = Motor::findMotor("FrontRightMotor")->getRotation();
  int l_BLM_Postion = -Motor::findMotor("BackLeftMotor")->getRotation();
  int l_BRM_Postion = Motor::findMotor("BackRightMotor")->getRotation();

  int l_average = (l_FLM_Postion + l_FRM_Postion + l_BLM_Postion + l_BRM_Postion)/4.0;

  if(m_autonTimer.getTime() < 2000){
    m_base.goToVector(0,0,0);
  }
  else{
    if(l_average < 9465){
      m_base.setBrakeMode(MOTOR_BRAKE_COAST);
      m_base.goToVector(0,0,150);
    }
    else{
      m_base.setBrakeMode(MOTOR_BRAKE_BRAKE);
      m_base.goToVector(0,0,0);
    }
  }
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
