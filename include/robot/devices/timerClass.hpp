#include "robot/varibleDecleration.hpp"

#ifndef TIMERCLASS_H
#define TIMERCLASS_H

  class Timer{
  private:
    int m_startTime;
    int m_currentTime;
    std::vector<int> m_previousLapTime;
    std::vector<int> m_nextFlag;

  public:
    Timer(const bool p_mode = false);

    int resetTime();

    int getTime();

    int lapTime(const int p_lapVersion = 0);

    bool preformAction(const int p_actionVersion = 0);

    int addActionDelay(const int p_delay, const int p_actionVersion = 0);

    int defineGUI(GraphicalInterface& p_gui, std::string p_returnScreen);
  };
#endif // TIMERCLASS_H
