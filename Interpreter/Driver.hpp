#include <iostream>
namespace Driver {
int Add(const int &v1, const int &v2) {
    return v1 + v2;
}

std::string Add(const std::string &v1, const std::string &v2) {
    return v1 + v2;
}

int Multiply(const int &v1, const int &v2) {
    return v1 * v2;
}

}  // namespace Driver
