#include "robot/autonomousClass.hpp"
#include "robotClass.hpp"

AutoBaseEvent::AutoBaseEvent(Base &p_base, const int p_delay, const double p_desiredXPosition, const double p_desiredYPosition, const double p_desiredOrientation, const short p_maximumVelocity, const pros::motor_brake_mode_e p_endBrakeMode):m_base(p_base) {
  m_actionDelay = p_delay;
  m_desiredXPosition = p_desiredXPosition;
  m_desiredYPosition = p_desiredYPosition;
  m_desiredYPosition = p_desiredYPosition;
  m_maximumVelocity = p_maximumVelocity;
  m_endBrakeMode = p_endBrakeMode;
}

AutoArmEvent::AutoArmEvent(Arm &p_arm, const int p_delay, const double p_desiredPosition, const short p_maximumVelocity, const pros::motor_brake_mode_e p_endBrakeMode):m_arm(p_arm){
  m_actionDelay = p_delay;
  m_desiredPosition = p_desiredPosition;
  m_maximumVelocity = p_maximumVelocity;
  m_endBrakeMode = p_endBrakeMode;
}

AutoIntakeEvent::AutoIntakeEvent(Intake &p_intake, const int p_delay, const double p_desiredPosition, const short p_maximumVelocity, const pros::motor_brake_mode_e p_endBrakeMode):m_intake(p_intake){
  m_actionDelay = p_delay;
  m_desiredPosition = p_desiredPosition;
  m_maximumVelocity = p_maximumVelocity;
  m_endBrakeMode = p_endBrakeMode;
  m_duration = false;
}
AutoIntakeEvent::AutoIntakeEvent(Intake &p_intake, const int p_delay, const int p_desiredDuration, const short p_maximumVelocity, const pros::motor_brake_mode_e p_endBrakeMode):m_intake(p_intake){
  m_actionDelay = p_delay;
  m_desiredDuration = p_desiredDuration;
  m_maximumVelocity = p_maximumVelocity;
  m_endBrakeMode = p_endBrakeMode;
  m_duration = true;
}

AutoProgram::AutoProgram(const std::string p_name, const AutonomousSide p_autoSide, const int p_programNumber):
m_baseTimer("Auton Base", false), m_armTimer("Auton Arm", false), m_intakeTimer("Auton Intake", false){
  m_name = p_name;
  m_autoSide = p_autoSide;
  m_programNumber = p_programNumber;
}

std::string AutoProgram::getName(){
  return m_name;
}

int AutoProgram::addBaseEvent(AutoBaseEvent& p_event){
  m_baseEvents.push_back(p_event);
  return 0;
}

int AutoProgram::addArmEvent(AutoArmEvent& p_event){
  m_armEvents.push_back(p_event);
  return 0;
}

int AutoProgram::addIntakeEvent(AutoIntakeEvent& p_event){
  m_intakeEvents.push_back(p_event);
  return 0;
}

Autonomous::Autonomous(Robot& p_robot):m_robot(p_robot){
  m_bluePrograms.resize(6, NULL);
  m_blueProgramNames.resize(6, "Not Defined");
  m_redPrograms.resize(6, NULL);
  m_redProgramNames.resize(6, "Not Defined");
  m_skillsPrograms.resize(6, NULL);
  m_skillsProgramNames.resize(6, "Not Defined");
  m_displayProgramNames.resize(6, "Not Defined");

  //m_robot.getTaskScheduler().addTask("Autonomous_Task", std::bind(&Autonomous::task,this), 25, TASK_ALWAYS);
  m_robot.getTaskScheduler().addTask("Autonomous_Dameon", std::bind(&Autonomous::autoProgramDaemon,this), 25, TASK_DURING_AUTO);
}

int Autonomous::addProgram(AutoProgram& p_program){
  switch ((int)p_program.getAutoSide()) {
    case AUTO_RED:
      m_redPrograms.at(p_program.getProgramNumber()) = &p_program;
      m_redProgramNames.at(p_program.getProgramNumber()) = p_program.getName();
      break;
    case AUTO_BLUE:
      m_bluePrograms.push_back(&p_program);
      m_blueProgramNames.at(p_program.getProgramNumber()) = p_program.getName();
      break;
    case AUTO_SKILLS:
      m_skillsPrograms.push_back(&p_program);
      m_skillsProgramNames.at(p_program.getProgramNumber()) = p_program.getName();
      break;
  }
  return 0;
}

