// Technische Hochschule Ingolstadt

#ifndef AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_OUTPUTNODE_H_
#define AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_OUTPUTNODE_H_

#include <string>
#include <Eigen/Eigen>
#include "Node.h"
#include "extendedkalmanfilters/LidarMeasurements.h"
#include "extendedkalmanfilters/RadarMeasurements.h"
#include "extendedkalmanfilters/RMSError.h"
#include "Tools.h"
#include "GlobalConsts.h"
#include "Ros.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

class OutputNode : public Node {
 private:
    ros::NodeHandle node_;
    ros::Subscriber radarSubscribe_;
    ros::Subscriber lidarSubscribe_;
    ros::Subscriber fusionSubscribe_;
    vector<VectorXd> estValues_;
    vector<VectorXd> gtValues_;
    VectorXd rmsErValues_;
    Tools tools_;
    extendedkalmanfilters::RMSError RMSError_;

 public:
    OutputNode();
    void subscribe();
    void publish();
    void rmsCalulate();
    void lidarCallback(const extendedkalmanfilters::LidarMeasurements::ConstPtr& lidaraMsg);
    void radarCallback(const extendedkalmanfilters::RadarMeasurements::ConstPtr& radarMsg);
    void fusionCallback(const extendedkalmanfilters::FusedMesurements::ConstPtr& fusedMsg);
    ~OutputNode() {}
};

#endif  // AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_OUTPUTNODE_H_