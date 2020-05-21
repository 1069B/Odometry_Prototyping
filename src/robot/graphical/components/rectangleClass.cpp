#include "robot/graphical/components/rectangleClass.hpp"
#include "robot/graphical/components/passInfo.hpp"
#include "robot/graphical/screenClass.hpp"

Rectangle::Rectangle(const PassInfo& p_info, Screen& p_screen): m_screen(p_screen){
  m_xOrgin = p_info.xOrgin; //Every thing is in realtion to the upper left coner
  m_yOrgin = p_info.yOrgin;
  m_length = p_info.length;
  m_width = p_info.width;
  m_mode = p_info.mode;
  if(m_mode)
    m_rectangleStyleFunction = p_info.lv_styleFunction;
  else
    m_rectangleStyle = p_info.style1;
}

void Rectangle::draw(){
  m_rectangle = lv_obj_create(m_screen.getObject(), NULL);
  lv_obj_set_size(m_rectangle, m_length, m_width);
  lv_obj_set_style(m_rectangle, m_rectangleStyle);
  lv_obj_align(m_rectangle, m_screen.getObject(), LV_ALIGN_IN_TOP_LEFT, m_xOrgin, m_yOrgin);
}

void Rectangle::update(){
  if(m_mode){
    m_rectangleStyle = m_rectangleStyleFunction();
    lv_obj_set_style(m_rectangle, m_rectangleStyle);
  }
}
