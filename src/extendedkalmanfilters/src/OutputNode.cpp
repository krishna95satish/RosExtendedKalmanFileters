// Technische Hochschule Ingolstadt

#include "extendedkalmanfilters/OutputNode.h"

OutputNode::OutputNode() {
   rmsErrPublish_ = outputNode_.advertise<extendedkalmanfilters::RMSError>(gRmsErrorMsgname, gQueueSize);
}

void OutputNode::subscribe() {
    fusionSubscribe_ = fusionNode_.subscribe(gFusionMsgname, gQueueSize, &OutputNode::fusionCallback, this);
    lidarSubscribe_ = lidarNode_.subscribe(gLidarMsgname, gQueueSize, &OutputNode::lidarCallback, this);
    radarSubscribe_ = radarNode_.subscribe(gRadarMsgname, gQueueSize, &OutputNode::radarCallback, this);
    
}

void OutputNode::lidarCallback(const extendedkalmanfilters::LidarMeasurements::ConstPtr& lidarMsg) {
    VectorXd gtValuesL(4);
    gtValuesL(0) = lidarMsg->x_ground_truth_;
    gtValuesL(1) = lidarMsg->y_ground_truth_; 
    gtValuesL(2) = lidarMsg->vx_ground_truth_;
    gtValuesL(3) = lidarMsg->vy_ground_truth_;
    gtValues_.push_back(gtValuesL);
}

void OutputNode::radarCallback(const extendedkalmanfilters::RadarMeasurements::ConstPtr& radarMsg) {
    VectorXd gtValuesR(4);
    gtValuesR(0) = radarMsg->x_ground_truth_;
    gtValuesR(1) = radarMsg->y_ground_truth_; 
    gtValuesR(2) = radarMsg->vx_ground_truth_;
    gtValuesR(3) = radarMsg->vy_ground_truth_;
    gtValues_.push_back(gtValuesR);
}


void OutputNode::fusionCallback(const extendedkalmanfilters::FusedMesurements::ConstPtr& fusedMsg) {
    VectorXd estValues(4);
    estValues(0) = fusedMsg->x_estimated_;
    estValues(1) = fusedMsg->y_estimated_;
    estValues(2) = fusedMsg->vx_estimated_;
    estValues(3) = fusedMsg->vy_estimated_;
    estValues_.push_back(estValues);
    if (gtValues_.size() != 0) {
        rmsCalulate();
    }
    
}


void OutputNode::publish() {
   //ROS_INFO("Publishing RMS Error.....");
    rmsErrPublish_.publish(RMSError_);
}

void OutputNode::rmsCalulate() {
    rmsErValues_ = tools_.calculateRMSE(estValues_, gtValues_);
    RMSError_.x_err_ = rmsErValues_(0);
    RMSError_.y_err_ = rmsErValues_(1);
    RMSError_.vx_err_ = rmsErValues_(2);
    RMSError_.vy_err_ = rmsErValues_(3);
    publish();
}


int main(int argc, char** argv) {
    Ros ros;
    ros.initialize(argc, argv, gOutputNode);
    OutputNode outputNode;
    outputNode.subscribe();
    ros.spin();
    return 0;
}
