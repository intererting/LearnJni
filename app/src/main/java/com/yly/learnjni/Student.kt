package com.yly.learnjni

import android.util.Log

/**
 * @author    yiliyang
 * @date      2022/8/8 下午5:41
 * @version   1.0
 * @since     1.0
 */
class Student {
    private var name: String = "default"

    external fun errorHandle()

    fun printName() {
        Log.i("LearnJni", name)
    }
}