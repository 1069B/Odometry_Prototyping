#include "robot/devices/controller/controllerClass.hpp"
#include "robot/graphical/GUIClass.hpp"

Controller::Controller(const pros::controller_id_e_t p_type):
  ButtonL1(ControlBtn(p_type, pros::E_CONTROLLER_DIGITAL_L1)),
  ButtonL2(ControlBtn(p_type, pros::E_CONTROLLER_DIGITAL_L2)),
  ButtonR1(ControlBtn(p_type, pros::E_CONTROLLER_DIGITAL_R1)),
  ButtonR2(ControlBtn(p_type, pros::E_CONTROLLER_DIGITAL_R2)),
  ButtonUp(ControlBtn(p_type, pros::E_CONTROLLER_DIGITAL_UP)),
  ButtonDown(ControlBtn(p_type, pros::E_CONTROLLER_DIGITAL_DOWN)),
  ButtonLeft(ControlBtn(p_type, pros::E_CONTROLLER_DIGITAL_LEFT)),
  ButtonRight(ControlBtn(p_type, pros::E_CONTROLLER_DIGITAL_RIGHT)),
  ButtonX(ControlBtn(p_type, pros::E_CONTROLLER_DIGITAL_X)),
  ButtonB(ControlBtn(p_type, pros::E_CONTROLLER_DIGITAL_B)),
  ButtonY(ControlBtn(p_type, pros::E_CONTROLLER_DIGITAL_Y)),
  ButtonA(ControlBtn(p_type, pros::E_CONTROLLER_DIGITAL_A)),
  Axis1(ControlAxis(p_type, pros::E_CONTROLLER_ANALOG_RIGHT_X)),
  Axis2(ControlAxis(p_type, pros::E_CONTROLLER_ANALOG_RIGHT_Y)),
  Axis3(ControlAxis(p_type, pros::E_CONTROLLER_ANALOG_LEFT_Y)),
  Axis4(ControlAxis(p_type, pros::E_CONTROLLER_ANALOG_LEFT_X)){
  if(p_type == pros::E_CONTROLLER_MASTER)
    m_name = "Main Controller";
  else
    m_name = "Partner Controller";
  m_controllerType = p_type;
}

int Controller::defineGUI(GraphicalInterface& p_gui, std::string p_returnScreen){
  p_gui.addScreen(m_name);
  p_gui.addLabel(m_name, 75, 10, redText, m_name);
  p_gui.addLabel(m_name, 300, 10, redText, "Battery: %d%", (std::function<int()>) std::bind(&Controller::getBatteryCapacity, this));
  p_gui.addRectangle(m_name, 0, 0, 480, 40, whiteText);
  // Col 1
  p_gui.addLabel(m_name, 10, 45, whiteText, "Button L1: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonL1));
  p_gui.addLabel(m_name, 10, 65, whiteText, "Button L2: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonL2));
  p_gui.addLabel(m_name, 10, 85, whiteText, "Button Up: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonUp));
  p_gui.addLabel(m_name, 10, 105, whiteText, "Button Left: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonLeft));
  p_gui.addLabel(m_name, 10, 125, whiteText, "Button Right: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonRight));
  p_gui.addLabel(m_name, 10, 145, whiteText, "Button Down: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonDown));
  // Col 2
  p_gui.addLabel(m_name, 200, 45, whiteText, "Button R1: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonR1));
  p_gui.addLabel(m_name, 200, 65, whiteText, "Button R2: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonR2));
  p_gui.addLabel(m_name, 200, 85, whiteText, "Button X: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonX));
  p_gui.addLabel(m_name, 200, 105, whiteText, "Button Y: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonY));
  p_gui.addLabel(m_name, 200, 125, whiteText, "Button A: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonA));
  p_gui.addLabel(m_name, 200, 145, whiteText, "Button B: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonB));
  // Col 3
  p_gui.addLabel(m_name, 370, 45, whiteText, "Axis 1: %d", (std::function<int()>) std::bind(&ControlAxis::getPercent, &Axis1));
  p_gui.addLabel(m_name, 370, 65, whiteText, "Axis 2: %d", (std::function<int()>) std::bind(&ControlAxis::getPercent, &Axis2));
  p_gui.addLabel(m_name, 370, 85, whiteText, "Axis 3: %d", (std::function<int()>) std::bind(&ControlAxis::getPercent, &Axis3));
  p_gui.addLabel(m_name, 370, 105, whiteText, "Axis 4: %d", (std::function<int()>) std::bind(&ControlAxis::getPercent, &Axis4));
  //Bottem
  p_gui.addButton(m_name, "Go Back", 160, 200, 150, 20);
  p_gui.addButtonScreenChange(m_name, "Go Back", p_returnScreen);

  p_gui.addRelationship(m_name, (std::function<bool()>)std::bind(&Controller::isConnected, this), "No_Device", true);
  return 0;
}

void Controller::clear(){
  for(int x = 0; x < 3; x++){
    setText(x, 0, "          ");
  }
}

void Controller::clearLine(const int p_line){
  setText(p_line, 0, "          ");
  pros::delay(50);
}

int Controller::getBatteryCapacity(){
  return pros::c::controller_get_battery_capacity(m_controllerType);
}

int Controller::getBatteryLevel(){
  return pros::c::controller_get_battery_level(m_controllerType);
}

bool Controller::isConnected(){
  return pros::c::controller_is_connected(m_controllerType);
}

void Controller::print(const int p_row, const int p_col, const char* p_fmt...){
  std::string sum = "";
  va_list args;
  va_start(args, p_fmt);
  while(*p_fmt != '\0') {
  	if(*p_fmt == '%'){
  		++p_fmt;
  		if(*p_fmt == 'd'){
  			sum += std::to_string(va_arg(args, int));
        ++p_fmt;
  		}
  		else if(*p_fmt == 'f'){
        sum += std::to_string(va_arg(args, double));
        ++p_fmt;
  		}
  		else if(*p_fmt == 'c'){
        sum += (char)(va_arg(args, int));
        ++p_fmt;
  		}
  		else{
	    	++p_fmt;
	    }
  	}
  	else{
      sum += *p_fmt;
  		++p_fmt;
  	}
  }
  va_end(args);
  int n = sum.length();
  char char_array[n + 1];
  strcpy(char_array, sum.c_str());
  pros::c::controller_set_text(m_controllerType, p_row, p_col, char_array);
  pros::delay(50);
}

void Controller::rumble(const char* p_fmt){
  pros::c::controller_rumble(m_controllerType, p_fmt);
  pros::delay(50);
}

void Controller::setText(const int p_row, const int p_col, const char* p_fmt){
  pros::c::controller_set_text(m_controllerType, p_row, p_col, p_fmt);
  pros::delay(50);
}

void Controller::callBackCheck(){
  ButtonL1.checkCallBack();
  ButtonL2.checkCallBack();
  ButtonR1.checkCallBack();
  ButtonR2.checkCallBack();
  ButtonUp.checkCallBack();
  ButtonDown.checkCallBack();
  ButtonLeft.checkCallBack();
  ButtonRight.checkCallBack();
  ButtonX.checkCallBack();
  ButtonB.checkCallBack();
  ButtonY.checkCallBack();
  ButtonA.checkCallBack();
}
