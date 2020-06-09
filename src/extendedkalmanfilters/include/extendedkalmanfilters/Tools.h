#ifndef AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_TOOLS_H_
#define AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_TOOLS_H_

#include <vector>
#include <iostream>
#include <cmath>
#include "Eigen/Dense"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

class Tools {
 public:
  Tools() {};
  Eigen::VectorXd calculateRMSE(const std::vector<Eigen::VectorXd> &estimations, 
                                const std::vector<Eigen::VectorXd> &ground_truth);
  Eigen::MatrixXd calculateJacobian(const Eigen::VectorXd& x_state);
 virtual ~Tools() {};
};

#endif  // AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_TOOLS_H_
