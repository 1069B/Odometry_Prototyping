#include "robot/varibleDecleration.hpp"

#ifndef PORTSELECTOR
#define PORTSELECTOR

struct PortSelector{
private:
  std::string m_name;
  Robot& m_robot;
  std::string m_returnID;

public:
  PortSelector(Robot& p_robot, std::string p_name, std::string p_returnID, int& p_port);

};
#endif // PORTSELECTOR
