
#include <GLES2/gl2.h>

#include <GLES2/gl2ext.h>

#include <unistd.h>
#include <iostream>
#include <vector>
#include "OpenGLESRenderer.hpp"
#include <android/log.h>

typedef void *FilePtr;

size_t GetSize(const FilePtr &fp) {
    FILE *_fp = static_cast<FILE *>(fp);

    long pos = ftell(_fp);
    fseek(_fp, 0, SEEK_END);
    size_t length = ftell(_fp);
    fseek(_fp, pos, SEEK_SET);

    return length;
}

static void OutputShaderErrorMessage(unsigned int shaderId) {
    int logSize, i;
    char *infoLog;

    // Get the size of the string containing the information log for the failed shader compilation message.
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);

    // Increment the size by one to handle also the null terminator.
    logSize++;

    // Create a char buffer to hold the info log.
    infoLog = new char[logSize];
    if (!infoLog) {
        return;
    }

    // Now retrieve the info log.
    glGetShaderInfoLog(shaderId, logSize, NULL, infoLog);

    // Write out the error message.
    for (i = 0; i < logSize; i++) {
        std::cerr << infoLog[i];
    }

    std::cerr << std::endl;

    // Pop a message up on the screen to notify the user to check the text file for compile errors.
    std::cerr << "Error compiling shader.  Check output error message." << std::endl;

    return;
}

static void OutputLinkerErrorMessage(unsigned int programId) {
    int logSize, i;
    char *infoLog;

    // Get the size of the string containing the information log for the failed shader compilation message.
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logSize);

    // Increment the size by one to handle also the null terminator.
    logSize++;

    // Create a char buffer to hold the info log.
    infoLog = new char[logSize];
    if (!infoLog) {
        return;
    }

    // Now retrieve the info log.
    glGetProgramInfoLog(programId, logSize, NULL, infoLog);

    // Write out the error message.
    for (i = 0; i < logSize; i++) {
        std::cerr << infoLog[i];
    }

    std::cerr << std::endl;

    // Pop a message up on the screen to notify the user to check the text file for linker errors.
    std::cerr << "Error compiling linker.  Check output error message." << std::endl;
}

std::string SyncOpenAndReadTextFileToString(const char *fileName) {
    std::string result;

    FilePtr fp = fopen(fileName, "r");
    if (!fp) {
        std::cerr << "Error in opening shader files: " << fileName << std::endl;
    } else {
        size_t length = GetSize(fp);
        std::cout << "Read file: " << fileName << std::endl;

        uint8_t m_pData[length + 1];
        length          = fread(m_pData, 1, length, static_cast<FILE *>(fp));
        m_pData[length] = '\0';

        std::cout << "Length: " << length << " bytes" << std::endl;

        fclose((FILE *)fp);
        fp = nullptr;

        char *content = reinterpret_cast<char *>(m_pData);

        if (content) {
            result = std::string(std::move(content));
        }
    }

    return result;
}

static bool LoadShaderFromString(const std::string content, const GLenum shaderType, GLuint &shader) {
    int status;

    // Create a shader object.
    shader = glCreateShader(shaderType);

    // Copy the shader source code strings into the shader objects.
    const char *pStr = content.c_str();
    glShaderSource(shader, 1, &pStr, NULL);

    // Compile the shaders.
    glCompileShader(shader);

    // Check to see if the shader compiled successfully.
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != 1) {
        // If it did not compile then write the syntax error message out to a text file for review.
        OutputShaderErrorMessage(shader);
        return false;
    }

    return true;
}

// ShaderID and Shader file name
typedef std::vector<std::pair<GLenum, std::string>> ShaderSourceList;

static bool LoadShaderProgram(const ShaderSourceList &source, GLuint &shaderProgram) {
    int status;

    // Create a shader program object.
    shaderProgram = glCreateProgram();

    for (auto it = source.cbegin(); it != source.cend(); it++) {
        GLuint shader;
        std::string filename = "src/code/Asset/Shaders/WebGL/";
        filename += it->second;
        std::string fileContent = SyncOpenAndReadTextFileToString(filename.c_str());

        status = LoadShaderFromString(fileContent, it->first, shader);
        if (!status) {
            std::cerr << "Error in loading shader file: " << filename << std::endl;
            std::cerr << fileContent << std::endl;
            return false;
        }

        // Attach the shader to the program object.
        glAttachShader(shaderProgram, shader);
        glDeleteShader(shader);
    }

    // Link the shader program.
    glLinkProgram(shaderProgram);

    // Check the status of the link.
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (status != 1) {
        // If it did not link then write the syntax error message out to a text file for review.
        OutputLinkerErrorMessage(shaderProgram);
        glDeleteProgram(shaderProgram);
        return false;
    }

    return true;
}

static GLuint shaderProgram;
static int width_;
static int height_;

void OpenGLESRenderer::initialize() {
//    std::cout << "OpenGLRenderer::initialize" << std::endl;
//    std::cout << "[OpenGL] " << glGetString(GL_VERSION) << std::endl;
//    std::cout << "[Vendor] " << glGetString(GL_VENDOR) << std::endl;
//    std::cout << "[Renderer] " << glGetString(GL_RENDERER) << std::endl;
//    std::cout << "[GLSL] " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    __android_log_write(ANDROID_LOG_INFO, "test", "OpenGLRenderer::initialize");

    std::string logInfo = "[OpenGL] "+ std::string((char *)glGetString(GL_VERSION));
    __android_log_write(ANDROID_LOG_INFO, "test", logInfo.c_str());

    logInfo = "[Vendor] "+ std::string((char *)glGetString(GL_VENDOR));
    __android_log_write(ANDROID_LOG_INFO, "test", logInfo.c_str());

    logInfo = "[Renderer] "+ std::string((char *)glGetString(GL_RENDERER));
    __android_log_write(ANDROID_LOG_INFO, "test", logInfo.c_str());

    logInfo = "[GLSL] "+ std::string((char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
    __android_log_write(ANDROID_LOG_INFO, "test", logInfo.c_str());

    width_ = -1;
    height_ = -1;

    glClearDepthf(1.0f);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // initialize shaders
    // ShaderSourceList list = {
    //     {GL_VERTEX_SHADER, "testShader.vert.glsl"},
    //     {GL_FRAGMENT_SHADER, "testShader.frag.glsl"}};

    // bool result = LoadShaderProgram(list, shaderProgram);
    // if (!result) {
    //     std::cerr << "Failed loading shader program!" << std::endl;
    // } else {
    //     std::cout << "Successfully load shader program!" << std::endl;
    // }

    // // Bind vPosition to attribute 0
    // glBindAttribLocation(shaderProgram, 0, "vPosition");
    // glBindAttribLocation(shaderProgram, 1, "vColor");

    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
}

void OpenGLESRenderer::renderFrame() {
    if (width_ > 0 && height_ > 0) {
        glViewport(0, 0, width_, height_);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glUseProgram(shaderProgram);

    // static GLfloat vVertices[] = {0.0f, 0.5f, 0.0f,
    //                               -0.5f, -0.5f, 0.0f,
    //                               0.5f, -0.5f, 0.0f};

    // static GLfloat vColor[] = {1.0f, 0.0f, 0.0f,
    //                            0.0f, 1.0f, 0.0f,
    //                            0.0f, 0.0f, 1.0f};

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    // glEnableVertexAttribArray(0);

    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, vColor);
    // glEnableVertexAttribArray(1);

    // glDrawArrays(GL_TRIANGLES, 0, 3);

    glFlush();
}

void OpenGLESRenderer::resizeView(int width, int height) {
    width_ = width;
    height_ = height;
}