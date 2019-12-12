package com.example.cpplibmanager

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class GLRenderer : GLSurfaceView.Renderer{
    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        initializeGL()
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

    companion object {
        init {
            System.loadLibrary("CppLibManager")
        }
    }
}