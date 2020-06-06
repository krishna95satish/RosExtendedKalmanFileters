// Copyright 2019 KPIT

#ifndef CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_rosBagCreator_H_
#define CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_rosBagCreator_H_

#include <extendedkalmanfilters/GlobalConsts.h>
#include "extendedkalmanfilters/RadarMeasurements.h"
#include "extendedkalmanfilters/LidarMeasurements.h"
#include "OutPut.h"

class RosBagCreator : public OutPut {
 public:
  RosBagCreator();
  void read();
  void lidarWrite(std::string& s_type, float x_m, float y_m, long long t, float x_gt, float y_gt, float vx_gt, float vy_gt);
  void radarWrite(std::string& s_type, float rho, float phi, float rhodot, long long t, float x_gt, float y_gt, float vx_gt, float vy_gt);
  void close();
};

#endif  // CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_rosBagCreator_H_
