#include "robot/subsystems/armClass.hpp"
#include "robot/devices/motorClass.hpp"
#include "robotClass.hpp"
#include "robot/graphical/components/alertClass.hpp"

Arm::Arm(Robot& p_robot, const std::string p_name) : m_robot(p_robot){
  m_name = p_name;
}

int Arm::initialize(const std::string p_armMotor, const int p_port, const int p_limitLow, const int p_limitHigh, const bool p_reversed){
  m_reversed = p_reversed;
  m_limitLow = p_limitLow;
  m_limitHigh = p_limitHigh;
  m_totalPossibleDisplacement = p_limitHigh - m_limitHigh;
  if(Motor::findMotor(p_armMotor) == NULL)
    m_armMotor = new Motor(p_armMotor,p_port,pros::E_MOTOR_GEARSET_36, p_reversed);
   else
     m_armMotor = Motor::findMotor(p_armMotor);

  m_armMotor->setBrake(m_brakeMode);

  if(m_brakeMode == pros::E_MOTOR_BRAKE_COAST)
    m_brakeString = "Coast";
  else if(m_brakeMode == pros::E_MOTOR_BRAKE_BRAKE)
    m_brakeString = "Brake";
  else
    m_brakeString = "Hold";

  defineGUI("Home");

  return 0;
}

int Arm::setLimitLowPreset(const double p_speedUpPercent, const double p_speedDownPercent, const int p_intialVelocity, const int p_maximumVelocity){
  m_presetHigh.m_position = m_limitHigh;
  m_presetHigh.m_speedUpPercent = p_speedUpPercent;
  m_presetHigh.m_speedDownPercent = p_speedDownPercent;
  m_presetHigh.m_maximumVelocity = p_maximumVelocity;
  m_presetHigh.m_initialVelocity = p_intialVelocity;
  return 0;
}

int Arm::setLimitHighPreset(const double p_speedUpPercent, const double p_speedDownPercent, const int p_intialVelocity, const int p_maximumVelocity){
  m_presetLow.m_position = m_limitLow;
  m_presetLow.m_speedUpPercent = p_speedUpPercent;
  m_presetLow.m_speedDownPercent = p_speedDownPercent;
  m_presetLow.m_maximumVelocity = p_maximumVelocity;
  m_presetLow.m_initialVelocity = p_intialVelocity;
  return 0;
}

int Arm::setPreset1(const int p_position, const double p_speedUpPercent, const double p_speedDownPercent, const int p_intialVelocity, const int p_maximumVelocity){
  m_preset1.m_position = p_position;
  m_preset1.m_speedUpPercent = p_speedUpPercent;
  m_preset1.m_speedDownPercent = p_speedDownPercent;
  m_preset1.m_maximumVelocity = p_maximumVelocity;
  m_preset1.m_initialVelocity = p_intialVelocity;
  return 0;
}

int Arm::setPreset2(const int p_position, const double p_speedUpPercent, const double p_speedDownPercent, const int p_intialVelocity, const int p_maximumVelocity){
  m_preset2.m_position = p_position;
  m_preset2.m_speedUpPercent = p_speedUpPercent;
  m_preset2.m_speedDownPercent = p_speedDownPercent;
  m_preset2.m_maximumVelocity = p_maximumVelocity;
  m_preset2.m_initialVelocity = p_intialVelocity;
  return 0;
}

int Arm::setPreset3(const int p_position, const double p_speedUpPercent, const double p_speedDownPercent, const int p_intialVelocity, const int p_maximumVelocity){
  m_preset3.m_position = p_position;
  m_preset3.m_speedUpPercent = p_speedUpPercent;
  m_preset3.m_speedDownPercent = p_speedDownPercent;
  m_preset3.m_maximumVelocity = p_maximumVelocity;
  m_preset3.m_initialVelocity = p_intialVelocity;
  return 0;
}

