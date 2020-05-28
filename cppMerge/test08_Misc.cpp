#include <cstring>
#include <iostream>

class test {
   public:
    virtual void dump(std::ostream &out) const = 0;
};

class test2 : public test {
   public:
    void dump(std::ostream &out) const override final {
        out << "hello!" << std::endl;
    }
};

class test3 : public test2 {
   public:
    virtual void testAB() const = 0;
};

class test4 : public test3 {
   public:
    void testAB() const {
        std::cout << "hello again!" << std::endl;
    }
};

class testRefMember {
   public:
    void setRef(const std::string &str) {
        m_str = &str;
    }

    void print() {
        std::cout << *m_str << std::endl;
    }

   private:
    const std::string *m_str;
};

int main() {
    testRefMember testRef;
    std::string demoStr = "hello ref member";
    testRef.setRef(demoStr);
    testRef.print();
    demoStr = "hello ref member 2";
    testRef.print();

    std::string a = "hello str move";
    std::string b;

    std::cout << "Before:" << std::endl;
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;

    b = std::move(a);

    std::cout << "After:" << std::endl;
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;

    test2 t2;
    test &t = t2;
    t.dump(std::cout);

    test4 t4;
    test3 &t3 = t4;
    t3.dump(std::cout);
    t3.testAB();

    std::cout << std::endl;
    std::cout << "Time test: " << std::endl;

    int year;
    time_t sekunnit;
    struct tm *p;
    time(&sekunnit);
    p = localtime(&sekunnit);

    year = p->tm_year;
    std::cout << "Year: " << year << std::endl;

    return 0;
}