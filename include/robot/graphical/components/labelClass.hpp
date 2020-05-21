#include "robot/varibleDecleration.hpp"

#ifndef LABELCLASS_H
#define LABELCLASS_H

class Label{
private:
  /*Fundamental Varibes for Label*/
  Screen& m_screen;
  lv_obj_t *m_label;
  short m_xOrgin, m_yOrgin;
  int m_mode;
  lv_style_t *m_style;
  std::string m_text;

  /*Addition Varibles for Numerical Integration*/
  int* m_intPointer;
	std::function<int()> m_intFunction;
	double* m_doublePointer;
	std::function<double()> m_doubleFunction;
	bool* m_boolPointer;
	std::function<bool()> m_boolFunction;
	std::string* m_stringPointer;
	std::function<std::string()> m_stringFunction;

public:
	Label(const PassInfo& p_info, Screen& p_screen);// mode 0

  void setString();

	void draw();

	void update();
};
#endif // LABELCLASS_H
