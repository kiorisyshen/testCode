#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int RUN_test() {
    Mat R = Mat::eye(Size(3, 3), CV_64F);
    std::cout << R << std::endl;

    R.row(2) = 2 * R.row(2);
    std::cout << R << std::endl;
    return 0;
}