#include "robot/devices/motorClass.hpp"
#include "robot/graphical/GUIClass.hpp"
#include "robot/devices/externalFileClass.hpp"

ExternalFile Motor::s_config("Motor_Config.txt");
std::vector<Motor*> Motor::s_motorArray;

Motor::Motor(const std::string p_name, const short p_input, const pros::motor_gearset_e_t p_type, const bool p_reverse){
  m_name = p_name;
  if(s_config.varExist(m_name+"_port")){
    m_port = s_config.readInt(m_name+"_port");
  }
  else{
    m_port = p_input;
    s_config.storeInt(m_name+"_port", m_port);
  }

  if(s_config.varExist(m_name+"_gearset")){
    m_motorGearSet = (pros::motor_gearset_e_t)s_config.readInt(m_name+"_gearset");
  }
  else{
    m_motorGearSet = p_type;
    s_config.storeInt(m_name+ "_gearset", m_motorGearSet);
  }

  if(s_config.varExist(m_name+"_reversed")){
    m_reversed = s_config.readBool(m_name+"_reversed");
  }
  else{
    m_reversed = p_reverse;
    s_config.storeBool(m_name+"_reversed", m_reversed);
  }

  m_internalPID = true;

  pros::c::motor_set_reversed(m_port, m_reversed);
  pros::c::motor_set_gearing(m_port, m_motorGearSet);
  pros::c::motor_set_brake_mode(m_port, pros::E_MOTOR_BRAKE_COAST);
  pros::c::motor_set_encoder_units(m_port, pros::E_MOTOR_ENCODER_DEGREES);

  s_motorArray.push_back(this);
}

int Motor::defineGUI(GraphicalInterface& p_gui, const std::string p_returnScreen){
  setStrings();
  p_gui.addScreen(m_name);
  p_gui.addLabel(m_name, 200, 10, redText, m_name);
  p_gui.addRectangle(m_name, 0, 0, 480, 40, whiteText);

  p_gui.addLabel(m_name, 20, 50, whiteText, "Desired Velocity: %d", &m_desiredVelocity);
  p_gui.addLabel(m_name, 20, 80, whiteText, "Actual Velocity: %d", (std::function<int()>)std::bind(&Motor::getVelocity, this));
  p_gui.addLabel(m_name, 20, 110, whiteText, "Position: %d Deg", (std::function<int()>)std::bind(&Motor::getRotation, this));
  p_gui.addLabel(m_name, 20, 140, whiteText, "Reversed: %b", &m_reversed);
  p_gui.addLabel(m_name, 20, 170, whiteText, "Motor Gearset: %s", &m_gearSetString);

  p_gui.addLabel(m_name, 260, 50, whiteText, "Desired Voltage: %d", &m_desiredVoltage);
  p_gui.addLabel(m_name, 260, 80, whiteText, "Actual Voltage: %d", (std::function<int()>)std::bind(&Motor::getVoltage, this));
  p_gui.addLabel(m_name, 260, 110, whiteText, "Tempature: %d C", (std::function<int()>)std::bind(&Motor::getTempature, this));
  p_gui.addLabel(m_name, 260, 140, whiteText, "Internal PID: %b", &m_internalPID);
  p_gui.addLabel(m_name, 260, 170, whiteText, "Brake Mode: %s", &m_brakeString);

  p_gui.addButton(m_name, "Go Back", 160, 200, 150, 20);
  p_gui.addButtonScreenChange(m_name, "Go Back", p_returnScreen);

  p_gui.addRelationship(m_name, (std::function<bool()>)std::bind(&Motor::isConnected, this), "No_Device", true);
  return 0;
}

void Motor::setVelocity(const int p_velocity){
  pros::c::motor_move_velocity(m_port, p_velocity);
  m_desiredVelocity = p_velocity;
  m_internalPID = true;
  m_desiredVoltage = 0;
}

void Motor::setVoltage(const int p_power){
  pros::c::motor_move_voltage(m_port, p_power);
  m_desiredVoltage = p_power;
  m_internalPID = false;
  m_desiredVelocity = 0;
}

void Motor::setBrake(const pros::motor_brake_mode_e_t p_power){
  pros::c::motor_set_brake_mode(m_port, p_power);
  m_brakeMode = p_power;
  setStrings();
}

void Motor::resetRotation(){
  pros::c::motor_tare_position(m_port);
}

bool Motor::isConnected(){
  return !(getTempature() == 2147483647);
}

int Motor::getVelocity(){
  return pros::c::motor_get_actual_velocity(m_port);
}

int Motor::getVoltage(){
  return pros::c::motor_get_voltage(m_port);
}

int Motor::getRotation(){
  return pros::c::motor_get_position(m_port);
}

int Motor::getTempature(){
  return pros::c::motor_get_temperature(m_port);
}

int Motor::setPort(const int p_port){
  m_port = p_port;
  s_config.storeInt(m_name+"_port", m_port);
  return 0;
}

int Motor::setReverse(const bool p_reverse){
  m_reversed = p_reverse;
  pros::c::motor_set_reversed(m_port, m_reversed);
  s_config.storeInt(m_name+"_reversed", p_reverse);
  return 0;
}

int Motor::setGearing(const int p_type){
  m_motorGearSet = (pros::motor_gearset_e_t)p_type;
  s_config.storeInt(m_name+ "_gearset", m_motorGearSet);
  pros::c::motor_set_gearing(m_port, m_motorGearSet);
  setStrings();
  return 0;
}

std::string Motor::getName(){
  return m_name;
}


void Motor::setStrings(){
  if(m_motorGearSet == pros::E_MOTOR_GEARSET_36)
    m_gearSetString = "100 RPM";
  else if(m_motorGearSet == pros::E_MOTOR_GEARSET_18)
    m_gearSetString = "200 RPM";
  else
    m_gearSetString = "600 RPM";

  if(m_brakeMode == pros::E_MOTOR_BRAKE_COAST)
    m_brakeString = "Coast";
  else if(m_brakeMode == pros::E_MOTOR_BRAKE_BRAKE)
    m_brakeString = "Brake";
  else
    m_brakeString = "Hold";
}

Motor* Motor::findMotor(std::string p_name){
  for(int x = 0; x < s_motorArray.size(); x++)
    if(s_motorArray.at(x)->m_name == p_name)
      return s_motorArray.at(x);
  return NULL;
}

Motor* Motor::findMotor(const std::string p_name, const short p_input, const pros::motor_gearset_e_t p_type, const bool p_reverse){
  for(int x = 0; x < s_motorArray.size(); x++)
    if(s_motorArray.at(x)->m_name == p_name)
      return s_motorArray.at(x);
  return new Motor(p_name, p_input, p_type, p_reverse);
}
