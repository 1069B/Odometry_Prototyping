#include "robot/graphical/components/buttonClass.hpp"
#include "robot/graphical/components/passInfo.hpp"
#include "robot/graphical/screenClass.hpp"
#include "robot/devices/timerClass.hpp"

Button::Button(const PassInfo& p_info, Screen& p_screen):
m_screen(p_screen),m_updateScreenVarible(p_screen.getNextScreenID()){
  m_xOrgin = p_info.xOrgin;
  m_yOrgin = p_info.yOrgin;
  m_length = p_info.length;
  m_width = p_info.width;
  m_buttonReleased = p_info.style1;
  m_buttonPressed = p_info.style2;
  m_text = p_info.text;
}

Timer Button::s_timer(false);

void Button::defineAction(const PassInfo& p_info){
  switch(p_info.mode){
    case 0:
      m_linkedScreenID = p_info.linkedID;
      m_changeScreen = true;
      break;
    case 1:
      m_changeVarPointer = p_info.intPointer;
      m_changeVarValue = p_info.passValue;
      m_changeVar = true;
      break;
    case 2:
      m_incrementVarPointer = p_info.intPointer;
      m_incrementVarValue = p_info.passValue;
      m_incrementVar = true;
      break;
    case 3:
      m_changeBackgroundPointer = p_info.intPointer;
      m_changeBackgroundValue = p_info.passValue;
      m_changeBackgroundStyle = p_info.style1;
      m_changeBackground = true;
      break;
    case 4:
      m_changeTextPointer = p_info.stringPointer;
      m_changeText = true;
      break;
    case 5:
      m_runFunction = p_info.intFunction;
      m_preformFunction = true;
      break;
  }
}

void Button::draw(){
  m_button = lv_btn_create(m_screen.getObject(), NULL);
  m_label = lv_label_create(m_button, NULL);
  lv_obj_align(m_button, m_screen.getObject(), LV_ALIGN_IN_TOP_LEFT, m_xOrgin, m_yOrgin);
  lv_obj_set_size(m_button, m_length, m_width); //set the button size
  lv_btn_set_style(m_button, LV_BTN_STYLE_REL, m_buttonReleased); //set the relesed style
  lv_btn_set_style(m_button, LV_BTN_STYLE_PR, m_buttonPressed); //set the pressed style
  if(m_changeText)
    lv_label_set_text(m_label, (*m_changeTextPointer).c_str());
  else
    lv_label_set_text(m_label, m_text.c_str());
}

void Button::update(){
  if(s_timer.preformAction() && lv_btn_get_state(m_button) == LV_BTN_STATE_PR){// On Press
    if(m_changeScreen)
      m_updateScreenVarible = m_linkedScreenID;

    if(m_changeVar)
      *m_changeVarPointer = m_changeVarValue;

    if(m_incrementVar)
      *m_incrementVarPointer += m_incrementVarValue;

    if(m_preformFunction)
      m_runFunction();

    s_timer.addActionDelay(1000);
  }
  if(m_changeBackground && *m_changeBackgroundPointer == m_changeBackgroundValue)
    lv_btn_set_style(m_button, LV_BTN_STYLE_REL, m_changeBackgroundStyle);
  else
    lv_btn_set_style(m_button, LV_BTN_STYLE_REL, m_buttonReleased);
  if(m_changeText)
    lv_label_set_text(m_label, (*m_changeTextPointer).c_str());
  else
    lv_label_set_text(m_label, m_text.c_str());
}

bool Button::returnState(){
  if(lv_btn_get_state(m_button) == LV_BTN_STATE_PR)
    return true;
   return false;
}

std::string Button::getText(){
  return m_text;
}
