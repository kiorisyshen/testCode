#include "GraphicsManager.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <GLES3/gl32.h>

#define GLAD_GL_ARB_compute_shader 0

#include <GLES2/gl2ext.h>

using namespace newbieGE;
using namespace std;

#define SHADER_ROOT "Shaders/WebGL/"

#define VS_BASIC_SOURCE_FILE SHADER_ROOT "basic.vert.glsl"
#define PS_BASIC_SOURCE_FILE SHADER_ROOT "basic.frag.glsl"

static void OutputShaderErrorMessage(unsigned int shaderId, const char *shaderFilename) {
    int logSize, i;
    char *infoLog;
    ofstream fout;

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

    // Open a file to write the error message to.
    fout.open("shader-error.txt");

    // Write out the error message.
    for (i = 0; i < logSize; i++) {
        fout << infoLog[i];
        cerr << infoLog[i];
    }

    // Close the file.
    fout.close();
    cerr << endl;

    // Pop a message up on the screen to notify the user to check the text file for compile errors.
    cerr << "Error compiling shader.  Check shader-error.txt for message." << shaderFilename << endl;

    return;
}

static void OutputLinkerErrorMessage(unsigned int programId) {
    int logSize, i;
    char *infoLog;
    ofstream fout;

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

    // Open a file to write the error message to.
    fout.open("linker-error.txt");

    // Write out the error message.
    for (i = 0; i < logSize; i++) {
        fout << infoLog[i];
        cerr << infoLog[i];
    }

    // Close the file.
    fout.close();
    cerr << endl;

    // Pop a message up on the screen to notify the user to check the text file for linker errors.
    cerr << "Error compiling linker.  Check linker-error.txt for message." << endl;
}

static bool LoadShaderFromFile(const char *filename, const GLenum shaderType, GLuint &shader) {
    std::string cbufferShaderBuffer;
    std::string commonShaderBuffer;
    std::string shaderBuffer;
    int status;

    // // Load the shader source file into a text buffer.
    // shaderBuffer = g_pAssetLoader->SyncOpenAndReadTextFileToString(filename);
    // if (shaderBuffer.empty()) {
    //     return false;
    // }

    // shaderBuffer = cbufferShaderBuffer + commonShaderBuffer + shaderBuffer;

    if (filename == VS_BASIC_SOURCE_FILE) {
        shaderBuffer =
            "attribute vec4 vPosition;    \n"
            "void main()                  \n"
            "{                            \n"
            "   gl_Position = vPosition;  \n"
            "}                            \n";
    }
    if (filename == PS_BASIC_SOURCE_FILE) {
        shaderBuffer =
            "precision mediump float;\n"
            "void main()                                  \n"
            "{                                            \n"
            "  gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );\n"
            "}                                            \n";
    }

    // Create a shader object.
    shader = glCreateShader(shaderType);

    // Copy the shader source code strings into the shader objects.
    const char *pStr = shaderBuffer.c_str();
    glShaderSource(shader, 1, &pStr, NULL);

    // Compile the shaders.
    glCompileShader(shader);

    // Check to see if the shader compiled successfully.
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != 1) {
        // If it did not compile then write the syntax error message out to a text file for review.
        OutputShaderErrorMessage(shader, filename);
        return false;
    }

    return true;
}

typedef vector<pair<GLenum, string>> ShaderSourceList;

static bool LoadShaderProgram(const ShaderSourceList &source, GLuint &shaderProgram) {
    int status;

    // Create a shader program object.
    shaderProgram = glCreateProgram();

    for (auto it = source.cbegin(); it != source.cend(); it++) {
        GLuint shader;
        status = LoadShaderFromFile(it->second.c_str(), it->first, shader);
        if (!status) {
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
        return false;
    }

    return true;
}

bool GraphicsManager::InitializeShaders() {
    GLuint shaderProgram;
    bool result = true;

    // Basic Shader
    ShaderSourceList listS = {
        {GL_VERTEX_SHADER, VS_BASIC_SOURCE_FILE},
        {GL_FRAGMENT_SHADER, PS_BASIC_SOURCE_FILE}};

    result = LoadShaderProgram(listS, shaderProgram);
    if (!result) {
        return result;
    }

    m_ShaderList[(int32_t)DefaultShaderIndex::BasicShader] = shaderProgram;

    return result;
}

int GraphicsManager::Initialize() {
    int result = 0;

    bool initShaderSucc = InitializeShaders();
    if (!initShaderSucc) result = -1;

    BeginScene();

    return result;
}

void GraphicsManager::Finalize() {
    EndScene();
}

void GraphicsManager::ResizeCanvas(int32_t width, int32_t height) {
    //Reset View
    glViewport(0, 0, (GLint)width, (GLint)height);
}

void GraphicsManager::Tick() {
    m_bFinishInit = true;

    RenderBuffers();
}

void GraphicsManager::RenderBuffers() {
    if (!m_bFinishInit) return;
    // Draw
}

void GraphicsManager::BeginScene() {
    // Prepare buffers
}

void GraphicsManager::EndScene() {
    // Clear buffers
}
