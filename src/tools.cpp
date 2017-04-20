#include <iostream>
#include <cmath>
#include "tools.h"


using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  /**
  Calculate the RMSE here.
  */
  VectorXd rmse(4);
  rmse << 0, 0, 0, 0;

  // Make sure estimation vector size is not zero and,
  // the estimation vector size is equal to the ground truth vector size
  if (estimations.size() != ground_truth.size()
    || estimations.size() == 0){
    std::cout << "Invalid estimation or ground_truth data" << std::endl;
    return rmse;
  }

  //accumulate squared residuals
  for (unsigned int i = 0; i < estimations.size(); ++i){

    VectorXd residual = estimations[i] - ground_truth[i];

    //coefficient-wise multiplication
    residual = residual.array()*residual.array();
    rmse += residual;
  }

  //calculate the mean
  rmse = rmse / estimations.size();

  //calculate the squared root
  rmse = rmse.array().sqrt();

  //return the result
  return rmse;
}

double Tools::NormalizeAng(const double& angle){
  const double Max = M_PI;
  const double Min = -M_PI;

  return angle < Min
    ? Max + std::fmod(angle - Min, Max - Min)
    : std::fmod(angle - Min, Max - Min) + Min;
  //return atan2(sin(angle), cos(angle));
}