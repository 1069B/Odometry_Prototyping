#include "robot/devices/encoderClass.hpp"
#include "robot/devices/externalFileClass.hpp"
#include "robotClass.hpp"


ExternalFile Encoder::s_config("Encoder_Config.txt");
ExternalFile Encoder::s_debug("Encoder_Debug.txt");

std::vector<Encoder*> Encoder::s_encoderArray;

Encoder::Encoder(Robot& p_robot, const std::string p_name ,const int p_port, const bool p_reverse):m_robot(p_robot){
  m_name = p_name;
  if(s_config.varExist(m_name+"_port")){
    m_port = s_config.readInt(m_name+"_port");
  }
  else{
    m_port = p_port;
    s_config.storeInt(m_name+"_port", m_port);
  }

  if(s_config.varExist(m_name+"_reversed")){
    m_reversed = s_config.readBool(m_name+"_reversed");
  }
  else{
    m_reversed = p_reverse;
    s_config.storeBool(m_name+"_reversed", m_reversed);
  }
  pros::c::adi_encoder_init(m_port, m_port+1, m_reversed);
  s_encoderArray.push_back(this);

  m_avgVelocity.resize(4);

  m_robot.getTaskScheduler().addTask(m_name, std::bind(&Encoder::task, this), 25, TASK_ALWAYS);
}

int Encoder::isConnected(){
  // if(getRotation() == 2147483647)// Needs to change detection methoud
  //   return true;
  return pros::c::adi_port_get_value(m_port);
}

int Encoder::getRotation(){
  return m_rotation;
}

int Encoder::getDisplacment(){
  return m_displacement;
}

int Encoder::resetRotation(){
  m_zeroPosition = pros::c::adi_encoder_get(m_port);
  return 0;
}

double Encoder::getVelocity(){
  return m_velocity;
}

int Encoder::getDirection(){
  return getVelocity()/fabs(getVelocity());
}

int Encoder::setPort(const int p_port){
  m_port = p_port;
  s_config.storeInt(m_name+"_port", m_port);
  pros::c::adi_encoder_init(m_port, m_port+1, m_reversed);
  return 0;
}

int Encoder::setReverse(const bool p_reverse){
  m_reversed = p_reverse;
  pros::c::adi_encoder_init(m_port, m_port+1, m_reversed);
  s_config.storeInt(m_name+"_reversed", p_reverse);
  return 0;
}

std::string Encoder::getName(){
  return m_name;
}

int Encoder::defineGUI(GraphicalInterface& p_gui, const std::string p_returnScreen){
  p_gui.addScreen(m_name);
  p_gui.addLabel(m_name, 200, 10, redText, m_name);
  p_gui.addRectangle(m_name, 0, 0, 480, 40, whiteText);

  p_gui.addLabel(m_name, 20, 50, whiteText, "Zero Position: %d", &m_zeroPosition);
  p_gui.addLabel(m_name, 20, 80, whiteText, "Rotation: %d Deg", &m_rotation);
  p_gui.addLabel(m_name, 20, 110, whiteText, "Displacement %f cm", &m_displacement);
  p_gui.addLabel(m_name, 20, 140, whiteText, "Velocity: %f cm/s", &m_velocity);
  p_gui.addLabel(m_name, 20, 170, whiteText, "Calculated Displacement: %f cm", &m_calculatedDisplacement);

  p_gui.addButton(m_name, "Go Back", 160, 200, 150, 20);
  p_gui.addButtonScreenChange(m_name, "Go Back", p_returnScreen);

  //p_gui.addRelationship(m_name, (std::function<bool()>)std::bind(&Encoder::isConnected, this), "No_Device", false);
  return 0;
}

int Encoder::task(){
  int l_timerChange = m_timer.lapTime();
  m_rotation = pros::c::adi_encoder_get(m_port);// Calculates the Rotation

  m_displacement = ((double)m_rotation / 360.00) * m_wheelCircumference;

  m_velocity = (m_displacement - m_previousDisplacement) / (l_timerChange / 1000.00);
  m_previousDisplacement = m_displacement;

  m_calculatedDisplacement += m_velocity * l_timerChange / 1000.00;

  return 0;
}

Encoder* Encoder::findEncoder(const std::string p_name){
  for(int x = 0; x < s_encoderArray.size(); x++)
    if(s_encoderArray.at(x)->m_name == p_name)
      return s_encoderArray.at(x);
  return NULL;
}

Encoder* Encoder::findEncoder(const short p_port){
  for(int x = 0; x < s_encoderArray.size(); x++)
    if(s_encoderArray.at(x)->m_port == p_port)
      return s_encoderArray.at(x);
  return NULL;
}
