#include "robot/devices/taskScheduleClass.hpp"

SubTask::SubTask(std::string p_name, std::function<int()> p_function, int p_callPeriod, TaskType p_callType):
m_timer(("SubTask: " + p_name), false){
    m_name = p_name;
    m_function = p_function;
    m_callPeriod = p_callPeriod;
    m_callType = p_callType;
};

std::string SubTask::getName(){
    return m_name;
}

std::function<int()> SubTask::getFunction(){
    return m_function;
}

int SubTask::getCallPeriod(){
    return m_callPeriod;
}

int SubTask::getCallFrequency(){
    return m_callFrequency;
}

TaskType SubTask::getCallType(){
    return m_callType;
}

TaskScheduler::TaskScheduler(Robot &l_robot, std::string p_name)
:m_robot(l_robot),m_config("Task_Schedular.txt")
{
    m_name = p_name;
}

int TaskScheduler::addTask(std::string p_name, std::function<int()> p_callBack, int p_callPeriod, TaskType p_callType){
    m_taskArray.push_back(new SubTask(p_name, p_callBack, p_callPeriod, p_callType));
    std::string l_local = p_name + " task has been added. Called every " + std::to_string(p_callPeriod) + " milliseconds";
    m_config.addLine(l_local);
    return 0;
}

int TaskScheduler::task(){
    for(int x = 0; x < m_taskArray.size(); x++){
        if(m_taskArray.at(x)->getCallType() == TASK_ALWAYS && m_taskArray.at(x)->m_timer.preformAction()){
            std::function<int()> l_localFunction = m_taskArray.at(x)->getFunction();
            l_localFunction();
            m_taskArray.at(x)->m_timer.addActionDelay(m_taskArray.at(x)->m_callPeriod);
            m_taskArray.at(x)->m_callFrequency = m_taskArray.at(x)->m_timer.lapTime();
        }

        switch((int)m_compMode) {
            case TASK_AUTO:
                if(m_taskArray.at(x)->getCallType() == TASK_DURING_AUTO && m_taskArray.at(x)->m_timer.preformAction()){
                    std::function<int()> l_localFunction = m_taskArray.at(x)->getFunction();
                    l_localFunction();
                    m_taskArray.at(x)->m_timer.addActionDelay(m_taskArray.at(x)->m_callPeriod);
                    m_taskArray.at(x)->m_callFrequency = m_taskArray.at(x)->m_timer.lapTime();
                }
                break;

            case TASK_OPERATER:
                if(m_taskArray.at(x)->getCallType() == TASK_DURING_OPERATER && m_taskArray.at(x)->m_timer.preformAction()){
                    std::function<int()> l_localFunction = m_taskArray.at(x)->getFunction();
                    l_localFunction();
                    m_taskArray.at(x)->m_timer.addActionDelay(m_taskArray.at(x)->m_callPeriod);
                    m_taskArray.at(x)->m_callFrequency = m_taskArray.at(x)->m_timer.lapTime();
                }
                break;

            default:
                break;
        }
    }
    return 0;
}

int TaskScheduler::setCompMode(RobotMode p_compMode){
    m_compMode = p_compMode;
    return 0;
}

SubTask* TaskScheduler::findTask(std::string p_name){
  for(int x = 0; x < m_taskArray.size(); x++)
    if(m_taskArray.at(x)->m_name == p_name)
      return m_taskArray.at(x);
  return NULL;
}

int TaskScheduler::defineGUI(){
    return 0;
}
