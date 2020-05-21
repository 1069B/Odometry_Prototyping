#include "robot/varibleDecleration.hpp"

#ifndef LINECLASS_H
#define LINECLASS_H

class Line{
private:
  Screen& m_screen;
  lv_obj_t* m_line;
  lv_point_t *m_points;
  lv_style_t *m_style;
public:
  Line(const PassInfo& p_info, Screen& p_screen);

  void draw();
};

#endif // LINECLASS_H
