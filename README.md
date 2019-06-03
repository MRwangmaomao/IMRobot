# IM(Intelligent Manufacture) Robot

This robot is combine with car and arm.


## car Simulation

### navigation
navigation and avoid obstacles by ros move base
```
roslaunch thurobot thurobot_laser_nav_gazabo.launch
roslaunch thurobot nav_cloister_demo_sim.launch
roslaunch thurobot thurobot_teleop.launch
```
 
exploring slam
```
roslaunch thurobot thurobot_laser_nav_gazabo.launch
roslaunch thurobot exploring_slam_demo.launch
rosrun thurobot exploring_slam_sim.py 
```

## car testing in robot


```
roslaunch thurobot bringup.launch 
```

You need to change linear_scale parameter in bringup.launch file.(I set as 1.0)


## arm simulation

```
roslaunch auboi5_moveit_config demo.launch sim:=true
```

Then select "Interact" and move the end-effector to a new goal.

In "Motion Planning" -> "Plan and Execute" to send trajectory to the sim robot

Exit RViz and Ctrl-C the demo.launch window

