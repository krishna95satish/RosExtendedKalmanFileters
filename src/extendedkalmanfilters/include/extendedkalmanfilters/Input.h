// Copyright 2019 KPIT  [legal/copyright]

#ifndef CAMRARFUSION_SRC_extendedkalmanfilters_INCLUDE_extendedkalmanfilters_INPUT_H_
#define CAMRARFUSION_SRC_extendedkalmanfilters_INCLUDE_extendedkalmanfilters_INPUT_H_

#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <string>
#include <vector>
#include "extendedkalmanfilters/RadarMeasurements.h"
#include "extendedkalmanfilters/LidarMeasurements.h"

class Input {
 public:
    virtual bool open() = 0;
    virtual void read() {}
};

#endif  // CAMRARFUSION_SRC_extendedkalmanfilters_INCLUDE_extendedkalmanfilters_INPUT_H_
