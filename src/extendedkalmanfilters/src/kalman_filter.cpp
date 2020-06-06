#include "extendedkalmanfilters/kalman_filter.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

/* 
 * Please note that the Eigen library does not initialize 
 *   VectorXd or MatrixXd objects with zeros upon creation.
 */

KalmanFilter::KalmanFilter() {}

KalmanFilter::~KalmanFilter() {}

void KalmanFilter::Init(VectorXd &x_in, MatrixXd &P_in, MatrixXd &F_in,
                        MatrixXd &H_in, MatrixXd &R_in,MatrixXd &R_rad_, MatrixXd &Q_in) {
  x_ = x_in;
  P_ = P_in;
  F_ = F_in;
  H_ = H_in;
  R_ = R_in;
  R_radar_ = R_rad_;
  Q_ = Q_in;
}

void KalmanFilter::Predict() {
  /**
   * TODO: predict the state
   */
    x_ = F_ * x_;
  MatrixXd Ft = F_.transpose();
  P_ = F_ * P_ * Ft + Q_;
}

void KalmanFilter::Update(const VectorXd &z) {
  /**
   * TODO: update the state by using Kalman Filter equations
   */
   VectorXd z_pred = H_ * x_;
  VectorXd y = z - z_pred;
  MatrixXd Ht = H_.transpose();
  MatrixXd S = H_ * P_ * Ht + R_;
  MatrixXd Si = S.inverse();
  MatrixXd PHt = P_ * Ht;
  MatrixXd K = PHt * Si;
   x_ = x_ + (K * y);
  long x_size = x_.size();
  MatrixXd I = MatrixXd::Identity(x_size, x_size);
  P_ = (I - K * H_) * P_;
}

void KalmanFilter::UpdateEKF(const VectorXd &z,const MatrixXd &Hj_) {
  /**
   * TODO: update the state by using Extended Kalman Filter equations
   */
  float rho = sqrt(x_(0)*x_(0) + x_(1)*x_(1));
  float phi = atan2(x_(1), x_(0));
  //std::cout << "phi = " << phi << std::endl;
  float rho_dot;
  if (fabs(rho) < 0.0001)
  {
    rho_dot = 0;
  }
  else 
  {
    rho_dot = (x_(0)*x_(2) + x_(1)*x_(3))/rho;
  }
  VectorXd z_pred(3);
  z_pred << rho, phi, rho_dot;
  VectorXd y = z - z_pred;
  
  while ( y(1) > M_PI || y(1) < -M_PI ) {
    if ( y(1) > M_PI ) 
    {
      y(1) -= 2*M_PI;
    } 
    else 
    {
      y(1) += 2*M_PI;
    }
  }
//  std::cout << y << std::endl;
//  std::cout << Hj_ << std::endl;
  MatrixXd S = Hj_*P_*Hj_.transpose() + R_radar_;
//  std::cout << S << std::endl;
  MatrixXd K = P_*Hj_.transpose()*S.inverse();
//  std::cout << K << std::endl;
  MatrixXd I = MatrixXd::Identity(4, 4);
  
  x_ = x_ + ( K * y );
  P_ = ( I - K * Hj_ ) * P_;
  
  
}
