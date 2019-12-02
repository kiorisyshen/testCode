#include "public/include/pubCppLib.hpp"
#include <iostream>
#include "cppLib.hpp"

void trigerLib(int in_INT) {
    if (runSomething(in_INT)) {
        std::cout << "Succeed" << std::endl;
    } else {
        std::cout << "Failed" << std::endl;
    }
}
