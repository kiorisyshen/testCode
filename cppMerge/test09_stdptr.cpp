#include <iostream>

struct test {
    int value = 0;
};

int main() {
    std::shared_ptr<test> p1 = std::make_shared<test>();

    p1->value = 100;

    std::shared_ptr<test> p2 = std::make_shared<test>(*p1);

    p2->value += 50;

    std::cout << "p1: " << p1 << ", value: " << p1->value << std::endl;
    std::cout << "p2: " << p2 << ", value: " << p2->value << std::endl;
}