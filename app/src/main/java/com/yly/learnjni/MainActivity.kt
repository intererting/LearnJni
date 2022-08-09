package com.yly.learnjni

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.TextView
import com.yly.learnjni.databinding.ActivityMainBinding
import java.util.*

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI()

//        localRef()

//        createGlobalRef()
//        Log.i("LearnJni", getGlobalRef())
//        deleteGlobalRef()

        val student = Student()
        student.errorHandle()
        println(student.printName())
    }

    /**
     * A native method that is implemented by the 'learnjni' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'learnjni' library on application startup.
        init {
            System.loadLibrary("learnjni")
        }
    }
}