int Autonomous::displayRedAuto(){
  m_displayProgramNames = m_redProgramNames;
  return AUTO_RED;
}
int Autonomous::displayBlueAuto(){
  m_displayProgramNames = m_blueProgramNames;
  return AUTO_BLUE;
}
int Autonomous::displaySkillsAuto(){
  m_displayProgramNames = m_skillsProgramNames;
  return AUTO_SKILLS;
}

int Autonomous::confirmAuto(){
  switch ((int)m_autoSide) {
    case AUTO_RED:
      m_selectedProgram = findProgram(m_selectedProgramNumber, AUTO_RED);
      break;
    case AUTO_BLUE:
      m_selectedProgram = findProgram(m_selectedProgramNumber, AUTO_BLUE);
      break;
    case AUTO_SKILLS:
      m_selectedProgram = findProgram(m_selectedProgramNumber, AUTO_SKILLS);
      break;
  }
  return 0;
}

AutoProgram* Autonomous::findProgram(const int p_number, const AutonomousSide p_autoSide){
  if(p_number >=0 && p_number <=5){
    switch ((int)p_autoSide) {
      case AUTO_RED:
          return m_redPrograms.at(p_number);
        break;
      case AUTO_BLUE:
          return m_bluePrograms.at(p_number);
        break;
      case AUTO_SKILLS:
          return m_skillsPrograms.at(p_number);
        break;
    }
  }
  return new AutoProgram("Error", AUTO_NONE, 0);
}

int Autonomous::defineGUI(const std::string p_returnScreenID){
  GraphicalInterface& l_gui = m_robot.getGUI();

  l_gui.addScreen("Autonomous_Side_Selector");
  l_gui.addLabel("Autonomous_Side_Selector", 200, 10, redText, "Which Side Are You On?");
  l_gui.addRectangle("Autonomous_Side_Selector", 0, 0, 480, 40, whiteText);

  l_gui.addButton("Autonomous_Side_Selector", "Red", 75, 50, 140, 30);
  l_gui.addButtonScreenChange("Autonomous_Side_Selector", "Red", "Autonomous_Program_Selector");
  l_gui.addButtonVaribleChange("Autonomous_Side_Selector", "Red", &m_autoSide, AUTO_RED);
  l_gui.addButtonRunFunction("Autonomous_Side_Selector", "Red", std::bind(&Autonomous::displayRedAuto, this));

  l_gui.addButton("Autonomous_Side_Selector", "Blue", 75, 100, 140, 30);
  l_gui.addButtonScreenChange("Autonomous_Side_Selector", "Blue", "Autonomous_Program_Selector");
  l_gui.addButtonVaribleChange("Autonomous_Side_Selector", "Blue", &m_autoSide, AUTO_BLUE);
  l_gui.addButtonRunFunction("Autonomous_Side_Selector", "Blue", std::bind(&Autonomous::displayBlueAuto, this));

  l_gui.addButton("Autonomous_Side_Selector", "Skills", 75, 150, 140, 30);
  l_gui.addButtonScreenChange("Autonomous_Side_Selector", "Skills", "Autonomous_Program_Selector");
  l_gui.addButtonVaribleChange("Autonomous_Side_Selector", "Skills", &m_autoSide, AUTO_SKILLS);
  l_gui.addButtonRunFunction("Autonomous_Side_Selector", "Skills", std::bind(&Autonomous::displaySkillsAuto, this));

  /* Auto Selector*/
  l_gui.addScreen("Autonomous_Program_Selector");
  l_gui.addLabel("Autonomous_Program_Selector", 200, 10, redText, "Select the Desired Routine");
  l_gui.addRectangle("Autonomous_Program_Selector", 0, 0, 480, 40, whiteText);

  l_gui.addButton("Autonomous_Program_Selector", "Button_0", 75, 50, 140, 30);
  l_gui.addButtonScreenChange("Autonomous_Program_Selector", "Button_0", "Select_Confermation");
  l_gui.addButtonVaribleChange("Autonomous_Program_Selector", "Button_0", &m_selectedProgramNumber, 0);
  l_gui.addButtonTextChange("Autonomous_Program_Selector", "Button_0", &m_displayProgramNames.at(0));

  l_gui.addButton("Autonomous_Program_Selector", "Button_1", 75, 100, 140, 30);
  l_gui.addButtonScreenChange("Autonomous_Program_Selector", "Button_1", "Select_Confermation");
  l_gui.addButtonVaribleChange("Autonomous_Program_Selector", "Button_1", &m_selectedProgramNumber, 1);
  l_gui.addButtonTextChange("Autonomous_Program_Selector", "Button_1", &m_displayProgramNames.at(1));

  l_gui.addButton("Autonomous_Program_Selector", "Button_2", 75, 150, 140, 30);
  l_gui.addButtonScreenChange("Autonomous_Program_Selector", "Button_2", "Select_Confermation");
  l_gui.addButtonVaribleChange("Autonomous_Program_Selector", "Button_2", &m_selectedProgramNumber, 2);
  l_gui.addButtonTextChange("Autonomous_Program_Selector", "Button_2", &m_displayProgramNames.at(2));

  l_gui.addButton("Autonomous_Program_Selector", "Button_3", 265, 50, 140, 30);
  l_gui.addButtonScreenChange("Autonomous_Program_Selector", "Button_3", "Select_Confermation");
  l_gui.addButtonVaribleChange("Autonomous_Program_Selector", "Button_3", &m_selectedProgramNumber, 3);
  l_gui.addButtonTextChange("Autonomous_Program_Selector", "Button_3", &m_displayProgramNames.at(3));

  l_gui.addButton("Autonomous_Program_Selector", "Button_4", 265, 100, 140, 30);
  l_gui.addButtonScreenChange("Autonomous_Program_Selector", "Button_4", "Select_Confermation");
  l_gui.addButtonVaribleChange("Autonomous_Program_Selector", "Button_4", &m_selectedProgramNumber, 4);
  l_gui.addButtonTextChange("Autonomous_Program_Selector", "Button_4", &m_displayProgramNames.at(4));

  l_gui.addButton("Autonomous_Program_Selector", "Button_5", 265, 150, 140, 30);
  l_gui.addButtonScreenChange("Autonomous_Program_Selector", "Button_5", "Select_Confermation");
  l_gui.addButtonVaribleChange("Autonomous_Program_Selector", "Button_5", &m_selectedProgramNumber, 5);
  l_gui.addButtonTextChange("Autonomous_Program_Selector", "Button_5", &m_displayProgramNames.at(5));

  l_gui.addScreen("Select_Confermation", 40, 20, 400, 200, popupBackground);
  l_gui.addButton("Select_Confermation", "Confirm", 20, 50, 140, 30);
  l_gui.addButtonScreenChange("Select_Confermation", "Confirm", "Home");
  l_gui.addButtonRunFunction("Select_Confermation", "Confirm", std::bind(&Autonomous::confirmAuto, this));

  return 0;
}

