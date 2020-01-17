#pragma once
#include <iostream>

class B {
   private:
    /* data */
   public:
    friend std::ostream &operator<<(std::ostream &out, B obj) {
        obj.print();
        return out;
    }

    void print();
};
