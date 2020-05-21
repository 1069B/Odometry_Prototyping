#include "robot/graphical/components/toggleClass.hpp"
#include "robot/graphical/components/passInfo.hpp"
#include "robot/graphical/screenClass.hpp"

Toggle::Toggle(const PassInfo& p_info, Screen& p_screen):m_screen(p_screen){
  m_xOrgin = p_info.xOrgin;
  m_yOrgin = p_info.yOrgin;
  m_length = p_info.length;
  m_width = p_info.width;
  m_mode = p_info.mode;
  switch(m_mode){
    case 0: m_boolPointer = p_info.boolPointer; break;
    case 1: m_boolFunction = p_info.boolFunction; break;
  }
}

void Toggle::draw(){
  m_toggle = lv_sw_create(m_screen.getObject(), NULL);
  lv_sw_set_style(m_toggle, LV_SW_STYLE_BG, &toggleBackground);
  lv_sw_set_style(m_toggle, LV_SW_STYLE_INDIC, &toggleInactive);
  lv_sw_set_style(m_toggle, LV_SW_STYLE_KNOB_ON, &toggleOn);
  lv_sw_set_style(m_toggle, LV_SW_STYLE_KNOB_OFF, &toggleOff);
  lv_obj_align(m_toggle, NULL, LV_ALIGN_IN_TOP_LEFT, m_xOrgin, m_yOrgin);
  lv_obj_set_size(m_toggle, m_length, m_width);
  update();
}

void Toggle::update(){
  switch(m_mode){
    case 0:
      if(*m_boolPointer)
        lv_sw_on(m_toggle);
      else
        lv_sw_off(m_toggle);
        break;
    case 1:
      if(m_boolFunction())
        lv_sw_on(m_toggle);
      else
        lv_sw_off(m_toggle);
      break;
  }
}

int Toggle::getState(){
  if(m_mode == 0)
    *m_boolPointer = lv_sw_get_state(m_toggle);
  return lv_sw_get_state(m_toggle);
}
