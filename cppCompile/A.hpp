#pragma once
#include <iostream>

class A {
   private:
    /* data */
   public:
    friend std::ostream &operator<<(std::ostream &out, A obj) {
        obj.print();
        return out;
    }

    void print();
};
