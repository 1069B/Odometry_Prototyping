#include "robot/varibleDecleration.hpp"
#include "robot/devices/timerClass.hpp"
#include "robot/devices/externalFileClass.hpp"
#include "robot/devices/controller/controllerClass.hpp"
#include "robot/devices/taskScheduleClass.hpp"
#include "robot/graphical/GUIClass.hpp"
#include "robot/subsystems/armClass.hpp"
#include "robot/subsystems/intakeClass.hpp"
#include "robot/subsystems/baseComponents/baseClass.hpp"
#include "robot/subsystems/baseComponents/holonomicClass.hpp"

#ifndef ROBOTCLASS_H
#define ROBOTCLASS_H

class Robot{
private:
  GraphicalInterface m_gui;

  Timer m_timer;
  ExternalFile m_config;
  TaskScheduler m_taskScheduler;

  Holonomic m_base;

  RobotMode m_robotMode;
  std::string m_robotModeString = "Disabled";

  int defineGUI();
  friend class Base;
  friend class Odometry;

  int m_programNumber = AUTO_DEFAULT;
public:
  Controller m_mainController;
  Controller m_partnerController;

  Robot();

  int task();

  GraphicalInterface& getGUI();

  int driverControl();

  int autonmous();

  int disabled();

  TaskScheduler& getTaskScheduler();

  RobotMode getRobotMode();

  int autoRed();
  int autoBlue();
  int autoSkills();
  int autoDefault();

  int baseStop();
  int baseTo(double speed, double orientation, double turning, int duration);
};

#endif // ROBOTCLASS_H
