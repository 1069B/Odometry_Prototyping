#include "robotClass.hpp"
#include "robot/devices/motorClass.hpp"
#include "robot/graphical/components/alertClass.hpp"
#include "robot/subsystems/baseComponents/holonomicClass.hpp"

int Robot::baseStop(){
  baseTo(0, 0, 0, 1000);
  return 0;
}

int Robot::baseTo(double speed, double orientation, double turning, int duration){
  m_base.goToVector(speed, orientation, turning);
  robot.task();
  pros::delay(duration);
  m_base.goToVector(0, 0, 0);
  robot.task();
  pros::delay(500);
  return 0;
}

int Robot::autoDefault(){
  baseTo(150, 180, 0, 750); // Cube in Red Small
  baseTo(150, 0, 0, 750); // Back robot up

  m_slider.goToVelocity(100);
  m_slider.task();
  pros::delay(750);
  m_slider.goToVelocity(0);
  m_slider.task();
  return 0;
}

int Robot::autoRed(){
  baseTo(75, 0, 0, 1000); // Cube in Red Small
  baseTo(75, 160, 0, 1000); // Back robot up
  baseTo(0, 0, 40, 2000); // Back robot up

  m_slider.goToVelocity(100);
  m_slider.task();
  pros::delay(750);
  m_slider.goToVelocity(0);
  m_slider.task();

  m_rightIntake.goToVelocity(-200);
  m_rightIntake.task();
  m_leftIntake.goToVelocity(200);
  m_leftIntake.task();

  baseTo(25, 0, 0, 8000);
  return 0;
}

int Robot::autoBlue(){
  baseTo(75, 0, 0, 1000); // Cube in Red Small
  baseTo(75, 200, 0, 1000); // Back robot up
  baseTo(0, 0, -40, 2000); // Back robot up

  m_slider.goToVelocity(100);
  m_slider.task();
  pros::delay(900);
  m_slider.goToVelocity(0);
  m_slider.task();

  m_rightIntake.goToVelocity(-200);
  m_rightIntake.task();
  m_leftIntake.goToVelocity(200);
  m_leftIntake.task();

  baseTo(25, 0, 0, 8000);
  return 0;
}

int Robot::autoSkills(){
  baseTo(75, 0, 0, 1000); // Cube in Red Small
  baseTo(100, 177, 0, 4500); // Back robot up along wall 1
  baseTo(100, 90, 0, 1500); // Drift away from wall 1 to get second cube
  baseTo(0, 0, 40, 1000); // Angle Robot back towards large red
  baseTo(110, 180, -7, 3100); // Move robot back towards scoring zone
  baseTo(150, 180, 0, 250);// Nudge 2 cubes into large red zone
  baseTo(50, 0, 0, 750);// Forwards away from zone
  baseTo(150, 101, 0, 3000);// Drift towards wall 3 step 1
  baseTo(150, 86, 0, 2250);// Drift towards wall 3 step 2
  baseTo(100, 0, 0, 750);// Shift around two cubes
  baseTo(50, 90, 0, 1900);// Right to wall
  baseTo(125, 180 - 5, 0, 1400);// Forwards into Blue Area
  baseTo(150, 180, 0, 250);// Nudge 2 cubes into large red zone
  baseTo(125, 359, 0, 3000);
  baseTo(125, 345, 0, 3000);
  baseTo(0, 0, 30, 1000);
  baseTo(200, 0, 0, 2000);
  baseTo(200, 180, 0, 1000);

  return 0;
}
