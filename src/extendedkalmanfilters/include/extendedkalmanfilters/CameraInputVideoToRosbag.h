// Copyright 2019 KPIT

#ifndef CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_CAMERAINPUTVIDEOTOROSBAG_H_
#define CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_CAMERAINPUTVIDEOTOROSBAG_H_

#include "Include.h"
#include "OutPut.h"

class CameraInputVideoToRosbag : public OutPut {
 private:
  CameraInputVideoToRosbag();
  static CameraInputVideoToRosbag* ptr;

 public:
  int count_;
  int publishreturn_;
  image_transport::Publisher cameraPublish_;
  rosbag::Bag bag_;
  cv::Mat frame_;
  sensor_msgs::ImagePtr Frames_;
  static CameraInputVideoToRosbag* instancecreation();

 public:
  explicit CameraInputVideoToRosbag(const ros::NodeHandle &nodeHandle);
  void write();
  virtual void close();
};

#endif  // CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_CAMERAINPUTVIDEOTOROSBAG_H_
