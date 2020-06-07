// Copyright 2019 KPIT  [legal/copyright]

#include "extendedkalmanfilters/RadarPublisherNode.h"
#include "extendedkalmanfilters/GlobalConsts.h"
#include "extendedkalmanfilters/Ros.h"

RadarPublisherNode::RadarPublisherNode(const std::string& fileName) {
    radarInput_->setFileName(fileName);
    radarPublish_ = radarNode_.advertise<extendedkalmanfilters::RadarMeasurements>(gRadarMsgname, gQueueSize);
}

void RadarPublisherNode::getData() {
    if (radarInput_->open()) {
        radarInput_->read(gRadarTopicname);
        tempRadarData_ = radarInput_->getData();
        radarInput_->close();
    } else {
        std::cout << "Error Opening the Bag file, Killing the Node....." << std::endl;
        ros::shutdown();
    }
}

void RadarPublisherNode::publish() {
    ROS_INFO("Publishing Radar Data");
    if (radarMsgCounter_ != length()) {
        radarPublish_.publish(tempRadarData_[radarMsgCounter_]);
        nextFrame();
    } else {
        repeatTransmission();
    }
}


int RadarPublisherNode::length() {
    return(tempRadarData_.size());
}

void RadarPublisherNode::nextFrame() {
    radarMsgCounter_++;
}

void RadarPublisherNode::repeatTransmission() {
    radarMsgCounter_ = gFrameReset;
}

int main(int argc, char** argv) {
    Ros ros_;
    ros_.initialize(argc, argv, gRadarPublisherNode);
    RadarPublisherNode radarPublisherNode(gRadarNodeFile);
    radarPublisherNode.getData();
    ros::Rate loop_rate(gPublisherBaudRate);
    while (ros::ok()) {
        radarPublisherNode.publish();
        ros_.rate();
        loop_rate.sleep();
    }
    return 0;
}
