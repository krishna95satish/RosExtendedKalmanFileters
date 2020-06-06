// Copyright 2019 KPIT  [legal/copyright]

#ifndef CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_FUSIONNODE_H_
#define CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_FUSIONNODE_H_

#include <string>
#include <vector>
#include <queue>
#include <Eigen/Eigen>
#include "extendedkalmanfilters/Node.h"
#include "extendedkalmanfilters/LidarMeasurements.h"
#include "extendedkalmanfilters/RadarMeasurements.h"
#include "extendedkalmanfilters/tools.h"
#include "extendedkalmanfilters/FusionEKF.h"
#include "extendedkalmanfilters/measurement_package.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

class FusionNode : public Node {
 private:
    std::string currentFrameID_{0};
    ros::NodeHandle node_;
    ros::Subscriber radarSubscribe_;
    ros::Subscriber lidarSubscribe_;
    FusionEKF fusionEKF_;
    Tools tools_;
    MeasurementPackage measPackage_;
    std::vector<VectorXd> estimations_;
    std::vector<VectorXd> groundTruth_;
    std::queue<extendedkalmanfilters::RadarMeasurements::ConstPtr> radarBuffer_;
    std::queue<extendedkalmanfilters::LidarMeasurements::ConstPtr> lidarBuffer_;
    extendedkalmanfilters::RadarMeasurements::ConstPtr currentRadarFrame_{nullptr};
    extendedkalmanfilters::LidarMeasurements::ConstPtr currentLidarFrame_{nullptr};

 public:
    FusionNode();
    void subscribe();
    void publish();
    void estimate();
    void kalmanFilter();
    void lidarCallback(const extendedkalmanfilters::LidarMeasurements::ConstPtr& lidaraMsg);
    void radarCallback(const extendedkalmanfilters::RadarMeasurements::ConstPtr& radarMsg);
    void publishonedata();
    ~FusionNode() {}
};

#endif  // CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_FUSIONNODE_H_
