#include <iostream>

template <class TT, int... Indexes>
class swizzle {
    // here sizeof...() is a function to query the number of parameter pack
    float v[sizeof...(Indexes)];

   public:
    TT &operator=(const TT &rhs) {
        int indexes[] = {Indexes...};  // unpack
        for (int i = 0; i < sizeof...(Indexes); i++) {
            v[indexes[i]] = rhs[i];  // access pack element
        }
        return *(TT *)this;
    }
    TT operator*(const TT &rhs) const {
        int indexes[] = {Indexes...};
        float result[sizeof...(Indexes)];
        for (size_t i = 0; i < sizeof...(Indexes); i++)
            result[i] = v[indexes[i]] * rhs[i];
        return TT(result[Indexes]...);
    }
    TT operator*(float &m) const {
        int indexes[] = {Indexes...};
        float result[sizeof...(Indexes)];
        for (size_t i = 0; i < sizeof...(Indexes); i++)
            result[i] = v[indexes[i]] * m;
        return TT(result[Indexes]...);
    }
    operator TT() const {
        // unpack
        return TT(v[Indexes]...);
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
};

// Vector3d
struct Vector3Type {
    union {
        float data[3];
        struct {
            float x, y, z;
        };
        swizzle<Vector2Type, 0, 1> xy;
        swizzle<Vector2Type, 1, 0> yx;
        swizzle<Vector2Type, 0, 2> xz;
        swizzle<Vector2Type, 2, 0> zx;
        swizzle<Vector2Type, 1, 2> yz;
        swizzle<Vector2Type, 2, 1> zy;
        swizzle<Vector3Type, 0, 1, 2> xyz;
        swizzle<Vector3Type, 1, 0, 2> yxz;
        swizzle<Vector3Type, 0, 2, 1> xzy;
        swizzle<Vector3Type, 2, 0, 1> zxy;
        swizzle<Vector3Type, 1, 2, 0> yzx;
        swizzle<Vector3Type, 2, 1, 0> zyx;
    };
    Vector3Type(){};
    Vector3Type(const float &_v)
        : x(_v), y(_v), z(_v){};
    Vector3Type(const float &_x, const float &_y, const float &_z)
        : x(_x), y(_y), z(_z){};
    operator float *() {
        return data;
    };
    operator const float *() const {
        return static_cast<const float *>(data);
    };
};

std::ostream &operator<<(std::ostream &os, const Vector3Type &vec) {
    os << "(" << vec[0] << ", " << vec[1] << ", " << vec[2] << ")";
    return os;
}

typedef Vector3Type Vec3D;

void testFunc(const Vec3D &qtn) {
    Vec3D result = qtn.xyz * 2.0;
    std::cout << result << std::endl;
}

int main(int argc, char **argv) {
    testFunc({1.0, 2.0, 3.0});

    Vec3D vec(3.0, 2.0, 1.0);
    Vec3D result = vec.xyz * 2.0;
    std::cout << result << std::endl;
}