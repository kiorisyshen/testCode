package com.example.cpplibmanager

class CppLibManager {
    external fun stringFromJNI(): String

    companion object {
        init {
            System.loadLibrary("CppLibManager")
        }
    }
}