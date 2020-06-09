// Technische Hochschule Ingolstadt

#ifndef AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_RADARINPUT_H_
#define AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_RADARINPUT_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Input.h"
#include "ros/ros.h"

class RadarInput : public Input {
 private:
    RadarInput() {}
    static RadarInput *RadarInputptr;

 protected:
    rosbag::Bag bag_;
    extendedkalmanfilters::RadarMeasurements::ConstPtr radarFrame_;
    std::vector<extendedkalmanfilters::RadarMeasurements::ConstPtr> radarFrames_;
    std::string fileName_;
    std::vector<std::string> topics_{""};
    bool statusFlag_;

 public:
    void setFileName(const std::string& fname);
    bool open();
    void close();
    void read(const std::string& topicNameInRosBag);
    std::vector<extendedkalmanfilters::RadarMeasurements::ConstPtr>& getData();
    static RadarInput* newinstance();
    ~RadarInput();
};

#endif  // AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_RADARINPUT_H_
