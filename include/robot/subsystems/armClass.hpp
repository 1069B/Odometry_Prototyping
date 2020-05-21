#include "robot/varibleDecleration.hpp"
#include "robot/devices/timerClass.hpp"

class Robot;

#ifndef ARMCLASSV2_H
#define ARMCLASSV2_H

struct ArmPreset{
public:
  int m_position = 0;
  double m_speedUpPercent = 0;
  double m_speedDownPercent = 0;
  int m_maximumVelocity = 0;
  int m_initialVelocity = 5;
};

class Arm {
private:
  Robot& m_robot;
  Motor* m_armMotor;
  std::string m_name = "Arm";

  int m_startPosition = 0;
  int m_currentPosition = 0;
  int m_endPosition = 0;

  int m_movementDisplacement = 0;
  int m_movementDirection = 0;
  int m_movementMaximumVelocity = 0;
  int m_movementIntialVelocity = 0;
  bool m_movementInProgess = false;
  std::string m_movementString = "User Based";

  int m_limitLow = 0;
  int m_limitHigh = 0;
  int m_totalPossibleDisplacement = 0;

  int m_desiredVelcoity = 0;
  int m_velcoityMaximum = 200;
  double m_velocityMaximumCoefficent = 1;

  double m_speedUpPercent = .25;
  double m_speedUpSlope=0;
  double m_speedUpDisplacement = 0;

  double m_speedDownPercent = .25;
  double m_speedDownSlope = 0;
  double m_speedDownDisplacement = 0;

  ArmPreset m_presetHigh;
  ArmPreset m_presetLow;
  ArmPreset m_preset1;
  ArmPreset m_preset2;
  ArmPreset m_preset3;
  ArmPreset m_preset4;

  pros::motor_brake_mode_e m_brakeMode = pros::E_MOTOR_BRAKE_HOLD;
  std::string m_brakeString = "Coast";

  bool m_reversed;
  ManipulatorMode m_mode = MANIPULATOR_DISABLED;
  std::string m_modeString = "Coast";


public:
  Arm(Robot& p_robot, const std::string p_name);

  /* Setting Functions */
  int initialize(const std::string p_armMotor, const int p_port, const int p_limitLow, const int p_limitHigh, const bool p_reversed = false);

  int setLimitLowPreset(const double p_speedUpPercent, const double p_speedDownPercent, const int p_intialVelocity, const int p_maximumVelocity);

  int setLimitHighPreset(const double p_speedUpPercent, const double p_speedDownPercent, const int p_intialVelocity, const int p_maximumVelocity);

  int setPreset1(const int p_position, const double p_speedUpPercent, const double p_speedDownPercent, const int p_intialVelocity, const int p_maximumVelocity);

  int setPreset2(const int p_position, const double p_speedUpPercent, const double p_speedDownPercent, const int p_intialVelocity, const int p_maximumVelocity);

  int setPreset3(const int p_position, const double p_speedUpPercent, const double p_speedDownPercent, const int p_intialVelocity, const int p_maximumVelocity);

  int setPreset4(const int p_position, const double p_speedUpPercent, const double p_speedDownPercent, const int p_intialVelocity, const int p_maximumVelocity);

  int setVelocityMaximumCoefficent(const int p_coefficeint);

  int setBrake(const pros::motor_brake_mode_e p_brakeMode);

  int setMaximumVelcoity(const int p_velocityMax);

  /* GO TO FUNCTION */
  int goToVelocity(const int p_velocity);//Mode 0

  int goToPosition(const int p_position, const double p_speedUpPercent, const double p_speedDownPercent, const int p_intialVelocity, const int p_maximumVelocity);// Mode 1

  int goToLimitLow();

  int goToLimitHigh();

  int goToPreset1();

  int goToPreset2();

  int goToPreset3();

  int goToPreset4();

  /* Main Tasks */

  int task();

  int defineGUI(const std::string p_returnScreen);
};

#endif // ARMCLASSV2_H
