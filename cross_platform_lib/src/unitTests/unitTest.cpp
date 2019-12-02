#include "unitTest.hpp"
#include <iostream>
#include "code/cppLib.hpp"

void runAllTests() {
    if (runSomething(3)) {
        std::cout << "Tests passed" << std::endl;
    } else {
        std::cout << "Tests failed" << std::endl;
    }
}