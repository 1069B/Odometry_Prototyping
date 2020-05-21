#include "robot/varibleDecleration.hpp"

#ifndef BUTTONCLASS_H
#define BUTTONCLASS_H

class Button{
private:
  /*Required Variles for Button*/
  Screen& m_screen;
  lv_obj_t* m_button, *m_label;
  short m_xOrgin, m_yOrgin, m_length, m_width;
  lv_style_t *m_buttonReleased, *m_buttonPressed;
  std::string m_text;
  std::string& m_updateScreenVarible;

  static Timer s_timer;

  /*Required Variles for Change Screen Action*/
  bool m_changeScreen = false;
  std::string m_linkedScreenID;

  /*Required Variles for Change Varible Value Action*/
  bool m_changeVar = false;
  int* m_changeVarPointer;
  int m_changeVarValue;

  /*Required Variles for Increment Varible Screen Action*/
  bool m_incrementVar = false;
  int* m_incrementVarPointer;
  int m_incrementVarValue;

  /*Required Variles for Change Style Action*/
  bool m_changeBackground = false;
  int* m_changeBackgroundPointer;
  int m_changeBackgroundValue;
  lv_style_t *m_changeBackgroundStyle;

  /*Required Varibles for Text Change*/
  bool m_changeText = false;
  std::string* m_changeTextPointer;

  /*Required Varibles for Run Function*/
  bool m_preformFunction = false;
  std::function<int()> m_runFunction;

public:
  Button(const PassInfo& p_info, Screen& p_screen);

  void defineAction(const PassInfo& p_info);

  void draw();

  void update();

  bool returnState();

  std::string getText();
};

#endif // BUTTONCLASS_H
