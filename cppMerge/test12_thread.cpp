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

    cv.wait(lk);
    for (int k = 0; k < 4; ++k) {
        std::srand(std::time(nullptr));  // use current time as seed for random generator
        int random_time = 1 + std::rand() % 100;

        std::this_thread::sleep_for(std::chrono::milliseconds(random_time));
        ++i;
        std::cerr << "i=" << i << "\n";
    }
    std::cerr << std::endl;
}

void signals() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lk(cv_m);
        std::cerr << "Notifying...\n";
    }
    cv.notify_all();

    // std::this_thread::sleep_for(std::chrono::seconds(1));

    // {
    //     std::lock_guard<std::mutex> lk(cv_m);
    //     i = 1;
    //     std::cerr << "Notifying again...\n";
    // }
    // cv.notify_all();
}

int main() {
    std::thread t1(waits), t2(waits), t3(waits), t4(signals);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}