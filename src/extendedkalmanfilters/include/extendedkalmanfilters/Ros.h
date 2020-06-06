// Copyright 2019 KPIT  [legal/copyright]

#ifndef CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_ROS_H_
#define CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_ROS_H_

#include <string>
#include "GlobalConsts.h"
#include "ros/ros.h"

class Ros {
 public:
    void initialize(int argc, char** argv, const std::string nodename);
    void spin();
    void rate();
};

#endif  // CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_ROS_H_
