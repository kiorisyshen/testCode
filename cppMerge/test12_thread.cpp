#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>

std::condition_variable cv;
std::mutex cv_m;  // This mutex is used for three purposes:
                  // 1) to synchronize accesses to i
                  // 2) to synchronize accesses to std::cerr
                  // 3) for the condition variable cv
int i = 0;

void waits() {
    std::unique_lock<std::mutex> lk(cv_m);
    std::cerr << "Start waits()... \n";

    // cv.wait(lk);
    for (int k = 0; k < 4; ++k) {
        std::cerr << "i=" << i << "\n";
    }
}

void signals() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lk(cv_m);
        std::cerr << "Notifying...\n";
    }
    cv.notify_all();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    {
        std::lock_guard<std::mutex> lk(cv_m);
        i = 1;
        std::cerr << "Notifying again...\n";
    }
    cv.notify_all();
}

int main() {
    std::thread t1(waits), t2(waits), t3(waits);
    t1.join();
    t2.join();
    t3.join();
    // t4.join();
}