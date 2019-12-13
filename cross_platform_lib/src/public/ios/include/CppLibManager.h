
#import <Foundation/Foundation.h>
#include "config.hpp"

NS_ASSUME_NONNULL_BEGIN

@interface CppLibManager : NSObject

- (void)trigerLib:(NSInteger)number;

- (bool)initWithView:(nonnull NSObject *)view;

#ifdef BUILD_TEST
- (void)runUnitTests;
#endif

@end

NS_ASSUME_NONNULL_END
