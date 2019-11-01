#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

int RUN_test(){
    Mat img(Size(200,200), CV_16UC1);
    img = Scalar(10000);
    imwrite("/Users/shen/Learning/test/cpp/build/img_Calc0.png", img);

    img -= 15000;
    imwrite("/Users/shen/Learning/test/cpp/build/img_Calc1.png", img);
    
    return 0;
}