int Autonomous::startProgram(){
  if(m_selectedProgram != NULL){
    if(m_selectedProgram->m_programStart){
      m_selectedProgram->m_programStart = true;
    }
  }
  return 0;
}

int Autonomous::autoProgramDaemon(){
  if(m_selectedProgram != NULL){
    if(m_selectedProgram->m_programStart){
      m_selectedProgram->m_programStart = false;
      m_selectedProgram->m_programRunning = true;

      m_selectedProgram->m_baseIteration = 0;
      m_selectedProgram->m_armIteration = 0;
      m_selectedProgram->m_intakeIteration = 0;


      m_selectedProgram->m_baseTimer.resetTime();
      m_selectedProgram->m_armTimer.resetTime();
      m_selectedProgram->m_intakeTimer.resetTime();
    }

    if(m_selectedProgram->m_baseTimer.preformAction()){
        m_selectedProgram->m_baseTimer.addActionDelay(500);// Check Delay Time
        if(m_selectedProgram->m_baseEvents.size() > m_selectedProgram->m_baseIteration){
          //m_robot.basse set parameters
          m_selectedProgram->m_baseIteration++;
        }
    }

    if(m_selectedProgram->m_armTimer.preformAction()){
        m_selectedProgram->m_armTimer.addActionDelay(500);
        if(m_selectedProgram->m_armEvents.size() > m_selectedProgram->m_armIteration){
          //m_robot.arm set parameters
          m_selectedProgram->m_armIteration++;
        }
    }

    if(m_selectedProgram->m_intakeTimer.preformAction()){
        m_selectedProgram->m_intakeTimer.addActionDelay(500);
        if(m_selectedProgram->m_intakeEvents.size() > m_selectedProgram->m_intakeIteration){
          //m_robot.basse set parameters
          m_selectedProgram->m_intakeIteration++;
        }
    }

  }
  return 0;
}
