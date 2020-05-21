#include "robot/graphical/components/labelClass.hpp"
#include "robot/graphical/components/passInfo.hpp"
#include "robot/graphical/screenClass.hpp"

Label::Label(const PassInfo& p_info, Screen& p_screen):m_screen(p_screen){// mode 0
  m_xOrgin = p_info.xOrgin;
  m_yOrgin = p_info.yOrgin;
  m_style = p_info.style1;
  m_text = p_info.text;
  m_mode = p_info.mode;
  switch(m_mode){
    case 0: break;
    case 1: m_intPointer = p_info.intPointer; break;
    case 2: m_intFunction = p_info.intFunction; break;
    case 3: m_doublePointer = p_info.doublePointer; break;
    case 4: m_doubleFunction = p_info.doubleFunction; break;
    case 5: m_boolPointer = p_info.boolPointer; break;
    case 6: m_boolFunction = p_info.boolFunction; break;
    case 7: m_stringPointer = p_info.stringPointer; break;
    case 8: m_stringFunction = p_info.stringFunction; break;
  }
}

void Label::setString(){
  std::string fmt = m_text;
  std::string sum = "";
  switch(m_mode){
    case 0:
      sum = fmt;
      break;
    case 1:
      sum = fmt.substr(0, fmt.find("%d")) + std::to_string(*m_intPointer) + fmt.substr(fmt.find("%d")+2);
      break;
    case 2:
      sum = fmt.substr(0, fmt.find("%d")) + std::to_string(m_intFunction()) + fmt.substr(fmt.find("%d")+2);
      break;
    case 3:
      sum = fmt.substr(0, fmt.find("%f")) + std::to_string(*m_doublePointer) + fmt.substr(fmt.find("%f")+2);
      break;
    case 4:
      sum = fmt.substr(0, fmt.find("%f")) + std::to_string(m_doubleFunction()) + fmt.substr(fmt.find("%f")+2);
      break;
    case 5:
      if(*m_boolPointer)
        sum = fmt.substr(0, fmt.find("%b")) + "True" + fmt.substr(fmt.find("%b")+2);
      else
        sum = fmt.substr(0, fmt.find("%b")) + "False" + fmt.substr(fmt.find("%b")+2);
      break;
    case 6:
      if(m_boolFunction())
        sum = fmt.substr(0, fmt.find("%b")) + "True" + fmt.substr(fmt.find("%b")+2);
      else
        sum = fmt.substr(0, fmt.find("%b")) + "False" + fmt.substr(fmt.find("%b")+2);
      break;
    case 7:
      sum = fmt.substr(0, fmt.find("%s")) + *m_stringPointer + fmt.substr(fmt.find("%s")+2);
      break;
    case 8:
      sum = fmt.substr(0, fmt.find("%s")) + m_stringFunction() + fmt.substr(fmt.find("%s")+2);
      break;
  }
  lv_label_set_text(m_label, sum.c_str());
}

void Label::draw(){
  m_label = lv_label_create(m_screen.getObject(), NULL);
  lv_obj_align(m_label, m_screen.getObject(), LV_ALIGN_IN_TOP_LEFT, m_xOrgin, m_yOrgin);
  setString();
  lv_obj_set_style(m_label, m_style);
}

void Label::update(){
  setString();
}
