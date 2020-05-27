#include "robotClass.hpp"
#include "robot/devices/externalFileClass.hpp"

SubTimer::SubTimer(const std::string p_name, const bool p_mode){
  m_name = p_name;
  Timer::addSubTimer(*this);
  if(p_mode){
    m_startTime = pros::millis();
    m_nextFlag = pros::millis();
    m_previousLapTime = pros::millis();
  }
  else{
    m_startTime = 0;
    m_nextFlag = 0;
    m_previousLapTime = 0;
  }
}

int SubTimer::resetTime(){
  m_startTime = pros::millis();
  m_previousLapTime = pros::millis();
  m_nextFlag = pros::millis();
  return 0;
}

int SubTimer::getTime(){
  m_currentTime = pros::millis() - m_startTime;
  return m_currentTime;
}

int SubTimer::lapTime(){
  m_currentTime = pros::millis() - m_startTime;
  int lapDuration = m_currentTime - m_previousLapTime;
  m_previousLapTime = m_currentTime;
  return lapDuration;
}

bool SubTimer::preformAction(){
  m_currentTime = pros::millis() - m_startTime;

  if(m_currentTime >= m_nextFlag)
    return true;
  else
    return false;
  return 0;
}

int SubTimer::addActionDelay(const int p_delay){
  m_currentTime = pros::millis() - m_startTime;
  m_nextFlag = m_currentTime + p_delay;
  return 1;
}

std::string SubTimer::getName(){
  return m_name;
}

int SubTimer::subGUI(GraphicalInterface& p_gui, const std::string p_returnScreen){
  p_gui.addScreen(m_name);
  p_gui.addLabel(m_name, 200, 10, redText, m_name);
  p_gui.addRectangle(m_name, 0, 0, 480, 40, whiteText);

  p_gui.addLabel(m_name, 20, 50, whiteText, "Start Time: %d ms", &m_startTime);
  p_gui.addLabel(m_name, 20, 80, whiteText, "Current Time: %d ms", &m_currentTime);
  p_gui.addLabel(m_name, 20, 110, whiteText, "Previous Lap Time: %d ms", &m_previousLapTime);
  p_gui.addLabel(m_name, 20, 140, whiteText, "Next Flag: %d", &m_nextFlag);

  p_gui.addButton(m_name, "Go Back", 160, 200, 150, 20);
  p_gui.addButtonScreenChange(m_name, "Go Back", p_returnScreen);
  return 0;
}

Timer::Timer(Robot &p_robot): m_robot(p_robot){}

std::vector<SubTimer*> Timer::m_timeArray{};

int Timer::addSubTimer(SubTimer& p_subTimer){
  m_timeArray.resize(m_timeArray.size()+1);
	m_timeArray.at(m_timeArray.size()-1) = &p_subTimer;
  return 0;
}

int Timer::defineGUI(std::string p_returnScreen){
  GraphicalInterface &l_gui = m_robot.getGUI();
  int l_subTimer = 0;

  for(int page=0; page < m_timeArray.size()/6.0; page++){
        std::string l_screenName = "Timers Page " + std::to_string(page + 1);
        l_gui.addScreen(l_screenName);
        l_gui.addLabel(l_screenName, 200, 10, redText, l_screenName);
        l_gui.addRectangle(l_screenName, 0, 0, 480, 40, whiteText);

        if(1 < (int)ceil(m_timeArray.size()/6.0)){//Adds Buttons for Next and Previous Pages Multiple Screens
          if(page == 0){// First Page
            l_gui.addButton(l_screenName, "Next Page", 265, 170, 150, 20);
            l_gui.addButtonScreenChange(l_screenName, "Next Page", "Timers Page " + std::to_string(page + 2));
          }
          else if(page + 1 == (int)ceil(m_timeArray.size()/6.0)){// Last Page
            l_gui.addButton(l_screenName, "Previous Page", 75, 170, 150, 20);
            l_gui.addButtonScreenChange(l_screenName, "Previous Page", "Timers Page " + std::to_string(page));
          }
          else{
            l_gui.addButton(l_screenName, "Previous Page", 75, 170, 150, 20);
            l_gui.addButtonScreenChange(l_screenName, "Previous Page", "Timers Page " + std::to_string(page));
            l_gui.addButton(l_screenName, "Next Page", 265, 170, 150, 20);
            l_gui.addButtonScreenChange(l_screenName, "Next Page", "Timers Page " + std::to_string(page + 2));
          }
        }

        l_gui.addButton(l_screenName, "Go Back", 160, 200, 150, 20);
        l_gui.addButtonScreenChange(l_screenName, "Go Back", p_returnScreen);

        for(int col = 0; col < 2; col++){
            for(int row = 0; row < 3 && row < m_timeArray.size()-(page*6) - 3*col; row++){
              std::string l_subTimerName = m_timeArray.at(l_subTimer)->getName();
              l_gui.addButton(l_screenName, l_subTimerName, 75+(190*col), 50 + (40*row), 150, 30);
              l_gui.addButtonScreenChange(l_screenName, l_subTimerName, l_subTimerName);

              m_timeArray.at(l_subTimer)->subGUI(l_gui, l_screenName);
              l_subTimer++;
            }
        }
    }
  return 0;
}
