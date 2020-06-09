// Technische Hochschule Ingolstadt

#ifndef AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_INPUT_H_
#define AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_INPUT_H_

#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <string>
#include <vector>
#include "extendedkalmanfilters/RadarMeasurements.h"
#include "extendedkalmanfilters/LidarMeasurements.h"
#include "extendedkalmanfilters/FusedMesurements.h"

class Input {
 public:
    virtual bool open() = 0;
    virtual void read() {}
};

#endif  // AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_INPUT_H_
