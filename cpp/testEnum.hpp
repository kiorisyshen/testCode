#include <iostream>

enum testEnum0 {
    a0,
    b0,
    testEnum0_length
};

enum testEnum1 {
    a1,
    b1,
    c1,
    testEnum1_length
};

enum testEnum2 {
    a2,
    b2,
    c2,
    d2,
    e2,
    f2,
    testEnum2_length
};

class testClass{
    public:
    int id;
};

void printTestClass(const testClass &c){
    std::cout << "id: " << c.id << std::endl;
}

void RUN_test(){
    // std::cout << testEnum0_length << std::endl;
    // testClass *A = new testClass;
    // printTestClass(*A);
    // delete A;
}