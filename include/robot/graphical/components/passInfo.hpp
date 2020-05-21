#include "robot/varibleDecleration.hpp"

#ifndef PASSINFO_H
#define PASSINFO_H

struct PassInfo{
  short xOrgin, yOrgin, length, width;
  int id, mode, rangeLow, rangeHigh, sizeFactor, angle ,numOfDashes, version, passValue;
  std::string text, linkedID, name;

  int* intPointer;
	std::function<int()> intFunction;
	double* doublePointer;
	std::function<double()> doubleFunction;
	bool* boolPointer;
	std::function<bool()> boolFunction;
	std::string* stringPointer;
	std::function<std::string()> stringFunction;
  std::function<lv_style_t*()> lv_styleFunction;

  lv_style_t *style1, *style2;
  lv_point_t *points;
};

#endif //PASSINFO_H
