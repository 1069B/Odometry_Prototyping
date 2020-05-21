#include "robot/varibleDecleration.hpp"

#ifndef ALERTCLASS_H
#define ALERTCLASS_H

class Alert{
private:
  lv_obj_t* m_alert;
  static bool m_repeat;

public:
  Alert();

  int draw(const std::string p_message);

  static lv_res_t alertResponse(lv_obj_t * btnm, const char *txt);
};

#endif // ALERTCLASS_H
