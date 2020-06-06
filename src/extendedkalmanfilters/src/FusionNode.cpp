// Copyright 2019 KPIT  [legal/copyright]

#include "extendedkalmanfilters/FusionNode.h"
#include "extendedkalmanfilters/GlobalConsts.h"
#include "extendedkalmanfilters/Ros.h"

FusionNode::FusionNode():imageTransport_(node_) {
  imagePublish_ = imageTransport_.advertise(gFusionMsgname, gImagerate);
}

void FusionNode::subscribe() {
    imageTransportSubcribe_ = imageTransport_.subscribe(gCameraMsgname, gQueueSize, &FusionNode::imageCallback, this);
    subscribe_ = node_.subscribe(gRadarMsgname, gQueueSize, &FusionNode::radarCallback, this);
}

void FusionNode::imageCallback(const sensor_msgs::Image::ConstPtr& cameraMsg) {
    openCvFrame_ = RosImgToOpenCv(cameraMsg);
    frameBuffer_.push(openCvFrame_);
}

void FusionNode::publish() {
    ROS_INFO("Publishing Fused Data");
    imagePublish_.publish(firstFrame_->toImageMsg());
}

void FusionNode::synchronize() {
if (!(radarBuffer_.empty()) && !(frameBuffer_.empty())) {  // Checking to verify if the buffers are not empty
    firstFrame_ = frameBuffer_.front();
    currentFrameID_ = firstFrame_->header.frame_id;
    currentRadarFrameID_ = radarBuffer_.front();
    plot();                                            // plot using the first queue element from both queues
    radarBuffer_.pop();
    frameBuffer_.pop();
    publish();
} else if (radarBuffer_.empty()) {                     // Checking if Radar data is empty publish Camera data
    publishonedata();
} else if (frameBuffer_.empty()) {
    ROS_INFO("Camera data is Empty");
}
}

void FusionNode::publishonedata() {
    firstFrame_ = frameBuffer_.front();
    publish();
}

void FusionNode::plot() {
    std::vector<int> cartCoOrdinates;
    cartCoOrdinates = polarToCartesianConverter_.getImageCoordinates(currentRadarFrameID_);
    cv::circle(firstFrame_->image, cv::Point2i\
    (cartCoOrdinates[0], cartCoOrdinates[1]), 5, cv::Scalar(0, 0, 255), 4, 5);
}

void FusionNode::radarCallback(const extendedkalmanfilters::RadarMsg::ConstPtr& radarMsg) {
    radarBuffer_.push(radarMsg);
    synchronize();
}

int main(int argc, char** argv) {
    Ros ros_;
    ros_.initialize(argc, argv, gFusionNode);
    FusionNode fusionNode;
    fusionNode.subscribe();
    ros_.spin();
    return 0;
}
