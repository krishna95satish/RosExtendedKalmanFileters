// Technische Hochschule Ingolstadt

#ifndef AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_BAGCREATOR_H_
#define AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_BAGCREATOR_H_

#include <rosbag/bag.h>
#include <ros/ros.h>
#include <iostream>

class BagCreator {
 public:
  BagCreator() {}
  ros::NodeHandle radarNode_;
  ros::NodeHandle lidarNode_;
  ros::Publisher radarPublish_;
  ros::Publisher lidarPublish_;
  virtual void close() {};
  virtual void radarWrite() {};
  virtual void lidarWrite() {};
  ~BagCreator() {}
};
#endif  // AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_BAGCREATOR_H_
