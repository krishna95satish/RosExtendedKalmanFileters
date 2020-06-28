// Technische Hochschule Ingolstadt

#ifndef CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_NODE_H_
#define CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_NODE_H_

#include "Input.h"
#include "GlobalConsts.h"
#include "Ros.h"
#include "LidarInput.h"
#include "RadarInput.h"
#include "Include.h"
#include "extendedkalmanfilters/RMSError.h"


class Node {
 protected:
    ros::NodeHandle lidarNode_;
    ros::NodeHandle radarNode_;
    ros::NodeHandle fusionNode_;
    ros::NodeHandle outputNode_;
    ros::Publisher radarPublish_;
    ros::Publisher lidarPublish_;
    ros::Publisher fusionPublish_;
    ros::Publisher rmsErrPublish_;
    ros::Subscriber subscribe_;
    std::vector<std::string> topics_{""};

 public:
    Node() {}
    LidarInput *lidarInput_ = LidarInput::newinstance();
    RadarInput *radarInput_ = RadarInput::newinstance();
    virtual void getData();
    virtual void publish();
    virtual void subscribe();
    virtual void repeatTransmission();
    virtual int length();
    virtual void nextFrame();
    virtual ~Node();
};

#endif  // CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_NODE_H_
