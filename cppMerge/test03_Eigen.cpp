#include <iostream>
#include "eigen/Eigen/Dense"

template <typename T, int row, int col>
using Matrix = Eigen::Matrix<T, row, col>;

template <typename T, int N>
inline void BuildIdentityMatrix(Matrix<T, N, N> &matrix) {
    matrix = Matrix<T, N, N>::Identity();
}

template <typename T>
class Quaternion {
   public:
    Eigen::Matrix<T, 4, 1> m_Value;

    Quaternion() {
        std::cout << "Quaternion constructor!" << std::endl;
        m_Value.Zero();
    }
    Quaternion(T a, T b, T c, T d) {
        std::cout << "Quaternion constructor!" << std::endl;
        m_Value << a, b, c, d;
    }
    Quaternion(const Eigen::Matrix<T, 4, 1> &rhs) {
        std::cout << "Quaternion constructor!" << std::endl;
        m_Value = rhs;
    }

    Quaternion(const Quaternion &lhs) {
        std::cout << "Quaternion copy constructor!" << std::endl;
        m_Value = lhs.m_Value;
    }

    Quaternion(Quaternion &&rhs) {
        std::cout << "Quaternion move constructor!" << std::endl;
        m_Value = std::move(rhs.m_Value);
    }

    Quaternion &operator=(const Quaternion &lhs) {
        m_Value = lhs;
        return *this;
    }

    Quaternion &operator=(Quaternion &&rhs) {
        m_Value = std::move(rhs.m_Value);
        return *this;
    }

    Quaternion<T> operator*(const Quaternion<T> &b) {
        Eigen::Matrix<T, 4, 4> matTmp;
        matTmp << m_Value[0], -m_Value[1], -m_Value[2], -m_Value[3],
            m_Value[1], m_Value[0], m_Value[3], -m_Value[2],
            m_Value[2], -m_Value[3], m_Value[0], -m_Value[1],
            m_Value[3], m_Value[2], -m_Value[1], m_Value[0];

        return Quaternion<T>(matTmp * b.m_Value);
    }

    ~Quaternion() {
        std::cout << "Quaternion de-constructor!" << std::endl;
    }
};

int main() {
    {
        Eigen::Vector4f v_t(1.0, 1.0, 1.0, 1.0);
        std::cout << v_t << std::endl;

        Eigen::Vector3f va(1, 1, 1);
        Eigen::Vector3f vb(1, 2, 3);
        std::cout << vb.dot(va) << std::endl;

        Eigen::Vector3f v(1.0, 3.5, 1.2);
        Matrix<float, 3, 1> v1(1.0, 3.5, 1.2);
        std::cout << "Vector: " << v1 << std::endl;

        Matrix<float, 3, 3> m3;
        // m3 = Matrix<float, 3, 3>::Identity();
        // m3.setIdentity();
        BuildIdentityMatrix(m3);
        std::cout << "m3: " << std::endl
                  << m3 << std::endl;

        Eigen::Vector3f vCol = m3.col(0);
        std::cout << "vCol: " << vCol << std::endl;

        vCol << 3, 2, 1;
        m3.col(0) = vCol;
        std::cout << "Replace m3 first col: " << m3 << std::endl;

        Eigen::Matrix4f m;
        m << 1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16;

        Eigen::Matrix3f mt;
        mt.col(0) = v;
        std::cout << "Content mt: " << mt << std::endl;

        Eigen::Matrix4d m1;
        m1 << 1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16;

        std::cout << "sizeof(Eigen::Vector3f): " << sizeof(v) << std::endl;
        std::cout << "sizeof(Eigen::Matrix4f): " << sizeof(m) << std::endl;
        std::cout << "sizeof(Eigen::Matrix4d): " << sizeof(m1) << std::endl
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
        std::cout << "Size: " << m1.size() << ", sizeof(*m1.data()): " << sizeof(*m1.data()) << std::endl;
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
    }

    {
        Quaternion<float> a;
        Quaternion<float> b(1, 2, 3, 4);

        Quaternion<float> c = a * b;
        Quaternion<float> d = std::move(a);
    }

    return 0;
}