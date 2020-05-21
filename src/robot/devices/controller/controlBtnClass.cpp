#include "robot/devices/controller/controlBtnClass.hpp"

ControlBtn::ControlBtn(const pros::controller_id_e_t p_controller, const pros::controller_digital_e_t p_type){
  m_controllerType = p_controller;
  m_buttonType = p_type;
}

void ControlBtn::setCallBack(const std::function<int()> p_function, const int p_delay){
  m_callBackState = true;
  m_callBack = p_function;
  m_callBackDelay = p_delay;
}

void ControlBtn::checkCallBack(){
  if(m_callBackState && state() && pros::millis() > m_lastCall+m_callBackDelay){
    m_callBack();
    m_lastCall = pros::millis();
  }
}

bool ControlBtn::state(){
  return pros::c::controller_get_digital(m_controllerType, m_buttonType);
}
