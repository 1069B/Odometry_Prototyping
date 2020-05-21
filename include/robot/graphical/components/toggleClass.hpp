#include "robot/varibleDecleration.hpp"

#ifndef TOGGLECLASS_H
#define TOGGLECLASS_H

class Toggle{
private:
  Screen& m_screen;
  lv_obj_t* m_toggle;
  short m_xOrgin, m_yOrgin, m_length, m_width;
  int m_mode;
  bool* m_boolPointer;
	std::function<bool()> m_boolFunction;

public:
	Toggle(const PassInfo& p_info, Screen& p_screen);// mode 0

	void draw();

	void update();

  int getState();
};

#endif // TOGGLECLASS_H
