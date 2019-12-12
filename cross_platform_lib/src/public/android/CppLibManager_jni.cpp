//
// Created by sijie.shen on 2019-12-11.
//

#include "CppLibManager_jni.h"
#include <jni.h>
#include <string>
#include "code/RHI/OpenGLES/OpenGLESRenderer.hpp"
#include "code/cppLib.hpp"


extern "C" JNIEXPORT jstring JNICALL
Java_com_example_cpplibmanager_CppLibManager_stringFromJNI(
    JNIEnv *env,
    jobject /* this */) {
    std::string hello = "Hello from C++";
    if (runSomething(5)) {
        hello += " Lib";
    }

    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_cpplibmanager_GLRenderer_initializeGL(
    JNIEnv *env,
    jobject /* this */) {

    OpenGLESRenderer::initialize();

    return 0;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_cpplibmanager_GLRenderer_renderFrame(
        JNIEnv *env,
        jobject /* this */) {

    OpenGLESRenderer::renderFrame();

    return 0;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_cpplibmanager_GLRenderer_resizeView(
        JNIEnv *env,
        jobject /* this */,
        jint width, jint height) {

    OpenGLESRenderer::resizeView(width, height);

    return 0;
}