#include "robot/varibleDecleration.hpp"
#include "timerClass.hpp"

#ifndef ENCODERCLASS_H
#define ENCODERCLASS_H

class Encoder{
private:
  std::string m_name = "Encoder";
  Robot& m_robot;
  short m_port;// 1,3,5,7
  SubTimer m_timer;

  int m_rotation = 0;
  double m_displacement = 0;
  double m_previousDisplacement = 0;

  int m_zeroPosition = 0;

  double m_calculatedDisplacement = 0;

  double m_velocity = 0;
  double m_timerChange = 0;

  int m_direction = 0;
  bool m_reversed = false;

  std::vector<double> m_avgVelocity;

  static ExternalFile s_config;
  static std::vector<Encoder*> s_encoderArray;

  static ExternalFile s_debug;

public:
  Encoder(Robot& p_robot, const std::string p_name, const int p_port, const bool p_reverse);

  int isConnected();// Still need a methoud for detecting connection

  int getRotation();

  int getDisplacment();

  int getCalculatedDisplacement();

  std::string getName();

  int resetRotation();

  double getVelocity();

  int getDirection();

  int setPort(const int p_port);

  int setReverse(const bool p_reverse);

  int defineGUI(GraphicalInterface& p_gui, const std::string p_returnScreen);

  int task();

  static Encoder* findEncoder(const std::string p_name);

  static Encoder* findEncoder(const short p_port);
};

#endif // ENCODERCLASS_H
