// Technische Hochschule Ingolstadt

#include "extendedkalmanfilters/OutputNode.h"

OutputNode::OutputNode() {
   rmsErrPublish_ = outputNode_.advertise<extendedkalmanfilters::RMSError>(gRmsErrorMsgname, gQueueSize);
}

void OutputNode::subscribe() {
    fusionSubscribe_ = fusionNode_.subscribe(gFusionMsgname, gQueueSize, &OutputNode::fusionCallback, this);
    
}


void OutputNode::fusionCallback(const extendedkalmanfilters::FusedMesurements::ConstPtr& fusedMsg) {
    VectorXd estValues(4);
    VectorXd gtValues(4);
    estValues(0) = fusedMsg->x_estimated_;
    estValues(1) = fusedMsg->y_estimated_;
    estValues(2) = fusedMsg->vx_estimated_;
    estValues(3) = fusedMsg->vy_estimated_;
    gtValues(0) = fusedMsg->x_gt_;
    gtValues(1) = fusedMsg->y_gt_; 
    gtValues(2) = fusedMsg->vx_gt_;
    gtValues(3) = fusedMsg->vy_gt_;
    estValues_.push_back(estValues);
    gtValues_.push_back(gtValues);
    rmsCalulate();
    
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
