// Copyright 2019 KPIT  [legal/copyright]

#include "extendedkalmanfilters/Include.h"
#include "extendedkalmanfilters/GlobalConsts.h"
#include "extendedkalmanfilters/CameraInputVideoToRosbag.h"

CameraInputVideoToRosbag* CameraInputVideoToRosbag::ptr = NULL;

CameraInputVideoToRosbag* CameraInputVideoToRosbag::instancecreation() {
    if (ptr == NULL) {
        ptr = new CameraInputVideoToRosbag;
    }
    return ptr;
}

CameraInputVideoToRosbag::CameraInputVideoToRosbag() {
    count_ = gCount;
    image_transport::ImageTransport imageTransport(node_);
    cameraPublish_ = imageTransport.advertise(gCameraTopicName, gImagerate);
    write();
}

void CameraInputVideoToRosbag::close() {
  bag_.close();
  exit(0);
}

CameraInputVideoToRosbag::CameraInputVideoToRosbag(const ros::NodeHandle &nodeHandle) {
    node_ = nodeHandle;
}

void CameraInputVideoToRosbag::write() {
    image_transport::ImageTransport imageTransport(node_);
    ros::Rate loop_rate(gPublisherBaudRate);
    cv::VideoCapture capture(CameraNodeFile);
    if (!capture.isOpened()) {
        std::cout << "File Error" << std::endl;
    }
    bag_.open(gCameraBag, rosbag::bagmode::Write);
    while (node_.ok()) {
        capture >> frame_;
        if (!frame_.empty()) {
            Frames_ = cv_bridge::CvImage(std_msgs::Header(), gColorStanderd, frame_).toImageMsg();
            std::stringstream string;
            string << count_;
            Frames_->header.frame_id = string.str();
            cameraPublish_.publish(Frames_);
            bag_.write(gCameraBagName, ros::Time::now(), Frames_);
            count_++;
        } else {
            break;
        }
        ros::spinOnce();
    }
}
