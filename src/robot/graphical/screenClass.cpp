#include "robot/graphical/components/passInfo.hpp"
#include "robot/graphical/screenClass.hpp"
#include "robot/graphical/components/buttonClass.hpp"
#include "robot/graphical/components/lineClass.hpp"
#include "robot/graphical/components/labelClass.hpp"
#include "robot/graphical/components/meterClass.hpp"
#include "robot/graphical/components/toggleClass.hpp"
#include "robot/graphical/components/rectangleClass.hpp"


Screen::Screen(const PassInfo& p_info):
m_nextScreenID(*p_info.stringPointer){
  m_pageID = p_info.name;
  m_xOrgin = p_info.xOrgin;
  m_yOrgin = p_info.yOrgin;
  m_length = p_info.length;
  m_width = p_info.width;
  m_style = p_info.style1;
  m_state = false;
}

lv_obj_t* Screen::getObject(){
  return m_container;
}

void Screen::changeBackground(lv_style_t& p_backColor){
  m_style = &p_backColor;
}

void Screen::addRelationship(const std::function<bool()> func, const bool inverse, const std::string otherScreen){
  m_relation = true;
  m_relatedFunc = func;
  m_relatedScreen = otherScreen;
  m_inversed = inverse;
}
std::string Screen::getRelatedScreen(){
  return m_relatedScreen;
}
std::function<bool()> Screen::getRelatedFunc(){
  return m_relatedFunc;
}
bool Screen::getInverse(){
  return m_inversed;
}

std::string& Screen::getNextScreenID(){
  return m_nextScreenID;
}

std::string Screen::getPageID(){
  return m_pageID;
}

bool Screen::isRelation(){
  return m_relation;
}

void Screen::addButton(const PassInfo& p_info){
  m_btnArray.resize(m_btnArray.size()+1);
	m_btnArray.at(m_btnArray.size()-1) = new Button(p_info, *this);
}
void Screen::addButtionAction(const PassInfo& p_info){
  for(int y = 0; y < m_btnArray.size(); y++){
    if(m_btnArray.at(y)->getText() == p_info.text)
      m_btnArray.at(y)->defineAction(p_info);
  }
}
void Screen::addLabel(PassInfo& p_info){
  m_labelArray.resize(m_labelArray.size()+1);
	m_labelArray.at(m_labelArray.size()-1) = new Label(p_info, *this);
}
void Screen::addLine(const PassInfo& p_info){
  m_lineArray.resize(m_lineArray.size()+1);
  m_lineArray.at(m_lineArray.size()-1) = new Line(p_info, *this);
}
void Screen::addMeter(const PassInfo& p_info){
  m_meterArray.resize(m_meterArray.size()+1);
  m_meterArray.at(m_meterArray.size()-1) = new Meter(p_info, *this);
}
void Screen::addToggle(const PassInfo& p_info){
  m_toggleArray.resize(m_toggleArray.size()+1);
  m_toggleArray.at(m_toggleArray.size()-1) = new Toggle(p_info, *this);
}
void Screen::addRectangle(const PassInfo& p_info){
  m_rectArray.resize(m_rectArray.size()+1);
  m_rectArray.at(m_rectArray.size()-1) = new Rectangle(p_info, *this);
}

void Screen::draw(){
  m_container = lv_cont_create(lv_scr_act(), NULL);
  lv_obj_align(m_container, NULL, LV_ALIGN_IN_TOP_LEFT, m_xOrgin, m_yOrgin);
  lv_obj_set_size(m_container, m_length, m_width);
  lv_obj_set_style(m_container, m_style);

  for(int y = 0; y < m_rectArray.size(); y++)
    m_rectArray.at(y)->draw();

  for(int y = 0; y < m_btnArray.size(); y++)
    m_btnArray.at(y)->draw();

  for(int y = 0; y <m_labelArray.size(); y++)
    m_labelArray.at(y)->draw();

  for(int y = 0; y < m_lineArray.size(); y++)
    m_lineArray.at(y)->draw();

  for(int y = 0; y < m_meterArray.size(); y++)
    m_meterArray.at(y)->draw();

  for(int y = 0; y < m_toggleArray.size(); y++)
    m_toggleArray.at(y)->draw();
  m_state = true;
}
void Screen::update(){
  for(int y = 0; y < m_btnArray.size(); y++)
    m_btnArray.at(y)->update();

  for(int y = 0; y < m_labelArray.size(); y++)
    m_labelArray.at(y)->update();

  for(int y = 0; y < m_meterArray.size(); y++)
    m_meterArray.at(y)->update();

  for(int y = 0; y < m_toggleArray.size(); y++)
    m_toggleArray.at(y)->update();
}
void Screen::detect(){
  for(int y = 0; y < m_toggleArray.size(); y++)
    m_toggleArray.at(y)->getState();
}
void Screen::remove(){
  if(m_state){
    lv_obj_clean(m_container);
    lv_obj_del(m_container);
    m_state = false;
  }
}
