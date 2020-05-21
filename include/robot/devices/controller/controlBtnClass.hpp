#include "robot/varibleDecleration.hpp"

#ifndef CONTROLBTNCLASS_H
#define CONTROLBTNCLASS_H

class ControlBtn{
private:
  pros::controller_id_e_t m_controllerType;
  pros::controller_digital_e_t m_buttonType;
  bool m_callBackState = false;
  std::function<int()> m_callBack;
  int m_callBackDelay = 0;
  int m_lastCall = 0;

public:
  ControlBtn(const pros::controller_id_e_t p_controller, const pros::controller_digital_e_t p_type);

  void setCallBack(const std::function<int()> p_function, const int p_delay);

  void checkCallBack();

  bool state();
};
#endif // CONTROLBTNCLASS_H