int Arm::setPreset4(const int p_position, const double p_speedUpPercent, const double p_speedDownPercent, const int p_intialVelocity, const int p_maximumVelocity){
  m_preset4.m_position = p_position;
  m_preset4.m_speedUpPercent = p_speedUpPercent;
  m_preset4.m_speedDownPercent = p_speedDownPercent;
  m_preset4.m_maximumVelocity = p_maximumVelocity;
  m_preset4.m_initialVelocity = p_intialVelocity;
  return 0;
}

int Arm::setVelocityMaximumCoefficent(const int p_coefficeint){
  m_velocityMaximumCoefficent = p_coefficeint;
  return 0;
}

int Arm::setBrake(const pros::motor_brake_mode_e p_brakeMode){
  m_brakeMode = p_brakeMode;
  if(m_brakeMode == pros::E_MOTOR_BRAKE_COAST)
    m_brakeString = "Coast";
  else if(m_brakeMode == pros::E_MOTOR_BRAKE_BRAKE)
    m_brakeString = "Brake";
  else
    m_brakeString = "Hold";
  return 0;
}

int Arm::setMaximumVelcoity(const int p_velocityMax){
  m_velcoityMaximum = p_velocityMax;
  return 0;
}

/* GO TO FUNCTION */
int Arm::goToVelocity(const int p_velocity){
  if(!m_movementInProgess){
    m_mode = MANIPULATOR_VELOCITY_DEPENDENT;
    m_modeString = "Velocity";
    int l_direction = 0;
    if(p_velocity !=0)
      l_direction = (double)abs(p_velocity)/(double)p_velocity;

    if(abs(p_velocity) > m_velcoityMaximum)
      m_desiredVelcoity = m_velcoityMaximum * l_direction;
    else
      m_desiredVelcoity = p_velocity;
  }
  return 0;
}

int Arm::goToPosition(const int p_position, const double p_speedUpPercent, const double p_speedDownPercent, const int p_intialVelocity, const int p_maximumVelocity){
  m_mode = MANIPULATOR_ENCODER_DEPENDENT;
  m_modeString = "Encoder";
  m_speedUpPercent = p_speedUpPercent;
  m_speedDownPercent = p_speedDownPercent;
  m_velcoityMaximum = p_maximumVelocity;
  m_movementIntialVelocity = p_intialVelocity;

  if(p_position > m_limitHigh){
    m_endPosition = p_position;
  }
  else if(p_position < m_limitLow){
    m_endPosition = p_position;
  }
  else{
    m_endPosition = p_position;
  }

  /*Set Varibles*/
  m_startPosition = m_armMotor->getRotation();
  m_movementDisplacement = m_endPosition-m_startPosition;

  /*Calculate Direction*/
  if(m_movementDisplacement != 0)
    m_movementDirection = m_movementDisplacement/abs(m_movementDisplacement);
  else
    m_movementDirection = 0;

  m_movementDisplacement = abs(m_movementDisplacement);

  /*Calculate Safe Movement Maximum Velocity*/
  m_movementMaximumVelocity = m_velcoityMaximum * m_velocityMaximumCoefficent * ((double)m_movementDisplacement/(double)m_totalPossibleDisplacement);
  if(abs(m_movementMaximumVelocity) > m_velcoityMaximum)
    m_movementMaximumVelocity = m_velcoityMaximum;

  /*Calculate Speed Up Varibles*/
  m_speedUpDisplacement = (double)m_movementDisplacement*m_speedUpPercent;
  m_speedUpSlope = (log((((double)m_movementMaximumVelocity + 1)/m_movementMaximumVelocity)-1))/(m_speedUpDisplacement - (m_speedUpDisplacement/2));

  /*Calculate Spped Down Varibles*/
  m_speedDownDisplacement = m_movementDisplacement * m_speedDownPercent;
  m_speedDownSlope = (log((((double)m_movementMaximumVelocity + 1)/m_movementMaximumVelocity)-1))/(m_speedDownDisplacement - (m_speedDownDisplacement/2));

  m_movementInProgess = true;
  return 0;
}

