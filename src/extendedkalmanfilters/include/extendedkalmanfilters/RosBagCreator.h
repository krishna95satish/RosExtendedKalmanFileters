// Technische Hochschule Ingolstadt

#ifndef AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_ROSBAGCREATOR_H_
#define AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_ROSBAGCREATOR_H_


#include "GlobalConsts.h"
#include "Include.h"
#include "BagCreator.h"
#include "Ros.h"
#include "extendedkalmanfilters/RadarMeasurements.h"
#include "extendedkalmanfilters/LidarMeasurements.h"

class RosBagCreator : public BagCreator {
 public:
  RosBagCreator();
  void read();
  void lidarWrite(std::string& s_type, float x_m, float y_m, long long t, float x_gt, float y_gt, float vx_gt, float vy_gt);
  void radarWrite(std::string& s_type, float rho, float phi, float rhodot, long long t, float x_gt, float y_gt, float vx_gt, float vy_gt);
  void close();
};

#endif  // AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_ROSBAGCREATOR_H_
