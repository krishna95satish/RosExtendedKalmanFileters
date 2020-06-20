// Technische Hochschule Ingolstadt

#ifndef AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_OUTPUTNODE_H_
#define AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_OUTPUTNODE_H_

#include <string>
#include <visualization_msgs/Marker.h>
#include <Eigen/Eigen>
#include "Node.h"
#include "extendedkalmanfilters/LidarMeasurements.h"
#include "extendedkalmanfilters/RadarMeasurements.h"
#include "extendedkalmanfilters/RMSError.h"
#include <geometry_msgs/Twist.h>
#include "Helper.h"
#include "GlobalConsts.h"
#include "Ros.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

class OutputNode : public Node {
 private:
    ros::NodeHandle node_;
       ros::NodeHandle n;
   ros::Publisher marker_pub;
    ros::Subscriber fusionSubscribe_;
    geometry_msgs::Twist twistMsg_;

    vector<VectorXd> estValues_;
    geometry_msgs::Point gtP_,estP_;
    visualization_msgs::Marker gtPoint_,EstPoint_;
    vector<VectorXd> gtValues_;
    ros::Publisher pub;
    VectorXd rmsErValues_;
    Helper helper_;
    extendedkalmanfilters::RMSError RMSError_;

 public:
    OutputNode();
    void subscribe();
    void publish();
    void visualize(VectorXd& estValue,VectorXd& gtValue);
    void rmsCalulate();
    void fusionCallback(const extendedkalmanfilters::FusedMesurements::ConstPtr& fusedMsg);
    ~OutputNode() {}
};

#endif  // AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_OUTPUTNODE_H_
