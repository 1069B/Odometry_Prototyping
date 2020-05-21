#include "robot/subsystems/baseComponents/baseClass.hpp"
#include "robot/subsystems/odometryClass.hpp"

Base::Base(Robot &p_robot, const int p_maximumVelocity):
m_robot(p_robot),
m_odometry(*(new Odometry(p_robot, "LeftTrackingWheel", "RightTrackingWheel", "CenterTrackingWheel"))),
m_config("base_config.txt"){
  m_maximumVelocity = p_maximumVelocity;
  m_odometry.defineGUI("Subsystems");
}

int Base::setMaximumVelocity(const int p_maximumVelocity){
  m_maximumVelocity = p_maximumVelocity;
  return 0;
}

double Base::setBrakeMode(const pros::motor_brake_mode_e p_brakeMode){
  m_brakeMode = p_brakeMode;
  return 0;
}

int Base::driverControl(){
  m_baseState = BASE_DRIVER_DEPENDENT;
  return 0;
}

int Base::goToPosition(const double p_xPosition, const double p_yPosition, const double p_speedUpPercent, const double p_speedDownPercent, const int p_intialVelocity, const int p_maximumVelocity){
  m_movementInProgress = true;
  m_finalXPosition = p_xPosition;
  m_finalXPosition = p_yPosition;

  m_movementSpeedUpPercent = p_speedUpPercent;
  m_movementSpeedDownPercent = p_speedDownPercent;
  m_movementIntialTranslationVelocity = p_intialVelocity;
  m_movementMaximumVelocity = p_maximumVelocity;
  return 0;
}

int Base::goToOrientation(const double p_orientation, const double p_speedUpPercent, const double p_speedDownPercent, const int p_intialVelocity, const int p_maximumVelocity){
  m_movementInProgress = true;
  m_finalOrientation = p_orientation;
  m_movementSpeedUpPercent = p_speedUpPercent;
  m_movementSpeedDownPercent = p_speedDownPercent;
  m_movementIntialOrientationVelocity = p_intialVelocity;
  m_movementMaximumVelocity = p_maximumVelocity;
  return 0;
}

int Base::goToVector(const double p_translationalVelocity, const double p_translationalAngle, const double p_angularVelocity){
  m_motionTranslationVelocity = p_translationalVelocity;
  m_motionTranslationAngle = p_translationalAngle;// Relative to Robot NOT FIELD
  m_motionOrientationVelocity = p_angularVelocity;
  m_baseState = BASE_VECTOR_DEPENDENT;
  return 0;
}

int Base::superTask(){
  m_odometry.task();

  switch ((int)m_baseState) {
    case BASE_STATIONARY:
      m_baseStateString = "Stationary";
      break;

    case BASE_DRIVER_DEPENDENT:
      m_baseStateString = "Driver";
      break;

    case BASE_ODOMETRY_DEPENDENT:
      m_baseStateString = "Odometry";
      break;
  }

  switch ((int)m_brakeMode) {
    case pros::E_MOTOR_BRAKE_COAST:
      m_brakeString = "Coast";
      break;
    case pros::E_MOTOR_BRAKE_BRAKE:
      m_brakeString = "Brake";
      break;
    case pros::E_MOTOR_BRAKE_HOLD:
      m_brakeString = "Hold";
      break;
  }
  return 0;
}