int Arm::goToLimitLow(){
  goToPosition(m_limitLow, m_presetLow.m_speedUpPercent, m_presetLow.m_speedDownPercent, m_presetLow.m_initialVelocity, m_presetLow.m_maximumVelocity);
  return 0;
}
int Arm::goToLimitHigh(){
  goToPosition(m_limitHigh, m_presetHigh.m_speedUpPercent, m_presetHigh.m_speedDownPercent, m_presetHigh.m_initialVelocity, m_presetHigh.m_maximumVelocity);
  return 0;
}

int Arm::goToPreset1(){
  goToPosition(m_preset1.m_position, m_preset1.m_speedUpPercent, m_preset1.m_speedDownPercent, m_preset1.m_initialVelocity, m_preset1.m_maximumVelocity);
  return 0;
}
int Arm::goToPreset2(){
  goToPosition(m_preset2.m_position, m_preset2.m_speedUpPercent, m_preset2.m_speedDownPercent, m_preset2.m_initialVelocity, m_preset2.m_maximumVelocity);
  return 0;
}
int Arm::goToPreset3(){
  goToPosition(m_preset3.m_position, m_preset3.m_speedUpPercent, m_preset3.m_speedDownPercent, m_preset3.m_initialVelocity, m_preset3.m_maximumVelocity);
  return 0;
}
int Arm::goToPreset4(){
  goToPosition(m_preset4.m_position, m_preset4.m_speedUpPercent, m_preset4.m_speedDownPercent, m_preset4.m_initialVelocity, m_preset4.m_maximumVelocity);
  return 0;
}

int Arm::task(){
  m_currentPosition = m_armMotor->getRotation();
  if(m_robot.getRobotMode() == ROBOT_DISABLED){
    m_armMotor->setVelocity(0);
    m_armMotor->setBrake(m_brakeMode);
    m_modeString = "Disabled";
    m_mode = MANIPULATOR_DISABLED;
  }
  else if(m_robot.getRobotMode() == ROBOT_OPERATER || m_robot.getRobotMode() == ROBOT_AUTO){
    if(m_mode == MANIPULATOR_VELOCITY_DEPENDENT){
      if(m_armMotor->getRotation() <= m_limitLow && m_desiredVelcoity/abs(m_desiredVelcoity) == -1)
        m_desiredVelcoity = 0;
      else if(m_armMotor->getRotation() >= m_limitHigh && m_desiredVelcoity/abs(m_desiredVelcoity) == 1)
        m_desiredVelcoity = 0;
      m_armMotor->setVelocity(m_desiredVelcoity);
      m_armMotor->setBrake(m_brakeMode);
      m_movementString = "User Based";
      m_modeString = "Velocity Dependent";
      m_mode = MANIPULATOR_VELOCITY_DEPENDENT;
    }
    else if(m_mode == MANIPULATOR_ENCODER_DEPENDENT){
      if(abs(m_currentPosition-m_startPosition) < fabs(m_speedUpDisplacement)){// Withen Speed Up
        m_desiredVelcoity = (m_movementMaximumVelocity + 1)/(1 + pow(M_E,(m_speedUpSlope*fabs(m_currentPosition-((double)m_speedUpDisplacement/2.0)))));
        if(m_desiredVelcoity < m_movementIntialVelocity)
          m_desiredVelcoity = m_movementIntialVelocity;
        m_armMotor->setVelocity(m_desiredVelcoity * m_movementDirection);
        m_movementString = "Speed Up";
      }
      else if(abs(m_endPosition-m_currentPosition) < fabs(m_speedDownDisplacement)){// Withen Slow Down
        m_desiredVelcoity = (m_movementMaximumVelocity + 1)/(1 + pow(M_E,(m_speedDownSlope*fabs((m_endPosition-m_currentPosition)-((double)m_speedUpDisplacement/2.0)))));
        m_armMotor->setVelocity(m_desiredVelcoity * m_movementDirection);
        m_movementString = "Speed Down";
      }
      else{// Coast
        m_armMotor->setVelocity(m_movementMaximumVelocity * m_movementDirection);
        m_movementString = "Coast";
      }

      if((m_movementDirection == 1 && m_endPosition-m_currentPosition <= 0) || (m_movementDirection == -1 && m_endPosition-m_currentPosition >= 0)){
        m_armMotor->setVelocity(0);
        m_movementInProgess = false;
        m_movementString = "User Based";
        m_mode = MANIPULATOR_DISABLED;
      }
      m_armMotor->setBrake(m_brakeMode);
      m_modeString = "Encoder Dependent";
      m_mode = MANIPULATOR_ENCODER_DEPENDENT;
    }
  }

  return 0;
}

