#include <iostream>
#include <string>

#define _ASSERT_GLUE(a, b) a##b
#define ASSERT_GLUE(a, b) _ASSERT_GLUE(a, b)

#define STATIC_ASSERT(expr)                                         \
    enum {                                                          \
        ASSERT_GLUE(g_assert_fail_, __LINE__) = 1 / (int)(!!(expr)) \
    }

void RUN_test() {
    STATIC_ASSERT(sizeof(float) == 1);  // should fail
}