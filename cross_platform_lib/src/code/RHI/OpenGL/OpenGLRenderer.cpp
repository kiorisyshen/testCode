
#include <GLES3/gl32.h>

#include <GLES2/gl2ext.h>

#include <unistd.h>
#include <iostream>
#include "OpenGLRenderer.hpp"

void OpenGLRenderer::initialize() {
    std::cout << "OpenGLRenderer::initialize" << std::endl;
    glClearDepthf(1.0f);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void OpenGLRenderer::renderFrame() {
    std::cout << "OpenGLRenderer::renderFrame" << std::endl;
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glFlush();
}