#include "robot/varibleDecleration.hpp"

#ifndef METERCLASS_H
#define METERCLASS_H

class Meter{
private:
  /*Required Varibles for Line Meter*/
  Screen& m_screen;
  lv_obj_t* m_meter, *m_label;
  short m_xOrgin, m_yOrgin;
  int m_id;
  lv_style_t *m_meterStyle, *m_labelStyle;

  /*Additional Agumenting Varibles*/
  int m_rangeLow = 0, m_rangeHigh = 100,
  m_size = 125, m_angle = 240, m_numberOfDashes = 22;
  std::function<int()> m_intFunction;
  
public:
  Meter(const PassInfo& p_info, Screen& p_screen);

  void draw();

  void update();
};

#endif // METERCLASS_H
