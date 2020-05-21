#include "robot/varibleDecleration.hpp"

#ifndef RECTANGLECLASS_H
#define RECTANGLECLASS_H

class Rectangle{
private:
  /*Required Variles for Retangle*/
  Screen& m_screen;
  lv_obj_t* m_rectangle;
  short m_xOrgin, m_yOrgin, m_length, m_width;
  int m_mode;

  /*Additional Varibles for Style Modifing*/
  lv_style_t *m_rectangleStyle;
  std::function<lv_style_t*()> m_rectangleStyleFunction;

public:
  Rectangle(const PassInfo& p_info, Screen& p_screen);

  void draw();

  void update();
};

#endif // RECTANGLECLASS_H
