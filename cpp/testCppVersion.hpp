#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1600)
// OK
#else
#error "C++11 is not supported"
#endif

static int test() { return 0; }

void RUN_test() { auto res = test(); }
