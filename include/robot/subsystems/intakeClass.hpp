#include "robot/varibleDecleration.hpp"
#include "robot/devices/timerClass.hpp"
#include "robot/devices/externalFileClass.hpp"

#ifndef INTAKECLASSV2_H
#define INTAKECLASSV2_H

struct IntakePreset{
public:
  int m_position = 0;
  double m_speedUpPercent = 0;
  double m_speedDownPercent = 0;
  int m_maximumVelocity = 0;
  int m_initialVelocity = 5;
  int m_duration = 0;
  ManipulatorMode m_mode = MANIPULATOR_DISABLED;
};

class Intake{
private:
  Robot& m_robot;
  Motor* m_intakeMotor = NULL;
  std::string m_name = "Intake";

  int m_startPosition = 0;
  int m_currentPosition = 0;
  int m_endPosition = 0;

  int m_desiredVelocity = 0;
  Direction m_desiredDirection = DIRECTION_STATIONARY;
  std::string m_desiredDirectionString = "STATIONARY";
  int m_maximumVelocity = 100;

  int m_movementDisplacement = 0;
  int m_movementVelocity = 0;
  int m_movementDuration = 0;
  Direction m_movementDirection = DIRECTION_STATIONARY;
  bool m_movementInProgess = false;
  std::string m_movementString = "User Based";

  pros::motor_brake_mode_e m_brakeMode = pros::E_MOTOR_BRAKE_HOLD;
  std::string m_brakeString = "Coast";
  ManipulatorMode m_mode = MANIPULATOR_DISABLED;
  std::string m_modeString = "Disabled";

  SubTimer m_timer;

public:
  Intake(Robot& p_robot, const std::string p_name);

  /*Setter Functions*/
  int initialize(const std::string p_intakeMotor, const int p_port, const int p_maximumVelcouty, const bool p_reversed = false);

  int setBrakeMode(const pros::motor_brake_mode_e p_brakeMode);

  /*Action Functions*/
  int goToVelocity(const int p_velocity);//Implied Direction Through Sign of Velocity
  int goToVelocity(const int p_velocity, const Direction p_direction);//Defined Direction ~ Velocity is taken as the amsolute.

  int goToDuration(const int p_duration, const int p_velocity, const Direction p_direction);

  int goToPosition(const int p_position, const int p_velocity, const Direction p_direction);// Mode 1

  int toggleForward();
  int toggleBackward();
  /* Main Tasks */
  int task();

  int defineGUI(const std::string p_returnScreen);
};

#endif // INTAKECLASSV2_H
