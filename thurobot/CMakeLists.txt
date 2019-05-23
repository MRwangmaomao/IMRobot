cmake_minimum_required(VERSION 2.8.3)
project(thurobot)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  rosserial_python
  sensor_msgs
  riki_msgs
  std_msgs
  tf
  gazebo_plugins
  gazebo_ros
  gazebo_ros_control
)
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES thurobot
  CATKIN_DEPENDS roscpp rospy tf nav_msgs riki_msgs geometry_msgs sensor_msgs std_msgs 
  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(thu_base src/thu_base.cpp)
add_executable(thu_base_node src/thu_base_node.cpp)
target_link_libraries(thu_base_node thu_base ${catkin_LIBRARIES})

