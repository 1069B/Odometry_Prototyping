#include "robotClass.hpp"

int x =0;
int a =0;
bool c = true;

int Robot::defineGUI(){
  defineStyles();
  m_mainController.defineGUI(m_gui, "Home");
  m_partnerController.defineGUI(m_gui, "Home");
  m_base.defineGUI("Home");

  m_gui.addScreen("Home");
  m_gui.addButton("Home", "Subsystems", 50, 100, 150, 30);
  m_gui.addButtonScreenChange("Home", "Subsystems", "Subsystems");
  m_gui.addButton("Home", "Auto Selector", 250, 100, 150, 30);
  m_gui.addButtonScreenChange("Home", "Auto Selector", "Autonomous_Side_Selector");
  m_gui.addLabel("Home", 80, 80, whiteText, "Robot Mode: %s", &m_robotModeString);
  m_gui.addLabel("Home", 80, 20, whiteText, "Program Mode: %d", &m_programNumber);

  m_gui.addScreen("Subsystems");
  m_gui.addButton("Subsystems", "Odometry", 20, 40, 150, 30);
  m_gui.addButtonScreenChange("Subsystems", "Odometry", "Odometry");
  m_gui.addButton("Subsystems", "Tray", 20, 80, 150, 30);
  m_gui.addButtonScreenChange("Subsystems", "Tray", "Tray");
  m_gui.addButton("Subsystems", "Slider", 20, 120, 150, 30);
  m_gui.addButtonScreenChange("Subsystems", "Slider", "Slider");

  m_gui.addButton("Subsystems", "Left Intake", 180, 40, 150, 30);
  m_gui.addButtonScreenChange("Subsystems", "Left Intake", "Left_Intake");
  m_gui.addButton("Subsystems", "Right Intake", 180, 80, 150, 30);
  m_gui.addButtonScreenChange("Subsystems", "Right Intake", "Right_Intake");
  m_gui.addButton("Subsystems", "Base", 180, 80, 150, 30);
  m_gui.addButtonScreenChange("Subsystems", "Base", "Holonomic");

  m_gui.addButton("Subsystems", "Cotrol_Main", 330, 40, 150, 30);
  m_gui.addButtonScreenChange("Subsystems", "Cotrol_Main", "Main Controller");
  m_gui.addButton("Subsystems", "Cotrol_Partner", 330, 80, 150, 30);
  m_gui.addButtonScreenChange("Subsystems", "Cotrol_Partner", "Partner Controller");

  m_gui.addButton("Subsystems", "Go Back", 200, 200, 150, 30);
  m_gui.addButtonScreenChange("Subsystems", "Go Back", "Home");


  // m_gui.addScreen("Settings");
  // m_gui.addLabel("Settings", 20, 20, whiteText, "Comp");

  m_gui.addScreen("No_Device");
  m_gui.addLabel("No_Device", 150, 100, whiteText, "Device Not Connected");
  m_gui.addButton("No_Device", "Go Back", 160, 200, 150, 20);
  m_gui.addButtonScreenChange("No_Device", "Go Back", "Home");

  m_gui.addScreen("No_Screen_Found");
  m_gui.addLabel("No_Screen_Found", 150, 100, whiteText, "Screen Not Found");
  m_gui.addButton("No_Screen_Found", "Go Back", 160, 200, 150, 20);
  m_gui.addButtonScreenChange("No_Screen_Found", "Go Back", "Home");

  // m_gui.addScreen("Timer1");
  // m_gui.addLabel("Timer1", 20, 20, whiteText, "Timer1: %d millis", (std::function<int()>) std::bind(&Timer::getTime, &m_timer));
  // m_gui.addLabel("Timer1", 20, 50, whiteText, "Timer1: %d lapTime", (std::function<int()>) std::bind(&Timer::lapTime, &m_timer));

  //m_gui.addLabel("Timer1", 20, 110, whiteText, "Calcs per sec %d", &a);


  //m_gui.addButton("Timer1", 0, 160, 200, 150, 20);
  //m_gui.addButtonAction("Timer1", 0,"Go Back", "Home");

  m_gui.addScreen("Autonomous_Side_Selector");
  m_gui.addLabel("Autonomous_Side_Selector", 200, 10, redText, "Which Side Are You On?");
  m_gui.addRectangle("Autonomous_Side_Selector", 0, 0, 480, 40, whiteText);

  m_gui.addButton("Autonomous_Side_Selector", "Red", 75, 50, 140, 30);
  m_gui.addButtonScreenChange("Autonomous_Side_Selector", "Red", "Home");
  m_gui.addButtonVaribleChange("Autonomous_Side_Selector", "Red", &m_programNumber, AUTO_RED);

  m_gui.addButton("Autonomous_Side_Selector", "Blue", 75, 90, 140, 30);
  m_gui.addButtonScreenChange("Autonomous_Side_Selector", "Blue", "Home");
  m_gui.addButtonVaribleChange("Autonomous_Side_Selector", "Blue", &m_programNumber, AUTO_BLUE);

  m_gui.addButton("Autonomous_Side_Selector", "Skills", 75, 130, 140, 30);
  m_gui.addButtonScreenChange("Autonomous_Side_Selector", "Skills", "Home");
  m_gui.addButtonVaribleChange("Autonomous_Side_Selector", "Skills", &m_programNumber, AUTO_SKILLS);

  m_gui.addButton("Autonomous_Side_Selector", "None", 75, 170, 140, 30);
  m_gui.addButtonScreenChange("Autonomous_Side_Selector", "None", "Home");
  m_gui.addButtonVaribleChange("Autonomous_Side_Selector", "None", &m_programNumber, AUTO_NONE);

  return 0;
}
