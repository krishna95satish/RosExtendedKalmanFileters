// Technische Hochschule Ingolstadt

#ifndef AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_EXTENDEDKKF_H_
#define AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_EXTENDEDKKF_H_

#include <string>
#include <iostream>
#include "Eigen/Dense"
#include "KalmanFilter.h"
#include "MeasurementPackage.h"
#include "Tools.h"

class ExtendedKF {
 public:
  Tools tools_;
  Eigen::MatrixXd R_laser_;
  Eigen::MatrixXd R_radar_;
  Eigen::MatrixXd H_laser_;
  Eigen::MatrixXd Hj_;
  KalmanFilter kf_;

private:
  bool is_initialized_;
  long long previous_timestamp_;

public:
  ExtendedKF();
  void processMeasurement(const MeasurementPackage &measurement_pack);
  virtual ~ExtendedKF() {};
 
};

#endif // AVML_SRC_EXTENDEDKALMANFILTERS_INCLUDE_EXTENDEDKALMANFILTERS_EXTENDEDKKF_H_
