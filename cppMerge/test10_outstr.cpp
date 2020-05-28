#include <iostream>
#include <ostream>
#include <sstream>

class testStr {
   public:
    std::string value = "lol";

    std::string toString() {
        // std::ostream outS;
        std::ostringstream SS;
        // SS << outS.rdbuf();
        SS << *this << " from toString." << std::endl;
        // std::cout << *this;
        return SS.str();
    }

    friend std::ostream &operator<<(std::ostream &out, const testStr &testStrObj) {
        out << testStrObj.value << " from ostream." << std::endl;
        return out;
    }
};

int main() {
    testStr a;
    std::cout << a;
    std::cout << a.toString();

    std::string msg = "";
    const char *m1  = "hello";
    const char *m2  = " string";
    msg += m1;
    msg += m2;
    std::cout << msg << std::endl;
}