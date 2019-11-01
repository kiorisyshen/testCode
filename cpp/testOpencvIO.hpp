#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

string type2str(int type) {
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

void printMatInfo(Mat &img_){
    double min, max;
    cv::minMaxLoc(img_, &min, &max);
    cout << "In Mat Min: " << min << " Max: " << max << endl;
    cout << type2str(img_.type()) << endl;
}

int RUN_test(){
    int testType = -1;
    cout << testType << " " << type2str(testType) << endl;

    Mat img(Size(200,200), CV_32FC1);
    cout << img.type() << " " << CV_32FC1 << endl;
    Mat roi_1(img, Rect(0,0,100,100));
    roi_1 = Scalar(100);
    Mat roi_2(img, Rect(100,0,100,100));
    roi_2 = Scalar(200);
    Mat roi_3(img, Rect(0,100,100,100));
    roi_3 = Scalar(-100);
    Mat roi_4(img, Rect(100,100,100,100));
    roi_4 = Scalar(400);

    imwrite("img_testOcvIO.tif", img);

    Mat img2(Size(200,200), CV_8UC1);
    Mat roi2_1(img2, Rect(0,0,100,100));
    roi2_1 = Scalar(-100);
    Mat roi2_2(img2, Rect(100,0,100,100));
    roi2_2 = Scalar(0);
    Mat roi2_3(img2, Rect(0,100,100,100));
    roi2_3 = Scalar(100);
    Mat roi2_4(img2, Rect(100,100,100,100));
    roi2_4 = Scalar(65535);

    imwrite("img_testOcvIO.png", img2);
    

    Mat img_oldTile;
    try {
        img_oldTile = imread("img_oldTile.png", IMREAD_UNCHANGED);
        printMatInfo(img_oldTile);
    } catch (runtime_error& ex) {
        fprintf(stderr, "Exception in reading img_oldTile.png: %s\n", ex.what());
        return 1;
    }

    Mat img_png;
    try {
        img_png = imread("img_testOcvIO.png", IMREAD_UNCHANGED);
        printMatInfo(img_png);
    } catch (runtime_error& ex) {
        fprintf(stderr, "Exception in reading img_testOcvIO.png: %s\n", ex.what());
        return 1;
    }

    Mat img_in;
    try {
        img_in = imread("img_testOcvIO.tif", IMREAD_UNCHANGED);
        printMatInfo(img_in);
    } catch (runtime_error& ex) {
        fprintf(stderr, "Exception in reading img_testOcvIO.tif: %s\n", ex.what());
        return 1;
    }

    Mat img_ = imread("/Users/shen/Library/Developer/CoreSimulator/Devices/84D7F36E-A5C0-4B00-AA2C-0DD3C4B208CE/data/Containers/Bundle/Application/D6CBD2DD-5F85-4784-A831-83E1243D6819/stDebug-terrain.app/testImg10.bundle/DJI_0001.JPG");
    cout << img_.size << endl;

    return 0;
}