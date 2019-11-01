#include <iostream>
#include <string>

void RUN_test() {
    std::string str1 = "test1";
    printf("1 std::string: "); printf("%s", str1.c_str());
    std::cout << "1 c_str(): " << str1.c_str();

    std::string str2 = "test2";
    std::cout << "2 std::string: " << str2;
    std::cout << "2 c_str(): " << str2.c_str();

    unsigned char* const addr = new unsigned char [15];
    uint32_t offset = 0;

    strcpy((char*)(addr+offset), str1.c_str());
    std::cout << "addr: " << addr;
    offset += (uint32_t)str1.size()+1;
    std::cout << "offset: " << offset;

    strcpy((char*)(addr+offset), str2.c_str());
    std::cout << "addr: " << addr;

    delete[] addr;
}