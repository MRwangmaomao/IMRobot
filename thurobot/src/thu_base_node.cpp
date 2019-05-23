#include <ros/ros.h>
#include "thu_base.h"

int main(int argc, char** argv )
{
    ros::init(argc, argv, "thu_base_node");
    RikiBase thu;
    ros::spin();
    return 0;
}
