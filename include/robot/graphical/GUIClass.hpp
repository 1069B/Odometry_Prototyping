#include "robot/varibleDecleration.hpp"
#include "robot/devices/timerClass.hpp"
#include "robot/devices/externalFileClass.hpp"

#ifndef GUICLASS_H
#define GUICLASS_H

class GraphicalInterface{
private:
  std::vector<Screen*> m_screenArray;
  int m_noVersion = 0;// For screens with only one version
  std::string m_previousScreenID = "A";
  std::string m_currentScreenID = "B";
  std::string m_nextScreenID = "C";
  Screen* m_nextScreen;// = new Screen("Blank", noVersion, defaultBackground, nextScreenID);
  Screen* m_currentScreen;// = new Screen("Blank", noVersion, defaultBackground, nextScreenID);
  SubTimer m_GUITimer;
  ExternalFile m_GUIStorage;
  void updateScreen();

public:
  GraphicalInterface(const std::string p_startingScreen="Home");

  void addScreen(const std::string p_name, lv_style_t& p_style = defaultBackground);
  void addScreen(const std::string p_name, const int p_xOrgin, const int p_yOrgin, const int p_length, const int p_width, lv_style_t& p_style = defaultBackground);

  void addRelationship(const std::string p_name, const std::function<bool()> p_function, const std::string p_otherScreen, const bool p_inverse = false);

  Screen *findScreen(const std::string p_name);

  void addButton(const std::string p_screenName, const std::string p_format, const int p_xOrgin, const int p_yOrgin, const int p_length, const int p_width, lv_style_t& p_btnRel=defaultBtnRel, lv_style_t& p_btnPress=defaultBtnPress);
	void addButtonScreenChange(const std::string p_screenName, const std::string p_format, const std::string p_linkedID);
  void addButtonVaribleChange(const std::string p_screenName, const std::string p_format, int* p_varible, const int p_value);
  void addButtonVaribleCounter(const std::string p_screenName, const std::string p_format, int* p_varible, const int p_btnIncrement);
  void addButtonStyleChange(const std::string p_screenName, const std::string p_format, int* p_varible, const int p_value, lv_style_t& p_style);
  void addButtonTextChange(const std::string p_screenName, const std::string p_format, std::string* p_varible);
  void addButtonRunFunction(const std::string p_screenName, const std::string p_format, std::function<int()> p_function);

  void defineLabel(PassInfo& p_info, const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, lv_style_t& p_style, const std::string p_format, const int p_mode);
  void addLabel(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, lv_style_t& p_style, const std::string p_format);// mode 0
  void addLabel(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, lv_style_t& p_style, const std::string p_format, int* p_function);// mode 1
	void addLabel(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, lv_style_t& p_style, const std::string p_format, std::function<int()> p_function);// mode 2
	void addLabel(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, lv_style_t& p_style, const std::string p_format, double* p_function);// mode 3
	void addLabel(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, lv_style_t& p_style, const std::string p_format, std::function<double()> p_function);// mode 4
	void addLabel(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, lv_style_t& p_style, const std::string p_format, bool* p_function);// mode 5
	void addLabel(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, lv_style_t& p_style, const std::string p_format, std::function<bool()> p_function);// mode 6
	void addLabel(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, lv_style_t& p_style, const std::string p_format, std::string* p_function);// mode 7
	void addLabel(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, lv_style_t& p_style, const std::string p_format, std::function<std::string()> p_function);// mode 8

  void addLine(const std::string p_screenName, lv_point_t* p_point, lv_style_t& p_style = whiteText);

  void addMeter(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, const std::function<int()> p_function, const int p_rangeL=0, const int p_rangeH=100, const int p_size=125, const int p_angle=240, const int p_numOfDashes=22, lv_style_t& p_metStyle=meterStyle, lv_style_t& p_textStyle=whiteText);
  void addMeter(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, const std::function<int()> p_function, lv_style_t& p_metStyle=meterStyle, lv_style_t& p_textStyle=whiteText);

  void addToggle(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, const int p_length, const int p_width, bool* p_varible);
  void addToggle(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, const int p_length, const int p_width, std::function<bool()> p_varible);

  void addRectangle(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, const int p_length, const int p_width, lv_style_t& p_style);
  void addRectangle(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, const int p_length, const int p_width, const std::function<lv_style_t*()> p_background);

  void task();
};

#endif // GUICLASS_H
