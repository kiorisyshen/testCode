#include <iostream>
#include "eigen/Eigen/Dense"

int main() {
    Eigen::Vector3f v(1.0, 3.5, 1.2);
    Eigen::Matrix4f m;
    m << 1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16;
    Eigen::Matrix4d m1;
    m1 << 1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16;

    std::cout << "sizeof(Eigen::Vector3f): " << sizeof(v) << std::endl;
    std::cout << "sizeof(Eigen::Matrix4f): " << sizeof(m) << std::endl
              << std::endl;

    std::cout << "Content m: " << m << std::endl;
    std::cout << "Content m1: " << m1 << std::endl
              << std::endl;

    std::cout << "In memory content m: " << std::endl;
    std::cout << "Size: " << m.size() << ", sizeof(m.data()): " << sizeof(m.data()) << std::endl;
    for (int i = 0; i < m.size(); i++)
        std::cout << *(m.data() + i) << "  ";
    std::cout << std::endl;

    std::cout << "In memory content m1: " << std::endl;
    std::cout << "Size: " << m1.size() << ", sizeof(m1.data()): " << sizeof(m1.data()) << std::endl;
    for (int i = 0; i < m1.size(); i++)
        std::cout << *(m1.data() + i) << "  ";
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "force memory content m1: " << std::endl;
    std::cout << "Size: " << m1.size() << ", sizeof(m1.data()): " << sizeof(m1.data()) << std::endl;
    double *forceM1 = m1.data();
    for (int i = 0; i < m1.size(); i++)
        std::cout << *(forceM1 + i) << "  ";
    std::cout << std::endl;
    std::cout << std::endl;

    return 0;
}