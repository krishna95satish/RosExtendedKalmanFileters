// Copyright 2019 KPIT  [legal/copyright]

#ifndef CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_FUSIONNODE_H_
#define CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_FUSIONNODE_H_

#include <string>
#include <queue>
#include "extendedkalmanfilters/Node.h"
#include "extendedkalmanfilters/RadarMsg.h"
#include "PolarToCartConverter.h"

class FusionNode : public Node {
 private:
    std::string currentFrameID_{0};
    ros::NodeHandle node_;
    ros::Subscriber subscribe_;
    image_transport::Subscriber imageTransportSubcribe_;
    image_transport::Publisher imagePublish_;
    image_transport::ImageTransport imageTransport_;
    cv_bridge::CvImagePtr openCvFrame_{nullptr};
    PolarToCartConverter polarToCartesianConverter_;
    cv_bridge::CvImagePtr firstFrame_;
    std::queue<extendedkalmanfilters::RadarMsg::ConstPtr> radarBuffer_;
    std::queue<cv_bridge::CvImagePtr> frameBuffer_;
    extendedkalmanfilters::RadarMsg::ConstPtr currentRadarFrameID_{nullptr};

 public:
    FusionNode();
    void subscribe();
    void publish();
    void synchronize();
    void plot();
    void imageCallback(const sensor_msgs::Image::ConstPtr& cameraMsg);
    void radarCallback(const extendedkalmanfilters::RadarMsg::ConstPtr& radarMsg);
    void publishonedata();
    ~FusionNode() {}
};

#endif  // CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_FUSIONNODE_H_