int Arm::defineGUI(const std::string p_returnScreen){
  auto &l_gui = m_robot.getGUI();
  m_armMotor->defineGUI(m_robot.getGUI(), m_name);

  l_gui.addScreen(m_name);
  l_gui.addLabel(m_name, 200, 10, redText, m_name);
  l_gui.addRectangle(m_name, 0, 0, 480, 40, whiteText);

  l_gui.addLabel(m_name, 20, 50, whiteText, "Current Position: %d Deg   ", &m_currentPosition);
  l_gui.addLabel(m_name, 20, 80, whiteText, "Desired Velocity: %d RPM   ", &m_desiredVelcoity);
  l_gui.addLabel(m_name, 20, 110, whiteText, "Arm Mode: %s", &m_modeString);
  l_gui.addLabel(m_name, 20, 140, whiteText, "Brake Mode: %s", &m_brakeString);
  l_gui.addLabel(m_name, 20, 170, whiteText, "Reversed: %b", &m_reversed);

  l_gui.addButton(m_name, m_name+" Motor", 250, 150, 150, 30);
  l_gui.addButtonScreenChange(m_name, m_name+" Motor", m_armMotor->getName());

  l_gui.addButton(m_name, "Next", 250, 200, 150, 30);
  l_gui.addButtonScreenChange(m_name, "Next", m_name+"`");

  l_gui.addButton(m_name, "Back", 40, 200, 150, 30);
  l_gui.addButtonScreenChange(m_name, "Back", "Subsystems");


  /*              Second Screen             */
  l_gui.addScreen(m_name+"`");
  l_gui.addLabel(m_name+"`", 200, 10, redText, m_name + "Automation");
  l_gui.addRectangle(m_name+"`", 0, 0, 480, 40, whiteText);

  l_gui.addLabel(m_name+"`", 20, 50, whiteText, "In Progess: %b", &m_movementInProgess);
  l_gui.addLabel(m_name+"`", 20, 75, whiteText, "Start Pos: %d Deg\t", &m_startPosition);
  l_gui.addLabel(m_name+"`", 20, 100, whiteText, "Current Pos: %d Deg\t", &m_currentPosition);
  l_gui.addLabel(m_name+"`", 20, 125, whiteText, "End Pos: %d Deg\t", &m_endPosition);
  l_gui.addLabel(m_name+"`", 20, 150, whiteText, "Direction: %d \t", &m_movementDirection);
  l_gui.addLabel(m_name+"`", 20, 175, whiteText, "Desired Vel: %d \t", &m_desiredVelcoity);

  l_gui.addLabel(m_name+"`", 220, 50, whiteText, "Displacement: %d \t", &m_movementDisplacement);
  l_gui.addLabel(m_name+"`", 220, 75, whiteText, "Up Displacement: %f Deg\t", &m_speedUpDisplacement);
  l_gui.addLabel(m_name+"`", 220, 100, whiteText, "Up Slope: %f Deg\t", &m_speedUpSlope);
  l_gui.addLabel(m_name+"`", 220, 125, whiteText, "Down Displacement: %f Deg\t", &m_speedDownDisplacement);
  l_gui.addLabel(m_name+"`", 220, 150, whiteText, "Down Slope: %f \t", &m_speedDownSlope);
  l_gui.addLabel(m_name+"`", 220, 175, whiteText, "Mode: %s", &m_movementString);

  l_gui.addButton(m_name+"`", "Previous", 100, 200, 150, 30);
  l_gui.addButtonScreenChange(m_name+"`", "Previous", m_name);
  return 0;
}
