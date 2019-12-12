#pragma once

#include <string>

class OpenGLESRenderer {
   public:
    static void initialize();
    static int initializeShaderProgramFromString(std::string vertStr, std::string fragStr);
    static void renderFrame();
    static void resizeView(int width, int height);
};