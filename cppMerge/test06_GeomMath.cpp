#include <iostream>
#include "eigen/Eigen/Eigen"

template <typename T, int row, int col>
using Matrix = Eigen::Matrix<T, row, col>;

// ------------------------------
// - Vector (Column default)
// ------------------------------
using Vecotr2d = Eigen::Vector2d;
using Vector3d = Eigen::Vector3d;
using Vector4d = Eigen::Vector4d;

using Vecotr2f = Eigen::Vector2f;
using Vector3f = Eigen::Vector3f;
using Vector4f = Eigen::Vector4f;

using Vecotr2i = Eigen::Vector2i;
using Vector3i = Eigen::Vector3i;
using Vector4i = Eigen::Vector4i;

using VectorXd = Eigen::VectorXd;
using VectorXf = Eigen::VectorXf;
using VectorXi = Eigen::VectorXi;

// ------------------------------
// - Matrix (Column major storage)
// ------------------------------
using Matrix3x3d = Eigen::Matrix3d;
using Matrix4x4d = Eigen::Matrix4d;

using Matrix3x3f = Eigen::Matrix3f;
using Matrix4x4f = Eigen::Matrix4f;

using Matrix3x3i = Eigen::Matrix3i;
using Matrix4x4i = Eigen::Matrix4i;

using MatrixXd = Eigen::MatrixXd;
using MatrixXf = Eigen::MatrixXf;
using MatrixXi = Eigen::MatrixXi;

/**
 * @brief Build view matrix in left-hand coordinates
 *      y  z
 *      | /
 *      |/
 *      ------ x
 * @param result 
 * @param position 
 * @param target 
 * @param up 
 */
inline void BuildViewLHMatrix(Matrix4x4f &result, const Vector3f position, const Vector3f target, const Vector3f up) {
    Vector3f zAxis, xAxis, yAxis;
    float result1, result2, result3;

    zAxis = target - position;
    zAxis.normalize();

    std::cout << "zAxis:" << std::endl
              << zAxis << std::endl;

    xAxis = up.cross(zAxis);
    xAxis.normalize();

    std::cout << "xAxis:" << std::endl
              << xAxis << std::endl;

    yAxis = zAxis.cross(xAxis);

    std::cout << "yAxis:" << std::endl
              << yAxis << std::endl;

    result1 = -xAxis.dot(position);

    result2 = -yAxis.dot(position);

    result3 = -zAxis.dot(position);

    // Set the computed values in the view matrix.
    result << xAxis[0], xAxis[1], xAxis[2], result1,
        yAxis[0], yAxis[1], yAxis[2], result2,
        zAxis[0], zAxis[1], zAxis[2], result3,
        0, 0, 0, 1;
}

int main() {
    Matrix4x4f lhViewM;
    Vector3f pos(-1, -1, -1);
    Vector3f target(0, 0, 0);
    Vector3f up(0, 1, 0);
    Vector3f testV;
    testV << 1, 0, -1;
    testV.normalize();

    BuildViewLHMatrix(lhViewM, pos, target, up);

    Vector4f worldPt;
    worldPt << (pos + testV), 1;
    std::cout << "worldPt: " << std::endl
              << worldPt << std::endl;
    std::cout << "lhViewM: " << std::endl
              << lhViewM << std::endl;
    std::cout << "resultPt: " << std::endl
              << lhViewM * worldPt << std::endl;
    return 0;
}