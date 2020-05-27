#include "robot/varibleDecleration.hpp"

#ifndef TIMERCLASS_H
#define TIMERCLASS_H

class SubTimer{
private:
  std::string m_name;

  int m_startTime;
  int m_currentTime;
  int m_previousLapTime;
  int m_nextFlag;

public:
  SubTimer(const std::string p_name, const bool p_mode = false);

  int resetTime();

  int getTime();

  int lapTime();

  bool preformAction();

  int addActionDelay(const int p_delay);

  int subGUI(GraphicalInterface& p_gui, std::string p_returnScreen);

  std::string getName();
};

class Timer{
  private:
    Robot &m_robot;
    static std::vector<SubTimer*> m_timeArray;

    static int addSubTimer(SubTimer& p_subTimer);

    friend class SubTimer;
  public:
    Timer(Robot &p_robot);

    int defineGUI(std::string p_returnScreen);
  };
#endif // TIMERCLASS_H
