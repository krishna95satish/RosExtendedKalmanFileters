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
   
    lidarBuffer_.push(lidarMsg);
    measPackage_.sensor_type_ = MeasurementPackage::LASER;
     std::cout << "got some lidar shit............" << std::endl;
     measPackage_.raw_measurements_ = VectorXd(2);
     //measPackage_.raw_measurements_ << 10 , 1;
    measPackage_.raw_measurements_ << lidarMsg->x_measured_, lidarMsg->y_measured_;
    measPackage_.timestamp_ = lidarMsg->time_stamp_;
    VectorXd gt_values(4);
    gt_values(0) = lidarMsg->x_ground_truth_;
    gt_values(1) = lidarMsg->y_ground_truth_; 
    gt_values(2) = lidarMsg->vx_ground_truth_;
    gt_values(3) = lidarMsg->vy_ground_truth_;
    groundTruth_.push_back(gt_values);
    estimate();
    //fusionEKF.ProcessMeasurement(measPackage_)
}

void FusionNode::publish() {
    ROS_INFO("Publishing Fused Data");
    //imagePublish_.publish(firstFrame_->toImageMsg());
}

void FusionNode::estimate() {
     std::cout << "estimating............" << std::endl;
if (!(radarBuffer_.empty()) && !(lidarBuffer_.empty())) {  // Checking to verify if the buffers are not empty
    currentLidarFrame_ = lidarBuffer_.front();
    currentRadarFrame_ = radarBuffer_.front();
    fusionEKF_.ProcessMeasurement(measPackage_);
    std::cout << "x :" << currentLidarFrame_->x_measured_ << std::endl;
    std::cout << "Estimated value is : " << fusionEKF_.ekf_.x_(0) << std::endl;
    //kalmanFilter();
   
    lidarBuffer_.pop();
    radarBuffer_.pop();
    //publish();
} else if (radarBuffer_.empty()) {                     // Checking if Radar data is empty publish Camera data
    //publishonedata();
} else if (radarBuffer_.empty()) {
    ROS_INFO("Camera data is Empty");
}
}

void FusionNode::publishonedata() {
    //firstFrame_ = frameBuffer_.front();
    //publish();
}

void FusionNode::kalmanFilter() {
    measPackage_.raw_measurements_ << currentLidarFrame_->x_measured_, currentLidarFrame_->y_measured_;

}

void FusionNode::radarCallback(const extendedkalmanfilters::RadarMeasurements::ConstPtr& radarMsg) {
    std::cout << "got some radar shit............" << std::endl;
    measPackage_.sensor_type_ = MeasurementPackage::RADAR;
    measPackage_.raw_measurements_ = VectorXd(3);
    measPackage_.raw_measurements_ << radarMsg->rho_measured_, radarMsg->phi_measured_, radarMsg->rhodot_measured_;
    measPackage_.timestamp_ = radarMsg->time_stamp_;
    VectorXd gt_values(4);
    gt_values(0) = radarMsg->x_ground_truth_;
    gt_values(1) = radarMsg->y_ground_truth_; 
    gt_values(2) = radarMsg->vx_ground_truth_;
    gt_values(3) = radarMsg->vy_ground_truth_;
    groundTruth_.push_back(gt_values);
    //estimate();
    radarBuffer_.push(radarMsg);
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
