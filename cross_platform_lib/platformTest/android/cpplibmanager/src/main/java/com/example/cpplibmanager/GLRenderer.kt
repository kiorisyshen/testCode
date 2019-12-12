package com.example.cpplibmanager

import android.opengl.GLSurfaceView
import android.util.Log
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class GLRenderer : GLSurfaceView.Renderer{
    public lateinit var vertContent: String
    public lateinit var fragContent: String

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        initializeGL()

        if (initializeShaderProgramFromString(vertContent, fragContent) != 0) {
            Log.d("test Shader", "Failed!")
        } else {
            Log.d("test Shader", "Success!")
        }
    }

    override fun onDrawFrame(gl: GL10?) {
        renderFrame()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        resizeView(width, height)
    }

    external fun initializeGL() : Int

    external fun renderFrame() : Int

    external fun resizeView(width: Int, height: Int) : Int

    external fun initializeShaderProgramFromString(vertContent: String, fragContent: String) : Int

    companion object {
        init {
            System.loadLibrary("CppLibManager")
        }
    }
}