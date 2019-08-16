# IM(Intelligent Manufacture) Robot

This robot is combine car with arm.

![IM-robot](开发笔记/img/IM-Robot.png)

## 1 car Simulation

### 1.1 navigation
navigation and avoid obstacles by ros move base
```
roslaunch thurobot thurobot_laser_nav_gazabo.launch
roslaunch thurobot nav_cloister_demo_sim.launch
roslaunch thurobot thurobot_teleop.launch
```
 
### 1.2 exploring slam
```
roslaunch thurobot thurobot_laser_nav_gazabo.launch
roslaunch thurobot exploring_slam_demo.launch
rosrun thurobot exploring_slam_sim.py 
```

## 2 car testing in robot


```
roslaunch thurobot bringup.launch 
```

You need to change linear_scale parameter in bringup.launch file.(I set as 1.0)


## 3 arm simulation

```
roslaunch auboi5_moveit_config demo.launch sim:=true
```

Then select "Interact" and move the end-effector to a new goal.

In "Motion Planning" -> "Plan and Execute" to send trajectory to the sim robot

Exit RViz and Ctrl-C the demo.launch window


# 4 bringup.launch
```
roslaunch thurobot bringup.launch
```

### 4.1 arduino_serial_node  

src/rosserial/rosserial_arduino/nodes/serial_node.py

1. 设置串口属性，波特率
2. 进入循环，执行SerialClient任务，接收并转发单片机发送的数据

### 4.2 apply_calib

src/imu_calib/src/accl_calib/apply_calib_node.cpp 
                           --apply_calib.cpp


## 4 remote move by keyboard
```
roslaunch teleop_twist_keyboard thurobot_teleop.py
```

## 6 remote establish map
```
roslaunch thurobot lidar_slam.launch
```

## 7 navigation by map
```
roslaunch thurobot navigate_multi.launch
```

## 8 automatic map
```
roslaunch thurobot auto_slam.launch
```

