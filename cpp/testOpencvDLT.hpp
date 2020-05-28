#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/sfm/numeric.hpp>

using namespace std;

template <typename newT>
void homogeneousToEuclidean(const cv::Mat &_X, cv::Mat &_x) {
    int d = _X.rows - 1;

    const cv::Mat_<newT> &X_rows = _X.rowRange(0, d);
    const cv::Mat_<newT> h       = _X.row(d);

    const newT *h_ptr = h[0], *h_ptr_end = h_ptr + h.cols;
    const newT *X_ptr = X_rows[0];
    newT *x_ptr       = _x.ptr<newT>(0);
    for (; h_ptr != h_ptr_end; ++h_ptr, ++X_ptr, ++x_ptr) {
        const newT *X_col_ptr = X_ptr;
        newT *x_col_ptr = x_ptr, *x_col_ptr_end = x_col_ptr + d * _x.step1();
        for (; x_col_ptr != x_col_ptr_end; X_col_ptr += X_rows.step1(), x_col_ptr += _x.step1())
            *x_col_ptr = (*X_col_ptr) / (*h_ptr);
    }
}

void homogeneousToEuclidean(const cv::InputArray _X, cv::OutputArray _x) {
    // src
    const cv::Mat X = _X.getMat();

    // dst
    _x.create(X.rows - 1, X.cols, X.type());
    cv::Mat x = _x.getMat();

    // type
    if (X.depth() == CV_32F) {
        homogeneousToEuclidean<float>(X, x);
    } else {
        homogeneousToEuclidean<double>(X, x);
    }
}

void triangulateDLT(const cv::Vec2d &xl, const cv::Vec2d &xr,
                    const cv::Matx34d &Pl, const cv::Matx34d &Pr,
                    cv::Vec3d &point3d) {
    cv::Matx44d design;
    for (int i = 0; i < 4; ++i) {
        design(0, i) = xl(0) * Pl(2, i) - Pl(0, i);
        design(1, i) = xl(1) * Pl(2, i) - Pl(1, i);
        design(2, i) = xr(0) * Pr(2, i) - Pr(0, i);
        design(3, i) = xr(1) * Pr(2, i) - Pr(1, i);
    }

    cv::Vec4d XHomogeneous;
    cv::SVD::solveZ(design, XHomogeneous);

    homogeneousToEuclidean(XHomogeneous, point3d);
}

const double deltaTx     = 4.0;
const double deltaTy     = 4.0;
const double focusLength = sqrt(2.0);
const double imgWidth    = 4.0;
const double imgHeight   = 4.0;

int RUN_test() {
    cv::Point2d x1(imgWidth * 3.0 / 4.0, imgHeight * 3.0 / 4.0);
    cv::Point2d x2(imgWidth / 4.0, imgHeight / 4.0);
    cv::Mat K = (cv::Mat_<double>(3, 3) << focusLength, 0, imgWidth * 0.5, 0, focusLength, imgHeight * 0.5, 0, 0, 1.0);
    cv::Mat R1, R2;
    cv::Mat T1, T2;

    {
        double yaw    = 0;
        double roll   = 0;
        double pitch  = 0;
        cv::Mat euler = (cv::Mat_<double>(1, 3) << pitch, roll, yaw);
        cv::Rodrigues(euler, R1);
        cv::Rodrigues(euler, R2);

        T1 = (cv::Mat_<double>(3, 1) << 0, 0, 0);
        T2 = (cv::Mat_<double>(3, 1) << deltaTx, deltaTy, 0);
    }

    {  // original
        cv::Mat tmpRa, tmpRb, mTa, mTb;
        R1.convertTo(tmpRa, CV_64F);
        R2.convertTo(tmpRb, CV_64F);
        T1.convertTo(mTa, CV_64F);
        T2.convertTo(mTb, CV_64F);
        mTa = -tmpRa * mTa;
        mTb = -tmpRb * mTb;
        cv::Mat trans_mat_a, trans_mat_b;
        hconcat(K * tmpRa, K * mTa, trans_mat_a);
        hconcat(K * tmpRb, K * mTb, trans_mat_b);

        cv::Point2d xa(x1.x, x1.y);
        cv::Point2d xb(x2.x, x2.y);

        cv::Vec3d point3d;
        triangulateDLT(xa, xb, trans_mat_a, trans_mat_b, point3d);
        std::cout << point3d << std::endl;
    }

    {  // new
    }

    return 0;
}