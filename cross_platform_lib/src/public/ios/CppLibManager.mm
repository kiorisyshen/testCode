#import "public/ios/include/CppLibManager.h"
#import <MetalKit/MetalKit.h>
#include <iostream>
#include "code/RHI/Metal/MetalRenderer.h"
#include "code/cppLib.hpp"

@implementation CppLibManager {
    MTKView *_view;

    MetalRenderer *_renderer;
}

 - (bool)initWithView:(nonnull NSObject *)view {
    _view        = (MTKView *)view;

    _view.device = MTLCreateSystemDefaultDevice();
    if (!_view.device) {
        NSLog(@"Metal is not supported on this device");
        return false;
    }

    _renderer = [[MetalRenderer alloc] initWithMetalKitView:_view];

    if (!_renderer) {
        NSLog(@"Renderer failed initialization");
        return false;
    }

    // Initialize our renderer with the view size
    [_renderer mtkView:_view drawableSizeWillChange:_view.drawableSize];

    _view.delegate = _renderer;

    return true;
}

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
