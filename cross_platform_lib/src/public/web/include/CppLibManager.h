// #include <emscripten/val.h>
#include <iostream>
#include <string>
#include "code/RHI/OpenGL/OpenGLRenderer.hpp"
#include "config.hpp"

namespace TestEngine {
namespace WebInterface {

class CppLibManager {
   public:
    CppLibManager() = default;
    bool trigerLib(int number);

    // For rendering
    void initializeLib();
    void renderFrame();

   private:
    OpenGLRenderer _oglRenderer;
};

}  // namespace WebInterface
}  // namespace TestEngine
