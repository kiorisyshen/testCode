#include <unistd.h>
#include <chrono>
#include <iostream>

int main() {
    double fps = 60.0;
    // std::chrono::duration<double> lag(1.0 / fps);
    double lag = 1.0 / fps;

    auto start = std::chrono::steady_clock::now();
    sleep(3);
    auto end = std::chrono::steady_clock::now();
}