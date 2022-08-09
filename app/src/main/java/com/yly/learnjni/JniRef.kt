package com.yly.learnjni

/**
 * @author    yiliyang
 * @date      2022/8/8 下午4:18
 * @version   1.0
 * @since     1.0
 */
external fun localRef()

external fun createGlobalRef()

external fun getGlobalRef(): String

external fun deleteGlobalRef()

external fun createWeakGlobalRef()

external fun deleteWeakGlobalRef()
