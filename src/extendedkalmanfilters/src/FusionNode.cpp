// Copyright 2019 KPIT  [legal/copyright]

#include "extendedkalmanfilters/FusionNode.h"
#include "extendedkalmanfilters/GlobalConsts.h"
#include "extendedkalmanfilters/Ros.h"

FusionNode::FusionNode() {
   fusionPublish_ = fusionNode_.advertise<extendedkalmanfilters::FusedMesurements>(gFusionMsgname, gQueueSize);
}

void FusionNode::subscribe() {
    lidarSubscribe_ = node_.subscribe(gLidarMsgname, gQueueSize, &FusionNode::lidarCallback, this);
    radarSubscribe_ = node_.subscribe(gRadarMsgname, gQueueSize, &FusionNode::radarCallback, this);
}

void FusionNode::lidarCallback(const extendedkalmanfilters::LidarMeasurements::ConstPtr& lidarMsg) {
   std::cout << "got some lidar data............" << std::endl;
    measPackage_.sensor_type_ = MeasurementPackage::LASER;
    measPackage_.raw_measurements_ = VectorXd(2);
    measPackage_.raw_measurements_ << lidarMsg->x_measured_, lidarMsg->y_measured_;
    measPackage_.timestamp_ = lidarMsg->time_stamp_;
    estimate();
}

void FusionNode::publish() {
    ROS_INFO("Publishing Fused Data");
    fusionPublish_.publish(fusedFrame_);
}

void FusionNode::estimate() {
     std::cout << "estimating............" << std::endl;
    fusionEKF_.ProcessMeasurement(measPackage_);
    fusedFrame_.x_estimated_ = fusionEKF_.ekf_.x_(0);
    fusedFrame_.y_estimated_ = fusionEKF_.ekf_.x_(1);
    fusedFrame_.time_stamp_ = measPackage_.timestamp_;
    fusedFrame_.vx_estimated_ = fusionEKF_.ekf_.x_(2);
    fusedFrame_.vy_estimated_ = fusionEKF_.ekf_.x_(3);
    publish();
}

void FusionNode::publishonedata() {
}

void FusionNode::radarCallback(const extendedkalmanfilters::RadarMeasurements::ConstPtr& radarMsg) {
    std::cout << "got some radar data............" << std::endl;
    measPackage_.sensor_type_ = MeasurementPackage::RADAR;
    measPackage_.raw_measurements_ = VectorXd(3);
    measPackage_.raw_measurements_ << radarMsg->rho_measured_, radarMsg->phi_measured_, radarMsg->rhodot_measured_;
    measPackage_.timestamp_ = radarMsg->time_stamp_;
    estimate();
}

int main(int argc, char** argv) {
    Ros ros_;
    ros_.initialize(argc, argv, gFusionNode);
    FusionNode fusionNode;
    fusionNode.subscribe();
    ros_.spin();
    return 0;
}
