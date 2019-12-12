package com.example.androidtestmain


import android.opengl.GLSurfaceView
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import kotlinx.android.synthetic.main.activity_main.*
import com.example.cpplibmanager.*

class MainActivity : AppCompatActivity() {
    private lateinit var openglView: GLSurfaceView
    private var openglViewInitialized: Boolean = false

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val testWrapper = CppLibManager()
//        sample_text.text = testWrapper.stringFromJNI()
        println(testWrapper.stringFromJNI())
        Log.d("test", testWrapper.stringFromJNI())

        openglView = testWrapper.initializeGLView(this)
        setContentView(openglView)

        openglViewInitialized = true
    }

    override fun onPause() {
        super.onPause()

        if (openglViewInitialized) {
            openglView.onPause()
        }
    }

    override fun onResume() {
        super.onResume()

        if (openglViewInitialized) {
            openglView.onResume()
        }
    }
}
