// Technische Hochschule Ingolstadt

#ifndef AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_OUTPUTNODE_H_
#define AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_OUTPUTNODE_H_

#include <string>
#include <Eigen/Eigen>
#include "Node.h"
#include "extendedkalmanfilters/LidarMeasurements.h"
#include "extendedkalmanfilters/RadarMeasurements.h"
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
    Tools tools_;
    MeasurementPackage measPackage_;
    extendedkalmanfilters::FusedMesurements fusedFrame_;

 public:
    OutputNode();
    void subscribe();
    void publish();
    void rmsError();
    void lidarCallback(const extendedkalmanfilters::LidarMeasurements::ConstPtr& lidaraMsg);
    void radarCallback(const extendedkalmanfilters::RadarMeasurements::ConstPtr& radarMsg);
    void radarCallback(const extendedkalmanfilters::FusedMesurements::ConstPtr& fusedMsg);
    ~OutputNode() {}
};

#endif  // AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_OUTPUTNODE_H_
