// Technische Hochschule Ingolstadt

#include "extendedkalmanfilters/OutputNode.h"


OutputNode::OutputNode() {

   rmsErrPublish_ = outputNode_.advertise<extendedkalmanfilters::RMSError>(gRmsErrorMsgname, gQueueSize);
   pub = outputNode_.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
   marker_pub = n.advertise<visualization_msgs::Marker>("visualization", 100, true);
}

void OutputNode::subscribe() {
    fusionSubscribe_ = fusionNode_.subscribe(gFusionMsgname, gQueueSize, &OutputNode::fusionCallback, this);
    
}


void OutputNode::fusionCallback(const extendedkalmanfilters::FusedMesurements::ConstPtr& fusedMsg) {
    VectorXd estValue_(4);
    VectorXd gtValue_(4);
    estValue_(0) = fusedMsg->x_estimated_;
    estValue_(1) = fusedMsg->y_estimated_;
    estValue_(2) = fusedMsg->vx_estimated_;
    estValue_(3) = fusedMsg->vy_estimated_;
    gtValue_(0) = fusedMsg->x_gt_;
    gtValue_(1) = fusedMsg->y_gt_; 
    gtValue_(2) = fusedMsg->vx_gt_;
    gtValue_(3) = fusedMsg->vy_gt_;
    estValues_.push_back(estValue_);
    gtValues_.push_back(gtValue_);

    visualize(estValue_,gtValue_);
    rmsCalulate();
    
}

void OutputNode::visualize(VectorXd& estValue,VectorXd& gtValue) {

    gtPoint_.header.frame_id = EstPoint_.header.frame_id  = gVizMarkerName;
    gtPoint_.header.stamp = EstPoint_.header.stamp = ros::Time::now();
    EstPoint_.ns =  gtPoint_.ns  = gVizNameSpace;
    gtPoint_.action  =  EstPoint_.action  = visualization_msgs::Marker::ADD;
    gtPoint_.pose.orientation.w = EstPoint_.pose.orientation.w = 1.0;
    gtPoint_.id = 0;
    EstPoint_.id = 1;
    gtPoint_.type = visualization_msgs::Marker::LINE_STRIP;
    EstPoint_.type = visualization_msgs::Marker::LINE_STRIP;
    gtPoint_.scale.x = EstPoint_.scale.x = 0.2;
    gtPoint_.scale.y = EstPoint_.scale.y  = 0.1;
    gtPoint_.color.g = 1.0f;
    EstPoint_.color.r = 1.0f;
    gtPoint_.color.a = EstPoint_.color.a = 1.0;

    gtP_.x = gtValue(0);
    gtP_.y = gtValue(1);
    gtP_.z = 0.0 ;

    estP_.x = estValue(0);
    estP_.y = estValue(1);
    estP_.z = 0.0 ;

    gtPoint_.points.push_back(gtP_);
    EstPoint_.points.push_back(estP_);
}


void OutputNode::publish() {
   //ROS_INFO("Publishing RMS Error.....");

    marker_pub.publish(gtPoint_);
    marker_pub.publish(EstPoint_);
    rmsErrPublish_.publish(RMSError_);
    pub.publish(twistMsg_);
}



void OutputNode::rmsCalulate() {
    rmsErValues_ = helper_.calculateRMSE(estValues_, gtValues_);
    RMSError_.x_err_ = rmsErValues_(0);
    twistMsg_.linear.x = rmsErValues_(0);
    RMSError_.y_err_ = rmsErValues_(1);
    //twistMsg_.linear.y = rmsErValues_(0);
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
