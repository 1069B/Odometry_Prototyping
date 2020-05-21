#include "robot/graphical/components/meterClass.hpp"
#include "robot/graphical/components/passInfo.hpp"
#include "robot/graphical/screenClass.hpp"

Meter::Meter(const PassInfo& p_info, Screen& p_screen): m_screen(p_screen){
  m_xOrgin = p_info.xOrgin;
  m_yOrgin = p_info.yOrgin;
  m_rangeLow = p_info.rangeLow;
  m_rangeHigh = p_info.rangeHigh;
  m_size = p_info.sizeFactor;
  m_angle = p_info.angle;
  m_numberOfDashes = p_info.numOfDashes;
  m_meterStyle = p_info.style1;// Default styles
  m_labelStyle = p_info.style2;
  m_intFunction = p_info.intFunction;
}

void Meter::draw(){
  m_meter = lv_lmeter_create(m_screen.getObject(), NULL);
  lv_obj_set_style(m_meter, m_meterStyle);
  lv_lmeter_set_range(m_meter, m_rangeLow, m_rangeHigh);
  lv_obj_set_size(m_meter, m_size, m_size);
  lv_obj_align(m_meter, m_screen.getObject(), LV_ALIGN_IN_TOP_LEFT, m_xOrgin, m_yOrgin);
  lv_lmeter_set_scale(m_meter, m_angle, m_numberOfDashes);
  lv_lmeter_set_value(m_meter, 42);

  m_label = lv_label_create(m_meter, NULL);
  lv_label_set_text(m_label, "42%");
  lv_obj_set_style(m_label, m_labelStyle);
  lv_obj_align(m_label, m_meter, LV_ALIGN_CENTER, 0, 0);
}

void Meter::update(){
    lv_lmeter_set_value(m_meter, m_intFunction());
    lv_label_set_text(m_label, std::to_string(m_intFunction()).c_str());
}
