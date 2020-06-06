// Copyright 2019 KPIT  [legal/copyright]
#include "extendedkalmanfilters/RadarInput.h"

void RadarInput::setFileName(const std::string& fname) {
    fileName_ = fname;
}

RadarInput* RadarInput::RadarInputptr = NULL;

bool RadarInput::open() {
    try {
        bag_.open(fileName_, rosbag::bagmode::Read);
        statusFlag_ = true;
    }
    catch(rosbag::BagIOException& errMsg) {
        ROS_INFO("Error is :  [%s]", errMsg.what());
        statusFlag_ = false;
    }
    return statusFlag_;
}

RadarInput* RadarInput::newinstance() {
    if (RadarInputptr == NULL) {
        RadarInputptr = new RadarInput;
    }
    return RadarInputptr;
}

void RadarInput::read(const std::string& topicNameInRosBag) {
    topics_.push_back(topicNameInRosBag);
    rosbag::View view(bag_, rosbag::TopicQuery(topics_));
    for (auto rosBagConstMsg : rosbag::View(bag_)) {
        radarFrame_  = rosBagConstMsg.instantiate<extendedkalmanfilters::RadarMeasurements>();
        if (radarFrame_  != NULL) {
            radarFrames_.push_back(radarFrame_);
        }
    }
}

std::vector<extendedkalmanfilters::RadarMeasurements::ConstPtr>& RadarInput::getData() {
    return radarFrames_;
}

void RadarInput::close() {
  bag_.close();
}

RadarInput::~RadarInput() {
    delete(RadarInputptr);
}
