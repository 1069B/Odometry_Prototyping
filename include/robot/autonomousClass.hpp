#include "robot/varibleDecleration.hpp"
#include "robot/devices/timerClass.hpp"

#ifndef AUTONOMOUSCLASS_H
#define AUTONOMOUSCLASS_H

struct AutoBaseEvent{
public:
  int m_actionDelay = 0;
  double m_desiredXPosition = 0;
  double m_desiredYPosition = 0;
  double m_desiredOrientation = 0;
  short m_maximumVelocity = 0;
  pros::motor_brake_mode_e m_endBrakeMode = pros::E_MOTOR_BRAKE_COAST;
  Base &m_base;

  AutoBaseEvent(Base &p_base, const int p_delay, const double p_desiredXPosition, const double p_desiredYPosition, const double p_desiredOrientation, const short p_maximumVelocity, const pros::motor_brake_mode_e p_endBrakeMode);
};

struct AutoArmEvent{
public:
  int m_actionDelay = 0;
  double m_desiredPosition = 0;
  short m_maximumVelocity = 0;
  pros::motor_brake_mode_e m_endBrakeMode = pros::E_MOTOR_BRAKE_COAST;
  Arm &m_arm;

  AutoArmEvent(Arm &p_arm, const int p_delay, const double p_desiredPosition, const short p_maximumVelocity, const pros::motor_brake_mode_e p_endBrakeMode);
};

struct AutoIntakeEvent{
public:
  int m_actionDelay = 0;
  int m_desiredDuration = 0;
  double m_desiredPosition = 0;
  short m_maximumVelocity = 0;
  bool m_duration = true;
  pros::motor_brake_mode_e m_endBrakeMode = pros::E_MOTOR_BRAKE_COAST;
  Intake &m_intake;

  AutoIntakeEvent(Intake &p_intake, const int p_delay, const double p_desiredPosition, const short p_maximumVelocity, const pros::motor_brake_mode_e p_endBrakeMode);
  AutoIntakeEvent(Intake &p_intake, const int p_delay, const int m_desiredDuration, const short p_maximumVelocity, const pros::motor_brake_mode_e p_endBrakeMode);
};

class AutoProgram{
public:
  std::string m_name;
  AutonomousSide m_autoSide;
  int m_programNumber;

  Timer m_autoTimer;
  bool m_programStart = false;
  bool m_programRunning = false;

  std::vector<AutoBaseEvent> m_baseEvents;
  int m_baseIteration = 0;

  std::vector<AutoArmEvent> m_armEvents;
  int m_armIteration = 0;

  std::vector<AutoIntakeEvent> m_intakeEvents;
  int m_intakeIteration = 0;

  AutoProgram(const std::string p_name, const AutonomousSide p_autoSide, const int p_programNumber);

  std::string getName();

  AutonomousSide getAutoSide();

  int getProgramNumber();

  int addBaseEvent(AutoBaseEvent& p_event);

  int addArmEvent(AutoArmEvent& p_event);

  int addIntakeEvent(AutoIntakeEvent& p_event);
};

class Autonomous{
private:
  Robot& m_robot;
  std::string m_name = "Autonomous";
  int m_selectedProgramNumber = INT_MAX;
  int m_autoSide = AUTO_NONE;
  AutoProgram *m_selectedProgram = NULL;

  std::vector<std::string> m_blueProgramNames;
  std::vector<AutoProgram*> m_bluePrograms;

  std::vector<std::string> m_redProgramNames;
  std::vector<AutoProgram*> m_redPrograms;

  std::vector<std::string> m_skillsProgramNames;
  std::vector<AutoProgram*> m_skillsPrograms;

  std::vector<std::string> m_displayProgramNames;

  int displayRedAuto();
  int displayBlueAuto();
  int displaySkillsAuto();

  int confirmAuto();

public:
  Autonomous(Robot& p_robot);

  int addProgram(AutoProgram& p_program);

  AutoProgram* findProgram(const int p_number, const AutonomousSide p_autoSide);

  int defineGUI(const std::string p_returnScreenID);

  int autoProgramDaemon();

  int startProgram();

};

#endif // AUTONOMOUSCLASS_H
