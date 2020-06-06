// Copyright 2019 rajesab
#ifndef CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_OUTPUT_H_
#define CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_OUTPUT_H_

#include <rosbag/bag.h>
#include <ros/ros.h>
#include <iostream>

class OutPut {
 public:
  OutPut() {}
  ros::NodeHandle radarNode_;
  ros::NodeHandle lidarNode_;
  ros::Publisher radarPublish_;
  ros::Publisher lidarPublish_;
  virtual void close() {}
  virtual void radarWrite() {}
  virtual void lidarWrite() {}
};
#endif  // CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_OUTPUT_H_
