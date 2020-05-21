#include "robot/varibleDecleration.hpp"
#include "robot/devices/externalFileClass.hpp"

#ifndef BASECLASSV2_H
#define BASECLASSV2_H

class Base{
public:
  /*Basic Varibles*/
  std::string m_name = "Base";
  Robot &m_robot;

  BaseState m_baseState = BASE_STATIONARY;
  std::string m_baseStateString = "Stationary";

  int m_maximumVelocity = 200;
  /*Brake Varibles*/
  pros::motor_brake_mode_e m_brakeMode = pros::E_MOTOR_BRAKE_COAST;
  std::string m_brakeString = "Coast";

  /*Robot Motion*/
  double m_motionTranslationVelocity = 0;
  double m_motionTranslationAngle = 0;// Relative to Robot NOT FIELD
  double m_motionOrientationVelocity = 0;


  /*Varibles for Automation*/
  Odometry &m_odometry;

  bool m_movementInProgress = false;
  double m_movementSpeedUpPercent = 0;
  double m_movementSpeedDownPercent = 0;
  double m_movementIntialTranslationVelocity = 0;
  double m_movementIntialOrientationVelocity = 0;
  double m_movementMaximumVelocity = 0;

  double m_intialOrientaion = 0;
  double m_finalOrientation = 0;

  double m_intialXPosition = 0;
  double m_finalXPosition = 0;

  double m_intialYPosition = 0;
  double m_finalYPosition = 0;

  ExternalFile m_config;

  Base(Robot &p_robot, const int p_maximumVelocity);

  int setMaximumVelocity(const int p_maximumVelocity);

  double setBrakeMode(const pros::motor_brake_mode_e p_brakeMode);

  int driverControl();

  int goToPosition(const double p_xPosition, const double p_yPosition, const double p_speedUpPercent, const double p_speedDownPercent, const int p_intialVelocity, const int p_maximumVelocity);

  int goToOrientation(const double p_orientation, const double p_speedUpPercent, const double p_speedDownPercent, const int p_intialVelocity, const int p_maximumVelocity);

  int goToVector(const double p_translationalVelocity, const double p_translationalAngle, const double p_angularVelocity);

  int superTask();
};

#endif // BASECLASSV2_H
