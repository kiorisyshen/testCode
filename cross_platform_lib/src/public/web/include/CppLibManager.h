// #include <emscripten/val.h>
#include <iostream>
#include <string>
#include "config.hpp"

namespace TestEngine {
namespace WebInterface {

class CppLibManager {
   public:
    CppLibManager() = default;
    bool trigerLib(int number);
};

}  // namespace WebInterface
}  // namespace TestEngine
