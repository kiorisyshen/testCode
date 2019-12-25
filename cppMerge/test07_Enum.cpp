#include <iostream>

template <typename T>
T endian_native_unsigned_int(T net_number) {
    T result = 0;

    for (size_t i = 0; i < sizeof(net_number); i++) {
        result <<= CHAR_BIT;
        result += ((reinterpret_cast<T *>(&net_number))[i] & UCHAR_MAX);
    }

    return result;
}

template <typename T>
T endian_net_unsigned_int(T native_number) {
    T result = 0;

    size_t i = sizeof(native_number);
    do {
        i--;
        (reinterpret_cast<uint8_t *>(&result))[i] = native_number & UCHAR_MAX;
        native_number >>= CHAR_BIT;
    } while (i != 0);

    return result;
}

namespace details {
constexpr int32_t i32(const char *s, int32_t v) {
    return *s ? i32(s + 1, v * 256 + *s) : v;
}
}  // namespace details

constexpr int32_t operator"" _i32(const char *s, size_t) {
    return details::i32(s, 0);
}

enum testE : int32_t {
    type1      = "TYP1"_i32,
    type2      = "TYP4"_i32,
    size_testE = 2,
};

enum testE1 {
    a = 0,
    b,
};

void enum2str(int32_t in_val, char *out_str) {
    int32_t t_v = endian_net_unsigned_int<int32_t>(in_val);
    char *t_str = reinterpret_cast<char *>(&t_v);
    out_str[0]  = t_str[0];
    out_str[1]  = t_str[1];
    out_str[2]  = t_str[2];
    out_str[3]  = t_str[3];
    out_str[4]  = '\0';
}

int main() {
    std::cout << testE::type1 << std::endl;
    std::cout << testE::type2 << std::endl;
    std::cout << testE::size_testE << std::endl
              << std::endl;

    char t1[5];
    enum2str(testE::type1, t1);
    char t2[5];
    enum2str(testE::type2, t2);

    std::cout << t1 << std::endl;
    std::cout << t2 << std::endl
              << std::endl;

    std::cout << testE1::a << std::endl;
    std::cout << testE1::b << std::endl;

    return 0;
}