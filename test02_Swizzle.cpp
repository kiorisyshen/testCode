#include <iostream>

template <class TT, int A, int B>
class swizzle {
    float v[2];

   public:
    TT &operator=(const TT &rhs) {
        v[A] = rhs.x;
        v[B] = rhs.y;
        return *(TT *)this;
    }
    TT operator*(const TT &rhs) {
        float result[2];
        result[0] = v[0] * rhs[0];
        result[1] = v[1] * rhs[1];
        return TT(result[0], result[1]);
    }
    operator TT() const {
        return TT(v[A], v[B]);
    }
};

struct Vector2Type {
    union {
        float data[2];
        struct {
            float x, y;
        };
        swizzle<Vector2Type, 0, 1> xy;
        swizzle<Vector2Type, 1, 0> yx;
    };
    Vector2Type(){};
    Vector2Type(const float &_v)
        : x(_v), y(_v){};
    Vector2Type(const float &_x, const float &_y)
        : x(_x), y(_y){};
    operator float *() {
        return data;
    };
    operator const float *() const {
        return static_cast<const float *>(data);
    };

    friend std::ostream &operator<<(std::ostream &os, const Vector2Type &vec);
};

std::ostream &operator<<(std::ostream &os, const Vector2Type &vec) {
    os << "(" << vec[0] << ", " << vec[1] << ")";
    return os;
}

int main(int argc, char **argv) {
    Vector2Type vec1(1.0, 2.0);
    Vector2Type vec2(1.0, 2.0);
    Vector2Type result = vec1.xy * 2.0;
    std::cout << result << std::endl;
}