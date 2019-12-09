#include "public/web/include/CppLibManager.h"
#include <emscripten/bind.h>
#include <iostream>
#include "code/cppLib.hpp"

using namespace emscripten;
using namespace TestEngine;

bool WebInterface::CppLibManager::trigerLib(int number) {
    // printf("WebInterface::CppLibManager::trigerLib");
    std::cout << "WebInterface::CppLibManager::trigerLib" << std::endl;
    return runSomething(number);
}

// For rendering
void WebInterface::CppLibManager::initializeLib() {
    std::cout << "WebInterface::CppLibManager::initializeLib" << std::endl;
    _oglRenderer.initialize();
}

void WebInterface::CppLibManager::renderFrame() {
    std::cout << "WebInterface::CppLibManager::renderFrame" << std::endl;
    _oglRenderer.renderFrame();
}

EMSCRIPTEN_BINDINGS(sdk_web_assembly) {
    class_<WebInterface::CppLibManager>("CppLibManager")
        .constructor()
        .function("trigerLib", &WebInterface::CppLibManager::trigerLib)
        .function("initializeLib", &WebInterface::CppLibManager::initializeLib)
        .function("renderFrame", &WebInterface::CppLibManager::renderFrame);
}