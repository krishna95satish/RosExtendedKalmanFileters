#include "extendedkalmanfilters/ExtendedKF.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;


ExtendedKF::ExtendedKF() {
  is_initialized_ = false;
  previous_timestamp_ = 0;
  R_laser_ = MatrixXd(2, 2);
  R_radar_ = MatrixXd(3, 3);
  H_laser_ = MatrixXd(2, 4);
  Hj_ = MatrixXd(3, 4);

  R_laser_ << 0.0255, 0,
              0, 0.0255;

  R_radar_ << 0.09, 0, 0,
              0, 0.0009, 0,
              0, 0, 0.09;

   H_laser_ << 1, 0, 0, 0,
               0, 1, 0, 0;
}

void ExtendedKF::processMeasurement(const MeasurementPackage& measurementPkg) {

  if (!is_initialized_) {
    kf_.X_ = VectorXd(4);
    kf_.X_ << 1, 1, 1, 1;
    MatrixXd PCovar = MatrixXd(4,4);
  	PCovar << 1,0,0,0,
  			    0,1,0,0,
  			    0,0,1000,0,
  			    0,0,0,1000;
  	MatrixXd F_in = MatrixXd(4,4);
    MatrixXd Q_in = MatrixXd(4, 4); 
    if (measurementPkg.sensor_type_ == MeasurementPackage::RADAR) {
      VectorXd xIn = kf_.X_;
      float rho = measurementPkg.rawMeasurements_(0);
      float phi = measurementPkg.rawMeasurements_(1);
      float rhoDot = measurementPkg.rawMeasurements_(2);
      xIn(0) = rho * cos(phi);
      xIn(1) = rho * sin(phi);      
      xIn(2) = rhoDot * cos(phi);
      xIn(3) = rhoDot * sin(phi);
      kf_.initialize(xIn, PCovar, F_in, H_laser_, R_laser_, R_radar_, Q_in);
      std::cout << "Initialization is Done! (RADAR)" << std::endl;

    }
    else if (measurementPkg.sensor_type_ == MeasurementPackage::LASER) {
      VectorXd xIn = kf_.X_;
      xIn(0) = measurementPkg.rawMeasurements_(0);
      xIn(1) = measurementPkg.rawMeasurements_(1);
      kf_.initialize(xIn, PCovar, F_in, H_laser_, R_laser_, R_radar_, Q_in);
      std::cout << "Initialization is Done! (LASER)" << std::endl;

    }
    is_initialized_ = true;
    previous_timestamp_ = measurementPkg.timestamp_;
    return;
  }
    float dt = (measurementPkg.timestamp_ - previous_timestamp_) / 1000000.0;
  	previous_timestamp_ = measurementPkg.timestamp_;
  kf_.F_ << 1, 0, dt, 0,
            0, 1, 0, dt,
            0, 0, 1, 0,
            0, 0, 0, 1;
  int nax = 9;
  int nay = 9;
    kf_.Q_ << pow(dt,4.0)*nax/4, 0, pow(dt,3.0)*nax/2, 0,
                  0, pow(dt,4.0)*nay/4, 0, pow(dt,3.0)*nay/2,
                  pow(dt,3.0)*nax/2, 0, pow(dt,2.0)*nax, 0,
                  0, pow(dt,3.0)*nay/2, 0, pow(dt,2.0)*nay;
  kf_.predict();
  if (measurementPkg.sensor_type_ == MeasurementPackage::RADAR) {
    Hj_ = helper_.calculateJacobian(kf_.X_);
    kf_.updateEKF(measurementPkg.rawMeasurements_, Hj_);
    std::cout << "Update by EKF is Done!" << std::endl;
  } else {
    kf_.update(measurementPkg.rawMeasurements_);
    std::cout << "Update by KF is Done!" << std::endl;
  }
}
