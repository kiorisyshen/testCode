#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 255);

unsigned char random_char() {
    return static_cast<unsigned char>(dis(gen));
}

std::string generate_hex(const unsigned int len) {
    std::stringstream ss;
    for (auto i = 0; i < len; i++) {
        const auto rc = random_char();
        std::stringstream hexstream;
        hexstream << std::hex << int(rc);
        auto hex = hexstream.str();
        ss << (hex.length() < 2 ? '0' + hex : hex);
    }
    return ss.str();
}

int main() {
    long numLoop   = 100000000;
    long block     = 100;
    long iterBlock = numLoop / block;

    int reachBlock = 1;
    std::unordered_set<std::string> uuidSet_0;
    for (long i = 0; i < numLoop; i++) {
        std::string tmpStr = generate_hex(32);

        if (uuidSet_0.find(tmpStr) != uuidSet_0.end()) {
            std::cout << "Found at i: " << i << std::endl;
            return -1;
        } else {
            uuidSet_0.emplace(tmpStr);
        }

        if (i > iterBlock * reachBlock) {
            std::cout << "Percentage: " << reachBlock << std::endl;
            ++reachBlock;
        }
    }
    std::cout << "Successful" << std::endl;
}