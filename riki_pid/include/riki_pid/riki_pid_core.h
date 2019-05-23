#ifndef SR_RIKI_PID_CORE_H
#define SR_RIKI_PID_CORE_H

#include "ros/ros.h"
#include "ros/time.h"

// Custom message includes. Auto-generated from msg/ directory.
#include "riki_msgs/PID.h"

// Dynamic reconfigure includes.
#include <dynamic_reconfigure/server.h>
// Auto-generated from cfg/ directory.
#include <riki_pid/rikiPIDConfig.h>

class RikiPID
{
public:
  RikiPID();
  ~RikiPID();
  void configCallback(riki_pid::rikiPIDConfig &config, double level);
  void publishMessage(ros::Publisher *pub_message);
  void messageCallback(const riki_msgs::PID::ConstPtr &msg);

  double p_;
  double d_;
  double i_;

};
#endif
