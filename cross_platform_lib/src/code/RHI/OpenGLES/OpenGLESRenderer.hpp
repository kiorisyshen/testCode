#pragma once

class OpenGLESRenderer {
   public:
    static void initialize();
    static void renderFrame();
    static void resizeView(int width, int height);
};