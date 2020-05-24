#include "robotClass.hpp"
#include "robot/devices/motorClass.hpp"
#include "robot/graphical/components/alertClass.hpp"
#include "robot/subsystems/baseComponents/holonomicClass.hpp"

Robot::Robot():
  m_gui("Odometry"),
  m_mainController(pros::E_CONTROLLER_MASTER),
  m_partnerController(pros::E_CONTROLLER_PARTNER),
  m_timer(),
  m_config("Robot_Config.txt"),
  m_base(*this, 200),
  m_taskScheduler(*this, "MainTaskScheduler")
  {
    m_partnerController.Axis2.setMultiplier(2);
    m_partnerController.Axis3.setMultiplier(2);

    defineGUI();
}

int Robot::task(){
  m_taskScheduler.task();
  m_gui.task();
  m_mainController.callBackCheck();
  m_partnerController.callBackCheck();

  m_base.task();

  if(m_robotMode == ROBOT_AUTO)
    m_robotModeString = "Autonomous";
  else if(m_robotMode == ROBOT_OPERATER)
    m_robotModeString = "Driver";
  else if(m_robotMode == ROBOT_DISABLED)
    m_robotModeString = "Disabled";
  return 0;
}

GraphicalInterface& Robot::getGUI(){
  return m_gui;
}

TaskScheduler& Robot::getTaskScheduler(){
  return m_taskScheduler;
}

int Robot::autonmous(){
  m_robotMode = ROBOT_AUTO;
  switch(m_programNumber) {
    case AUTO_RED:
      autoRed();
      break;

    case AUTO_BLUE:
      autoBlue();
      break;

    case AUTO_SKILLS:
      autoSkills();
      break;

    case AUTO_DEFAULT:
      autoDefault();
      break;

    case AUTO_NONE:
      break;
  }
  return 0;
}

int Robot::driverControl(){
  m_robotMode = ROBOT_OPERATER;
  m_base.driverControl();
  return 0;
}

int Robot::disabled(){
  m_robotMode = ROBOT_DISABLED;
  return 0;
}

RobotMode Robot::getRobotMode(){
  return m_robotMode;
}
