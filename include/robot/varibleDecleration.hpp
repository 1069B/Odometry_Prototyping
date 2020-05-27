#include "main.h"
#include "graphical/styles.hpp"

#ifndef ENUMS_H
#define ENUMS_H

const int g_encoderVelocityMaximum = 0;
const double g_trackingWheelDistance = 26.355;//Unit: cm
const double g_trackingWheelCircumfrence = 22.15;//Unit: cm

enum RobotMode{
    ROBOT_AUTO = 0,
    ROBOT_OPERATER = 1,
    ROBOT_DISABLED = 2
};

enum TaskMode{
    TASK_AUTO = 0,
    TASK_OPERATER = 1,
    TASK_DISABLED = 2
};

enum TaskType{
    TASK_DURING_AUTO = 0,
    TASK_DURING_OPERATER = 1,
    TASK_ALWAYS = 2
};

enum ManipulatorMode {
  MANIPULATOR_VELOCITY_DEPENDENT = 0,
  MANIPULATOR_TIME_DEPENDENT = 1,
  MANIPULATOR_ENCODER_DEPENDENT = 2,
  MANIPULATOR_DISABLED = 3,
  MANIPULATOR_TOGGLE_FORWARD = 4,
  MANIPULATOR_TOGGLE_BACKWARD = 5
};

enum BaseType {
	HOLONOMIC = 0,
	HBASE = 1,
	MECANUM = 2,
	TANK2 = 3,
	TANK4 = 4
};

enum BaseState{
  BASE_STATIONARY = 0,
  BASE_DRIVER_DEPENDENT = 1,
  BASE_ODOMETRY_DEPENDENT = 2,
  BASE_VECTOR_DEPENDENT = 3,
  BASE_AUTONOMOUS_MOVEMENT = 4
};

enum BaseMode {
	NO_CORECTIONS = 0,
	ACTIVE_CORRECTIONS = 1,
};

enum AutonomousSide{
  AUTO_DEFAULT = 0,
  AUTO_BLUE = 1,
  AUTO_RED = 2,
  AUTO_SKILLS = 3,
  AUTO_NONE = 4
};

enum Direction{
  DIRECTION_FORWARD = 1,
  DIRECTION_STATIONARY = 0,
  DIRECTION_BACKWARDS = -1
};

class ControlAxis;
class ControlBtn;
class Controller;

class Encoder;
class ExternalFile;
class Motor;

struct SubTask;
class TaskScheduler;
class Timer;
class SubTimer;

struct PassInfo;
class Alert;
class Button;
class Label;
class Line;
class Meter;
class Rectangle;
class Toggle;

class Screen;
class GraphicalInterface;

struct PortSelector;

class Arm;
class Base;
class Holonomic;
class Intake;
class Odometry;

struct AutoBaseEvent;
struct AutoArmEvent;
struct AutoIntakeEvent;

class AutoProgram;
class Autonomous;

class Robot;

extern Alert g_alert;

extern Robot robot;

#endif // ENUMS_H
