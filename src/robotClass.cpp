#include "robotClass.hpp"
#include "robot/devices/motorClass.hpp"
#include "robot/graphical/components/alertClass.hpp"
#include "robot/subsystems/baseComponents/holonomicClass.hpp"

Robot::Robot():
  m_gui("Home"),
  m_mainController(pros::E_CONTROLLER_MASTER),
  m_partnerController(pros::E_CONTROLLER_PARTNER),
  m_timer(),
  m_config("Robot_Config.txt"),
  m_base(*this, 200),
  m_tray(*this, "Tray"),
  m_slider(*this, "Slider"),
  m_leftIntake(*this, "Left_Intake"),
  m_rightIntake(*this, "Right_Intake"),
  m_taskScheduler(*this, "MainTaskScheduler")
  {
    // if(m_config.varExist("Comp_Mode"))
    //   m_robotMode = m_config.readString("Comp_Mode");
    // else
    //   m_robotMode = "DriverControl";

    m_tray.initialize("TrayMotor", 5, 0, 675, false);
    m_slider.initialize("SliderMotor", 8, -25, 680, true);
    m_leftIntake.initialize("Left_Intake_Motor", 18, false);
    m_rightIntake.initialize("Right_Intake_Motor", 9, true);

    m_partnerController.Axis2.setMultiplier(2);
    m_partnerController.Axis3.setMultiplier(2);

    m_tray.setLimitHighPreset(.25, .75, 20, 35);
    m_tray.setPreset1(650, .20, .80, 20, 35);
    m_tray.setLimitLowPreset(.25, .25, 20, 35);

    m_slider.setLimitHighPreset(.25, .25, 25, 75);
    m_slider.setPreset1(400, .25, .25, 25, 75);// High Pick Uo
    m_slider.setPreset2(600, .25, .25, 25, 75);// Low Pickup
    m_slider.setPreset3(100, .25, .25, 25, 40);//Scoreing
    m_slider.setLimitLowPreset(.25, .25, 25, 75);

    defineGUI();
}

int Robot::task(){
  m_taskScheduler.task();
  m_gui.task();
  m_mainController.callBackCheck();
  m_partnerController.callBackCheck();

  m_tray.task();
  m_slider.task();
  m_base.task();
  m_leftIntake.task();
  m_rightIntake.task();

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
  //g_alert.draw("Left Intake Speed: " + std::to_string(m_partnerController.Axis3.getValue()));
  m_leftIntake.goToVelocity(-m_partnerController.Axis3.getValue());
  m_rightIntake.goToVelocity(m_partnerController.Axis2.getValue());

  if(m_partnerController.ButtonL1.state() == true)
    m_tray.goToVelocity(30);
  else if(m_partnerController.ButtonL2.state() == true)
    m_tray.goToVelocity(-30);
  else
    m_tray.goToVelocity(0);

  if(m_partnerController.ButtonUp.state() == true){
    m_tray.goToLimitHigh();
    m_slider.goToLimitLow();
  }
  else if(m_partnerController.ButtonDown.state() == true){
    m_tray.goToLimitLow();
    m_slider.goToLimitLow();
  }



  if(m_partnerController.ButtonR1.state() == true)
    m_slider.goToVelocity(-75);
  else if(m_partnerController.ButtonR2.state() == true)
    m_slider.goToVelocity(75);
  else
    m_slider.goToVelocity(0);

  if(m_partnerController.ButtonX.state() == true){
    m_slider.goToLimitLow();
  }
  else if(m_partnerController.ButtonA.state() == true){
    m_slider.goToPreset1();
  }
  else if(m_partnerController.ButtonY.state() == true){
    m_slider.goToPreset2();
  }
  else if(m_partnerController.ButtonB.state() == true){
    m_slider.goToLimitLow();
  }

  m_base.driverControl();
  return 0;
}

int Robot::disabled(){
  m_robotMode = ROBOT_DISABLED;
  //m_base.disabled();
  // m_leftIntake.disabled();
  // m_rightIntake.disabled();
  m_tray.goToVelocity(0);
  m_tray.setBrake(MOTOR_BRAKE_COAST);
  m_slider.goToVelocity(0);
  m_slider.setBrake(MOTOR_BRAKE_COAST);
  return 0;
}

RobotMode Robot::getRobotMode(){
  return m_robotMode;
}
