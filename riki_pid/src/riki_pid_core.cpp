#include "riki_pid/riki_pid_core.h"

RikiPID::RikiPID()
{
}

RikiPID::~RikiPID()
{
}

void RikiPID::publishMessage(ros::Publisher *pub_message)
{
  riki_msgs::PID msg;
  msg.p = p_;
  msg.d = d_;
  msg.i = i_;
  pub_message->publish(msg);
}

void RikiPID::messageCallback(const riki_msgs::PID::ConstPtr &msg)
{
  p_ = msg->p;
  d_ = msg->d;
  i_ = msg->i;

  //echo P,I,D
  ROS_INFO("P: %f", p_);
  ROS_INFO("D: %f", d_);
  ROS_INFO("I: %f", i_);
}

void RikiPID::configCallback(riki_pid::rikiPIDConfig &config, double level)
{
  //for PID GUI
  p_ = config.p;
  d_ = config.d;
  i_ = config.i;

}
