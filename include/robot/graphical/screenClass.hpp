#include "robot/varibleDecleration.hpp"

#ifndef SCREENCLASS_H
#define SCREENCLASS_H

class Screen{
private:
  short m_xOrgin;
  short m_yOrgin;
  short m_length;
  short m_width;

  lv_obj_t* m_container;
  lv_style_t* m_style;

  std::string m_pageID;
  std::string m_relatedScreen;
  std::string& m_nextScreenID;

  std::vector<Button*> m_btnArray;
  std::vector<Label*> m_labelArray;
  std::vector<Meter*> m_meterArray;
  std::vector<Line*> m_lineArray;
  std::vector<Toggle*> m_toggleArray;
  std::vector<Rectangle*> m_rectArray;

  bool m_relation = false;
  bool m_state;
  bool m_inversed;

  std::function<bool()> m_relatedFunc;

public:
	Screen(const PassInfo& p_info);

	void addButton(const PassInfo& p_info);

	void addButtionAction(const PassInfo& p_info);

  void addLabel(PassInfo& p_info);

  void addLine(const PassInfo& p_info);

  void addMeter(const PassInfo& p_info);

  void addToggle(const PassInfo& p_info);

  void addRectangle(const PassInfo& p_info);

  lv_obj_t* getObject();

  void addRelationship(const std::function<bool()> p_function, const bool p_inverse, const std::string p_otherScreen);

  std::string getRelatedScreen();

  std::function<bool()> getRelatedFunc();

  bool getInverse();

  std::string& getNextScreenID();

  std::string getPageID();

  bool isRelation();

  void draw();

  void changeBackground(lv_style_t& p_backColor);

  void update();

  void detect();

  void remove();
};
#endif // SCREENCLASS_H
