// Technische Hochschule Ingolstadt

#include "extendedkalmanfilters/RosBagCreator.h"

extendedkalmanfilters::RadarMeasurements radarMeasurement;
extendedkalmanfilters::LidarMeasurements lidarMeasurement;

rosbag::Bag radarBag(gRadarBag, rosbag::bagmode::Write);
rosbag::Bag lidarBag(gLidarBag, rosbag::bagmode::Write);

RosBagCreator::RosBagCreator() {
  radarPublish_ = radarNode_.advertise<extendedkalmanfilters::RadarMeasurements>(gRadarTopic, gQueueSize);
  lidarPublish_ = lidarNode_.advertise<extendedkalmanfilters::LidarMeasurements>(gLidarTopic, gQueueSize);
}

void RosBagCreator :: read() {
  
  std::string sensor_type, rho_measured, phi_measured, rhodot_measured, time_stamp,
  x_ground_truth, y_ground_truth, vx_ground_truth, vy_ground_truth, yaw_groundtruth, 
  yaw_rate_groundtruth, x_measured, y_measured;

  std::ifstream finput(RadarDataFile);
  std::string line;
  std::stringstream string(line);
  while (getline(finput, line)) {
    std::stringstream string(line);
    std::getline(string, sensor_type, ',');
    if (sensor_type == "L") {

      std::string s_type;
      long long t;
      float x_m, y_m, x_gt, y_gt, vx_gt, vy_gt;
      std::getline(string, x_measured, ',');
      std::getline(string, y_measured, ',');
      std::getline(string, time_stamp, ',');
      std::getline(string, x_ground_truth, ',');
      std::getline(string, y_ground_truth, ',');
      std::getline(string, vx_ground_truth, ',');
      std::getline(string, vy_ground_truth, ',');
      std::getline(string, yaw_groundtruth, ',');
      std::getline(string, yaw_rate_groundtruth, ',');
      s_type = sensor_type;
      x_m = atof(x_measured.c_str());
      y_m = atof(y_measured.c_str());
      t = atof(time_stamp.c_str());
      x_gt = atof(x_ground_truth.c_str());
      y_gt = atof(y_ground_truth.c_str());
      vx_gt = atof(vx_ground_truth.c_str());
      vy_gt = atof(vy_ground_truth.c_str());
      lidarWrite(s_type, x_m, y_m, t, x_gt, y_gt, vx_gt, vy_gt);

    } else if (sensor_type == "R") {

      std::cout << "Radar Data" << std::endl;
      std::string s_type;
      long long t;
      float rho, phi, rhodot, x_gt, y_gt, vx_gt, vy_gt;
      std::getline(string, rho_measured, ',');
      std::getline(string, phi_measured, ',');
      std::getline(string, rhodot_measured, ',');
      std::getline(string, time_stamp, ',');
      std::getline(string, x_ground_truth, ',');
      std::getline(string, y_ground_truth, ',');
      std::getline(string, vx_ground_truth, ',');
      std::getline(string, vy_ground_truth, ',');
      std::getline(string, yaw_groundtruth, ',');
      std::getline(string, yaw_rate_groundtruth, ',');
      s_type = sensor_type;
      rho = atof(rho_measured.c_str());
      phi = atof(phi_measured.c_str());
      rhodot = atof(rhodot_measured.c_str());
      t = atof(time_stamp.c_str());
      x_gt = atof(x_ground_truth.c_str());
      y_gt = atof(y_ground_truth.c_str());
      vx_gt = atof(vx_ground_truth.c_str());
      vy_gt = atof(vy_ground_truth.c_str());
      radarWrite(s_type, rho, phi, rhodot, t, x_gt, y_gt, vx_gt, vy_gt);

    } else {
      std::cout << "Unknown Data!! exiting" << std::endl;
      break;
    }
  }
}

void RosBagCreator :: radarWrite(std::string& s_type, float rho, float phi, float rhodot, long long t, float x_gt, float y_gt, float vx_gt, float vy_gt) {
  radarMeasurement.sensor_type_ = s_type;
  radarMeasurement.rho_measured_ = rho;
  radarMeasurement.phi_measured_ = phi;
  radarMeasurement.rhodot_measured_ = rhodot;
  radarMeasurement.time_stamp_ = t;
  radarMeasurement.x_ground_truth_ = x_gt;
  radarMeasurement.y_ground_truth_ = y_gt;
  radarMeasurement.vx_ground_truth_ = vx_gt;
  radarMeasurement.vy_ground_truth_ = vy_gt;
  radarBag.write(gRadarBagName, ros::Time::now(), radarMeasurement);
  radarPublish_.publish(radarMeasurement);
}

void RosBagCreator :: lidarWrite(std::string& s_type, float x_m, float y_m, long long t, float x_gt, float y_gt, float vx_gt, float vy_gt) {
  lidarMeasurement.sensor_type_ = s_type;
  lidarMeasurement.x_measured_ = x_m;
  lidarMeasurement.y_measured_ = y_m;
  lidarMeasurement.time_stamp_ = t;
  lidarMeasurement.x_ground_truth_ = x_gt;
  lidarMeasurement.y_ground_truth_ = y_gt;
  lidarMeasurement.vx_ground_truth_ = vx_gt;
  lidarMeasurement.vy_ground_truth_ = vy_gt;
  lidarBag.write(gLidarBagName, ros::Time::now(), lidarMeasurement);
  lidarPublish_.publish(lidarMeasurement);
}


void RosBagCreator :: close() {
  radarBag.close();
  lidarBag.close();
}
