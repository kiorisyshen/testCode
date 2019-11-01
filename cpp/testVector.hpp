#include <iostream>
#include <vector>

class ctest {
public:
  std::vector<int> m_list;
  void func(std::vector<int> &out) { out = m_list; }
};

void RUN_test() {
  ctest ct;
  ct.m_list.push_back(5);

  std::vector<int> outList;
  ct.func(outList);
  for (auto v : outList) {
    std::cout << v << std::endl;
  }
  ct.m_list.clear();
  for (auto v : outList) {
    std::cout << v << std::endl;
  }
}