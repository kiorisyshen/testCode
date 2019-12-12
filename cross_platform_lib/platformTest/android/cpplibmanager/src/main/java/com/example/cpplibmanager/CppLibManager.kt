package com.example.cpplibmanager
import android.opengl.GLSurfaceView
import android.content.Context

class CppLibManager {
    private lateinit var openglView: GLSurfaceView
    private lateinit var openglRenderer: GLRenderer

    fun initializeGLView(context: Context): GLSurfaceView {
        // Create a GLSurfaceView instance and set it
        // as the ContentView for this Activity.
        openglView = GLSurfaceView(context)
        openglView.setEGLContextClientVersion(2);

        openglRenderer = GLRenderer()
        openglView.setRenderer(openglRenderer)

        return openglView
    }

    external fun stringFromJNI(): String

    companion object {
        init {
            System.loadLibrary("CppLibManager")
        }
    }
}
