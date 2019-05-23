rm -rf /home/rikirobot/catkin_ws/src/rikirobot_project/rikirobot/maps/house.pgm 
rm -rf /home/rikirobot/catkin_ws/src/rikirobot_project/rikirobot/maps/house.yaml

rosservice call /write_state /home/rikirobot/catkin_ws/src/rikirobot_project/rikirobot/maps/map.bag.pbstream

rosrun cartographer_ros cartographer_pbstream_to_ros_map -pbstream_filename=/home/rikirobot/catkin_ws/src/rikirobot_project/rikirobot/maps/map.bag.pbstream


cp  /home/rikirobot/catkin_ws/src/rikirobot_project/rikirobot/maps/map.pgm /home/rikirobot/catkin_ws/src/rikirobot_project/rikirobot/maps/house.pgm

cp  /home/rikirobot/catkin_ws/src/rikirobot_project/rikirobot/maps/map.yaml /home/rikirobot/catkin_ws/src/rikirobot_project/rikirobot/maps/house.yaml

