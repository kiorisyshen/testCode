#import "public/ios/include/CppLibManager.h"
#include <iostream>
#include "code/cppLib.hpp"

@implementation CppLibManager

- (void)trigerLib:(NSInteger)number {
    if (runSomething((int)number)) {
        std::cout << "trigerLib Succeed" << std::endl;
    } else {
        std::cout << "trigerLib Failed" << std::endl;
    }
}

#ifdef BUILD_TEST

#include "unitTests/unitTest.hpp"
- (void)runUnitTests {
    runAllTests();
}

#endif

@end
