// Technische Hochschule Ingolstadt

#ifndef AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_LidarPublisherNode_H_
#define AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_LidarPublisherNode_H_

#include <vector>
#include <string>
#include "LidarInput.h"
#include "Node.h"
#include "GlobalConsts.h"
#include "Ros.h"

class LidarPublisherNode : public Node {
 private:
    std::vector<extendedkalmanfilters::LidarMeasurements::ConstPtr> tempLidarData_;
    int lidarMsgCounter_{0};

 public:
    LidarPublisherNode() {}
    explicit LidarPublisherNode(const std::string& fileName);
    void getData();
    void publish();
    void nextFrame();
    int length();
    void repeatTransmission();
    void close();
    ~LidarPublisherNode(){}
};

#endif  // AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_LidarPublisherNode_H_
