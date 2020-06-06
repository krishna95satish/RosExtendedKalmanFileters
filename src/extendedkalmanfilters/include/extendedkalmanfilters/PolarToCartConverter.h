// Copyright 2019 KPIT  [legal/copyright]

#ifndef CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_POLARTOCARTCONVERTER_H_
#define CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_POLARTOCARTCONVERTER_H_

#include <vector>
#include "Include.h"
#include "extendedkalmanfilters/RadarMsg.h"

class PolarToCartConverter {
 protected:
    int yaw_;
    int imgCols_;
    int imgRows_;
    int lateralOffset_;
    int radarheight_;
    int radarLateralOffset_;
    int cameraToRadarDist_;
    double height_;
    double pitch_;
    double pixelWidth_;
    double Pixelheight_;
    double focalLength_;
 public:
    PolarToCartConverter();
    std::vector<int> getImageCoordinates(const extendedkalmanfilters::RadarMsg::ConstPtr& radar_msg);
    double realWorldDistanceToImageRow(double f32_distance);
    double realWorldWidthToImageCol(double f32_distance, double f32_width);
};

#endif  // CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_POLARTOCARTCONVERTER_H_
