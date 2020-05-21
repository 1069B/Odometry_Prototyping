#include "robot/varibleDecleration.hpp"
#include "robot/devices/timerClass.hpp"
#include "robot/devices/externalFileClass.hpp"

#ifndef ODOMETRYCLASS_H
#define ODOMETRYCLASS_H

class Odometry{
private:
  std::string m_name = "Odometry";
  Robot& m_robot;

  Encoder* m_leftEncoder = NULL;
  Encoder* m_centerEncoder = NULL;
  Encoder* m_rightEncoder = NULL;

  double m_orientation = 0;
  double m_xPosition = 0;
  double m_yPosition = 0;
  double m_xVelocity = 0;
  double m_yVelocity = 0;

	double m_radiusLeft = 0;
	double m_radiusRight = 0;
	double m_radiusAvg = 0;

	double m_orientationVelocity = 0;
	double m_velocityLeft = 0;
	double m_velocityRight = 0;
	double m_velocityAvg = 0;

  double m_timeChange = 0;

  double m_test = 0;
	double m_currentOrientationTime = 0;
	double m_previousOrientationTime = 0;

	double m_currentOrientationVelocityTime = 0;
	double m_previousOrientationVelocityTime = 0;

	double m_currentOrientation = 0;
	double m_previousOrientation = 0;

	Timer m_timer;

  std::string m_turnType;
	double m_trakingDistanceTotal = 26.355;//Units in cm
	double m_trackingDistanceLeft = 13.496;//Units in cm
	double m_trackingDistanceRight = 12.859;//Units in cm

  double orientationConverter(const double p_angle);

  int calculateDirection(const int p_value);
  int calculateDirection(const double p_value);

  int calculatePosition();
  int calculateOrientation();

  ExternalFile m_translationDebug;
  ExternalFile m_OrientationDebug;

public:
  Odometry(Robot& p_robot, const std::string p_leftEncoder, const std::string p_rightEncoder, const std::string p_centerEncoder);

  double getOrientation();

  double getOrientationVelocity();

  double getRadiusLeft(const double p_leftVelocity, const double p_rightVelocity);

  double getRadiusRight(const double p_leftVelocity, const double p_rightVelocity);

  double setOrientation(const double p_orientation);

  double getXposition();

  double getXVelocity();

  double setXposition(const double p_xPosition);

  double getYposistion();

  double getYVelocity();

  double setYposition(const double p_yPosition);

  int defineGUI(const std::string p_returnScreen);

  int task();
};
#endif // ODOMETRYCLASS_H
