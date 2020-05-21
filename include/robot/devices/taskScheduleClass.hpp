#include "robot/varibleDecleration.hpp"
#include "timerClass.hpp"
#include "externalFileClass.hpp"

#ifndef TASKSCHEDCLASS_H
#define TASKSCHEDCLASS_H

struct SubTask{
private:
    std::string m_name;
    std::function<int()> m_function;
    int m_callPeriod = 50;
    int m_callFrequency = 0;
    Timer m_timer;
    TaskType m_callType;
    friend class TaskScheduler;
public:
    SubTask(std::string p_name, std::function<int()> p_function, int p_callPeriod, TaskType p_callType);

    std::string getName();

    std::function<int()> getFunction();

    int getCallPeriod();

    int getCallFrequency();

    TaskType getCallType();
};

class TaskScheduler{
private:
    Robot &m_robot;
    std::string m_name;
    std::vector<SubTask*> m_taskArray;
    RobotMode m_compMode;
    ExternalFile m_config;
public:
    TaskScheduler(Robot &l_robot, std::string p_name);

    int addTask(std::string p_name, std::function<int()> p_callBack, int p_callPeriod, TaskType p_callType);

    int task();

    int setCompMode(RobotMode p_compMode);

    int defineGUI();

    SubTask* findTask(std::string p_name);
};

#endif // TASKSCHEDCLASS_H
