
#include <GLES3/gl32.h>

#include <GLES2/gl2ext.h>

#include <unistd.h>
#include <iostream>
#include "OpenGLRenderer.hpp"

typedef void *FilePtr;

size_t GetSize(const FilePtr &fp) {
    FILE *_fp = static_cast<FILE *>(fp);

    long pos = ftell(_fp);
    fseek(_fp, 0, SEEK_END);
    size_t length = ftell(_fp);
    fseek(_fp, pos, SEEK_SET);

    return length;
}

void OpenGLRenderer::initialize() {
    std::cout << "OpenGLRenderer::initialize" << std::endl;
    glClearDepthf(1.0f);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // initialize shaders
    std::string vertFile = "src/code/Asset/Shaders/WebGL/testShader.vert.glsl";

    FilePtr fp = fopen(vertFile.c_str(), "r");
    if (!fp) {
        std::cerr << "Error in opening shader files: " << vertFile << std::endl;
    } else {
        size_t length = GetSize(fp);
        std::cout << "Open file: " << vertFile << std::endl;
        std::cout << "Length: " << length << std::endl;
    }
}

void OpenGLRenderer::renderFrame() {
    // std::cout << "OpenGLRenderer::renderFrame" << std::endl;
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glFlush();
}