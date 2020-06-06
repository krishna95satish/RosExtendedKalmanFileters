// Copyright 2019 <KPIT> [legal/copyright]

#ifndef CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_LidarPublisherNode_H_
#define CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_LidarPublisherNode_H_

#include <vector>
#include <string>
#include "lidarInput.h"
#include "Node.h"
#include "GlobalConsts.h"

class LidarPublisherNode : public Node {
 private:
    std::vector<extendedkalmanfilters::LidarMeasurements::ConstPtr> tempLidarData_;
    int lidarMsgCounter_{0};

 public:
    LidarPublisherNode() {}
    explicit LidarPublisherNode(const std::string& fileName);
    void getData();
    void publish();
    void nextFrame();
    int length();
    void repeatTransmission();
    void close();
    ~LidarPublisherNode(){}
};

#endif  // CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_LidarPublisherNode_H_
