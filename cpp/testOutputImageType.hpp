#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

int RUN_test() {
  cv::Mat imgTmp = cv::imread("area_1_0_0.png", IMREAD_UNCHANGED);
  std::cout << imgTmp.type() << std::endl;

  return 0;
}