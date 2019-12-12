package com.example.cpplibmanager
import android.opengl.GLSurfaceView
import android.content.Context
import android.util.Log
import java.io.BufferedReader
import java.io.InputStream

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

        // Init default shaders
        openglRenderer.vertContent = context.assets.open("testShader.vert.glsl").bufferedReader().use(BufferedReader::readText)
        openglRenderer.fragContent = context.assets.open("testShader.frag.glsl").bufferedReader().use(BufferedReader::readText)

        return openglView
    }

    external fun stringFromJNI(): String

    companion object {
        init {
            System.loadLibrary("CppLibManager")
        }
    }
}
