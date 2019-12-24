#include <cstdint>
#include <iostream>

void freeArray(uint8_t *&array) {
    delete[] array;
    array = nullptr;
}

int main() {
    // uint8_t *constmemBlock1  = new uint8_t[11];
    uint8_t *memBlock2 = new uint8_t[12];
    // const uint8_t *memBlock3 = new uint8_t[13];

    // memBlock1 = memBlock2;   // no
    // memBlock3 = memBlock2;   // ok

    // memBlock1++;         // no
    // memBlock3[2] = 0;    // no

    std::cout << "memBlock2: " << std::endl;
    for (int i = 0; i < 12; ++i) {
        memBlock2[i] = i;
        std::cout << i << ": " << memBlock2[i] << std::endl;
    }

    // std::cout << "memBlock2: " << &memBlock2 << std::endl;
    freeArray(memBlock2);
    if (memBlock2 == nullptr) {
        std::cout << &memBlock2 << ", is nullptr" << std::endl;
    } else {
        std::cout << memBlock2 << ", not nullptr" << std::endl;
    }

    // delete[] memBlock2;
    // memBlock2 = nullptr;
    // if (memBlock2 == nullptr) {
    //     std::cout << &memBlock2 << ", is nullptr" << std::endl;
    // } else {
    //     std::cout << memBlock2 << ", not nullptr" << std::endl;
    // }

    return 0;
}