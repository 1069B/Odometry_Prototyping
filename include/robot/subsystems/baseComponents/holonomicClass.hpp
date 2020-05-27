#include "robot/varibleDecleration.hpp"
#include "robot/devices/externalFileClass.hpp"
#include "baseClass.hpp"

#ifndef HOLONOMICCLASS_H
#define HOLONOMICCLASS_H

class Holonomic: public Base{
private:
  Motor& m_frontLeftMotor;
  Motor& m_frontRightMotor;
  Motor& m_backLeftMotor;
  Motor& m_backRightMotor;

  double m_desiredFrontLeftVelocity = 0;
  double m_desiredFrontRightVelocity = 0;
  double m_desiredBackLeftVelocity = 0;
  double m_desiredBackRightVelocity = 0;

  bool m_speedUpCurve = true;
	bool m_driftTurning = true;

  int m_speedUpCoeffiecientA = 201;
	int m_speedUpCoeffiecientB = 5;
	double m_speedUpCoeffiecientC = 0.05;
	int m_speedUpCoeffiecientH = -27;

  double speedUp(int p_controllerValue);

public:
  Holonomic(Robot &p_robot, const int p_maximumVelocity);

  int task();

  int defineGUI(const std::string p_returnScreen);

  int autonomous();

  int setBrakeMode(pros::motor_brake_mode_e_t p_brakeMode);
};

#endif // HOLONOMICCLASS_H
