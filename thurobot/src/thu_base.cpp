#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>
#include <thu_base.h>

RikiBase::RikiBase():
    linear_velocity_x_(0),
    linear_velocity_y_(0),
    angular_velocity_z_(0),
    last_vel_time_(0),
    vel_dt_(0),
    x_pos_(0),
    y_pos_(0),
    heading_(0)
{
    //NodeHandle作用：首先，在roscpp程序的内部，它提供了RAII方式启动和关闭。
    //其次，提供了一个额外的层命令空间解决方案，可以使组件更容易写。 
    /**
        ros::init(argc, argv, "node_name"); // node name
        ros::NodeHandle n; //n 命名空间为/node_namespace
        ros::NodeHandle n1("sub"); // n1命名空间为/node_namespace/sub
        ros::NodeHandle n2(n1,"sub2");// n2命名空间为/node_namespace/sub/sub2
        ros::NodeHandle pn1("~"); //pn1 命名空间为/node_namespace/node_name
        ros::NodeHandle pn2("~sub"); //pn2 命名空间为/node_namespace/node_name/sub
        ros::NodeHandle pn3("~/sub"); //pn3 命名空间为/node_namespace/node_name/sub
        ros::NodeHandle gn("/global"); // gn 命名空间为/global 
     */
    ros::NodeHandle nh_private("~"); //~代表访问私有名称
    odom_publisher_ = nh_.advertise<nav_msgs::Odometry>("raw_odom", 50);
    velocity_subscriber_ = nh_.subscribe("raw_vel", 50, &RikiBase::velCallback, this);
    nh_private.getParam("linear_scale", linear_scale_);
    
    //ROS_INFO("linear_scale_: %f", linear_scale_);
}

void RikiBase::velCallback(const riki_msgs::Velocities& vel)
{
    ros::Time current_time = ros::Time::now();

    linear_velocity_x_ = vel.linear_x * linear_scale_;
    linear_velocity_y_ = vel.linear_y * linear_scale_;
    angular_velocity_z_ = vel.angular_z;

    vel_dt_ = (current_time - last_vel_time_).toSec();
    last_vel_time_ = current_time;

    double delta_heading = angular_velocity_z_ * vel_dt_ ; //radians
    double delta_x = (linear_velocity_x_ * cos(heading_) - linear_velocity_y_ * sin(heading_)) * vel_dt_ ; //m
    double delta_y = (linear_velocity_x_ * sin(heading_) + linear_velocity_y_ * cos(heading_)) * vel_dt_ ; //m

    //calculate current position of the robot
    x_pos_ += delta_x;
    y_pos_ += delta_y;
    heading_ += delta_heading;

    //calculate robot's heading in quaternion angle
    //ROS has a function to calculate yaw in quaternion angle
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(heading_);

    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_footprint";
    //robot's position in x,y, and z
    odom_trans.transform.translation.x = x_pos_;
    odom_trans.transform.translation.y = y_pos_;
    odom_trans.transform.translation.z = 0.0;
    //robot's heading in quaternion
    odom_trans.transform.rotation = odom_quat;
    odom_trans.header.stamp = current_time;
    //publish robot's tf using odom_trans object
    // odom_broadcaster_.sendTransform(odom_trans);

    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";
    odom.child_frame_id = "base_footprint";

    //robot's position in x,y, and z
    odom.pose.pose.position.x = x_pos_;
    odom.pose.pose.position.y = y_pos_;
    odom.pose.pose.position.z = 0.0;
    //robot's heading in quaternion
    odom.pose.pose.orientation = odom_quat;
    odom.pose.covariance[0] = 0.001;
    odom.pose.covariance[7] = 0.001;
    odom.pose.covariance[35] = 0.001;

    //linear speed from encoders
    odom.twist.twist.linear.x = linear_velocity_x_;
    odom.twist.twist.linear.y = linear_velocity_y_;
    odom.twist.twist.linear.z = 0.0;

    odom.twist.twist.angular.x = 0.0;
    odom.twist.twist.angular.y = 0.0;
    //angular speed from encoders
    odom.twist.twist.angular.z = angular_velocity_z_;
    odom.twist.covariance[0] = 0.0001;
    odom.twist.covariance[7] = 0.0001;
    odom.twist.covariance[35] = 0.0001;

    odom_publisher_.publish(odom);
}
