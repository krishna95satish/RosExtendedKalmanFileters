    // Copyright 2019 KPIT  [legal/copyright]

#ifndef CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_LidarInput_H_
#define CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_LidarInput_H_

#include "Input.h"
#include <string>
#include <vector>

class LidarInput : public Input {
 private:
    LidarInput() {}
    static LidarInput *lidarInputptr_;
 protected:
    std::string fileName_;
    extendedkalmanfilters::LidarMeasurements::ConstPtr lidarFrame_;
    std::vector<extendedkalmanfilters::LidarMeasurements::ConstPtr> lidarFrames_;
    rosbag::Bag bag_;
    std::vector<std::string> topics_{""};
    bool statusFlag_;

 public:
    void setFileName(const std::string& fname);
    bool open();
    void close();
    void read(const std::string& topicNameInRosBag);
    std::vector<extendedkalmanfilters::LidarMeasurements::ConstPtr>& getData();
    static LidarInput* newinstance();
    ~LidarInput();
};

#endif  // CAMRARFUSION_SRC_ROSBAG_CREATION_INCLUDE_ROSBAG_CREATION_LidarInput_H_
