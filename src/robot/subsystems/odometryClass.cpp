#include "robot/subsystems/odometryClass.hpp"
#include "robot/devices/encoderClass.hpp"
#include "robot/graphical/components/alertClass.hpp"
#include "robotClass.hpp"

Odometry::Odometry(Robot& p_robot, const std::string p_leftEncoder, const std::string p_rightEncoder, const std::string p_centerEncoder):
m_robot(p_robot),
m_orientationTimer("Odometry Orientation", false),
m_OrientationDebug("Orientation_Debugging.csv", true){//m_translationDebug("Translation_Debugging.csv", true),
  if(Encoder::findEncoder(p_leftEncoder) == NULL)
    m_leftEncoder = new Encoder(m_robot, p_leftEncoder, 1, false);
  else
    m_leftEncoder = Encoder::findEncoder(p_leftEncoder);

  if(Encoder::findEncoder(p_rightEncoder) == NULL)
    m_rightEncoder = new Encoder(m_robot, p_rightEncoder, 3, true);
  else
    m_rightEncoder = Encoder::findEncoder(p_rightEncoder);

  if(Encoder::findEncoder(p_centerEncoder) == NULL)
    m_centerEncoder = new Encoder(m_robot, p_centerEncoder, 5, true);
  else
    m_centerEncoder = Encoder::findEncoder(p_centerEncoder);

  m_robot.getTaskScheduler().addTask("Odometry", std::bind(&Odometry::task, this), 4, TASK_ALWAYS);

  m_OrientationDebug.addLine("Time:, Cycle Duration:, LTW Vel:, RTW Vel:, Orientation:");
}

double Odometry::getRadiusLeft(const double p_leftVelocity, const double p_rightVelocity){
  if(p_leftVelocity == 0 || (int)p_leftVelocity == (int)p_rightVelocity){
   m_radiusLeft = 0;
   return m_radiusLeft;
 }
 else if(p_rightVelocity == 0){
   m_radiusLeft = g_trackingWheelDistance;
   return m_radiusLeft;
 }
 else{
   m_radiusLeft = fabs(g_trackingWheelDistance/(p_rightVelocity/p_leftVelocity-1));
   return m_radiusLeft;
 }
 return 404;
}

double Odometry::getRadiusRight(const double p_leftVelocity, const double p_rightVelocity){
  if(p_rightVelocity == 0 || (int)p_leftVelocity == (int)p_rightVelocity){
    m_radiusRight = 0;
    return m_radiusRight;
  }
  else if(p_leftVelocity == 0){
    m_radiusRight = g_trackingWheelDistance;
    return m_radiusRight;
  }
  else{
    m_radiusRight = fabs(g_trackingWheelDistance/(p_leftVelocity/p_rightVelocity-1));
    return m_radiusRight;
  }
  return 404;
}

double Odometry::getOrientation(){
  return m_absoluteOrientation;
}

double Odometry::setOrientation(const double p_orientation){
  m_absoluteOrientation = p_orientation;
  return 0;
}

double Odometry::getXposition(){
  return m_xPosition;
}

double Odometry::getXVelocity(){
  return m_xVelocity;
}

double Odometry::setXposition(const double p_xPosition){
  m_xPosition = p_xPosition;
  return 0;
}

double Odometry::getYposistion(){
  return m_yPosition;
}

double Odometry::getYVelocity(){
  return m_yVelocity;
}

double Odometry::getOrientationVelocity(){
  return m_orientationVelocity;
}

double Odometry::setYposition(const double p_yPosition){
  m_yPosition = p_yPosition;
  return 0;
}

double Odometry::orientationConverter(const double p_angle){
  double l_orientation = 0;
  if(0 <= p_angle && p_angle < 360)// Detects if Angle is withen desired bounds
    l_orientation = p_angle;
  else{// If not calculate angle
    if(fabs(p_angle) / p_angle == -1)// Negative Angle
      l_orientation = std::fmod(p_angle, 360) + 360;
    else
      l_orientation = std::fmod(p_angle, 360);
  }
  return l_orientation;
}

int Odometry::calculateDirection(const int p_value){
  if(p_value !=0)
    return abs(p_value)/p_value;
  return 0;
}
int Odometry::calculateDirection(const double p_value){
  if(p_value !=0)
    return fabs(p_value)/p_value;
  return 0;
}

int Odometry::calculatePosition(){

  return 0;
}

