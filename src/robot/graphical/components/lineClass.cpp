#include "robot/graphical/components/lineClass.hpp"
#include "robot/graphical/components/passInfo.hpp"
#include "robot/graphical/screenClass.hpp"

Line::Line(const PassInfo& p_info, Screen& p_screen): m_screen(p_screen){
  m_points = p_info.points;
  m_style = p_info.style1;
}

void Line::draw(){
  m_line = lv_line_create(m_screen.getObject(), NULL);
  lv_line_set_points(m_line, m_points, 2);
  lv_obj_align(m_line, m_screen.getObject(), LV_ALIGN_IN_TOP_LEFT, 0, 0);
  lv_line_set_style(m_line, m_style);
}
