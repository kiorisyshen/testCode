#include <iostream>
#include <string>

class funcBase {
public:
  virtual bool operator()(int num) = 0;
};

class funcDerived : public funcBase {
public:
  std::string content;
  bool operator()(int num) {
    std::cout << content << std::endl;
    std::cout << num << std::endl;
    return true;
  }
};

class computer {
public:
  computer(funcBase &baseFunc) : m_BaseFunc(baseFunc) {}
  int m_nCount = 2;
  funcBase &m_BaseFunc;

  void run() { m_BaseFunc(m_nCount); }
};

// Main function
void RUN_test() {
  funcDerived fd;
  computer c0(fd);

  fd.content = "fd";
  c0.run();
}