int Odometry::calculateOrientation(){
    m_velocityLeft = m_leftEncoder->getVelocity();
    m_velocityRight = m_rightEncoder->getVelocity();
    m_radiusLeft = getRadiusLeft(m_velocityLeft, m_velocityRight);
    m_radiusRight = getRadiusRight(m_velocityLeft, m_velocityRight);

    m_timeChange = m_orientationTimer.lapTime()/1000.0;

    if(fabs(m_radiusLeft) < 0.0001)
        m_radiusLeft = 0;
    if(fabs(m_radiusRight) < 0.0001)
        m_radiusRight = 0;

    if((int)m_velocityLeft == (int)m_velocityRight){
      m_leftOrientationVelocity = 0;
      m_rightOrientationVelocity = 0;
      m_orientationVelocity = 0;
      m_radiusLeft = 0;
      m_radiusRight = 0;
      m_turnType = "Not Turning";
    }
    else{
      /*Calculates the Left Orientation Change*/
      if((int)m_velocityLeft != 0 || (int)m_radiusLeft != 0)
        m_leftOrientationVelocity = fabs((180*m_velocityLeft*m_timeChange)/(M_PI*m_radiusLeft));
      else
        m_leftOrientationVelocity = 0;

      /*Calculates the Right Orientation Change*/
      if((int)m_velocityRight != 0 || (int)m_radiusRight != 0)
        m_rightOrientationVelocity = fabs((180*m_velocityRight*m_timeChange)/(M_PI*m_radiusRight));
      else
        m_rightOrientationVelocity = 0;


      if(fabs(m_velocityLeft) > fabs(m_velocityRight)){
        m_leftOrientationVelocity *= -calculateDirection(m_velocityLeft);
        m_rightOrientationVelocity *= -calculateDirection(m_velocityLeft);
      }
      else if(fabs(m_velocityLeft) < fabs(m_velocityRight)){
        m_leftOrientationVelocity *= calculateDirection(m_velocityRight);
        m_rightOrientationVelocity *= calculateDirection(m_velocityRight);
      }
      else{
        m_leftOrientationVelocity *= -calculateDirection(m_velocityLeft);
        m_rightOrientationVelocity *= calculateDirection(m_velocityRight);
      }
    }

    if(m_leftOrientationVelocity != 0 && m_rightOrientationVelocity != 0)
      m_orientationVelocity = (m_leftOrientationVelocity+m_rightOrientationVelocity)/2.0;
    else if(m_leftOrientationVelocity == 0 && m_rightOrientationVelocity != 0)
      m_orientationVelocity = m_rightOrientationVelocity;
    else if(m_leftOrientationVelocity != 0 && m_rightOrientationVelocity == 0)
      m_orientationVelocity = m_leftOrientationVelocity;
    else
      m_orientationVelocity = 0;

    m_absoluteOrientation += m_orientationVelocity;
    m_relativeOrientation = orientationConverter(m_absoluteOrientation);

    m_OrientationDebug.addLine(std::to_string(pros::millis())+", "+std::to_string(m_timeChange)+", "+std::to_string(m_velocityLeft)+", "+std::to_string(m_velocityRight)+", "+ std::to_string(m_absoluteOrientation));
  return 0;
}

int Odometry::task(){
  calculatePosition();
  calculateOrientation();
  return 0;
}

int Odometry::defineGUI(const std::string p_returnScreen){
  GraphicalInterface& l_gui = m_robot.m_gui;
  m_leftEncoder->defineGUI(l_gui, "Odometry");
  m_centerEncoder->defineGUI(l_gui, "Odometry");
  m_rightEncoder->defineGUI(l_gui, "Odometry");

  l_gui.addScreen(m_name);
  l_gui.addLabel(m_name, 200, 10, redText, m_name);
  l_gui.addRectangle(m_name, 0, 0, 480, 40, whiteText);

  l_gui.addLabel(m_name, 20, 50, whiteText, "Absolute Angle: %f Deg", &m_absoluteOrientation);
  l_gui.addLabel(m_name, 20, 80, whiteText, "Relative Angle: %f", &m_relativeOrientation);
  l_gui.addLabel(m_name, 20, 110, whiteText, "Cycle Duration: %f", &m_timeChange);
  // l_gui.addLabel(m_name, 20, 125, whiteText, "Velocity of XPosition: %f", &m_xVelocity);
  // l_gui.addLabel(m_name, 20, 150, whiteText, "Current YPosition: %f", &m_yPosition);
  // l_gui.addLabel(m_name, 20, 175, whiteText, "Velocity of YPosition: %f", &m_yVelocity);

  // l_gui.addLabel(m_name, 20, 75, whiteText, "Left Velocity: %d", (std::function<int()>)std::bind(&Encoder::getVelocity, m_leftEncoder));
  // l_gui.addLabel(m_name, 20, 100, whiteText, "Right Velocity: %d", (std::function<int()>)std::bind(&Encoder::getVelocity, m_rightEncoder));
  // l_gui.addLabel(m_name, 20, 125, whiteText, "Left Radius: %f", &m_radiusLeft);
  // l_gui.addLabel(m_name, 20, 150, whiteText, "Right Radius: %f", &m_radiusRight);
  // l_gui.addLabel(m_name, 20, 175, whiteText, "Average Radius: %f", &m_radiusAvg);
  // l_gui.addLabel(m_name, 20, 200, whiteText, "Time: %d", (std::function<int()>)std::bind(&Timer::getTime, m_timer));
  // l_gui.addLabel(m_name, 20, 200, whiteText, "T %f", &m_timeChange);

  l_gui.addButton(m_name, m_leftEncoder->getName(), 300, 60, 140, 30);
  l_gui.addButtonScreenChange(m_name, m_leftEncoder->getName(), m_leftEncoder->getName());
  l_gui.addButton(m_name, m_centerEncoder->getName(), 300, 100, 140, 30);
  l_gui.addButtonScreenChange(m_name, m_centerEncoder->getName(), m_centerEncoder->getName());
  l_gui.addButton(m_name, m_rightEncoder->getName(), 300, 140, 140, 30);
  l_gui.addButtonScreenChange(m_name, m_rightEncoder->getName(), m_rightEncoder->getName());

  l_gui.addButton(m_name, "Go Back", 160, 200, 150, 20);
  l_gui.addButtonScreenChange(m_name, "Go Back", p_returnScreen);
  return 0;
}
