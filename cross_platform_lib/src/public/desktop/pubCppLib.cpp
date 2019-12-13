#include "public/desktop/include/pubCppLib.hpp"
#include <iostream>
#include "code/cppLib.hpp"

void trigerLib(int in_INT) {
    if (runSomething(in_INT)) {
        std::cout << "trigerLib Succeed" << std::endl;
    } else {
        std::cout << "trigerLib Failed" << std::endl;
    }
}

#ifdef BUILD_TEST

#include "unitTests/unitTest.hpp"
void runUnitTests() {
    runAllTests();
}

#endif