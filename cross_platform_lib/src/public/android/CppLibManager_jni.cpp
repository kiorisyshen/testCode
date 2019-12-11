//
// Created by sijie.shen on 2019-12-11.
//

#include "CppLibManager_jni.h"
#include <jni.h>
#include <string>
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
