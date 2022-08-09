#include <jni.h>
#include <string>
#include <android/log.h>

#define TAG "LearnJni"
// __VA_ARGS__ 代表 ...的可变参数
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__);
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__);
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__);
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__);
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__);

jstring globalRef;
jclass dateClazz;

extern "C" JNIEXPORT jstring

JNICALL
Java_com_yly_learnjni_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
/**
 * 局部引用
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_yly_learnjni_JniRefKt_localRef(JNIEnv
*env,
jclass clazz
) {
jclass dateClazz = env->FindClass("java/util/Date");
jmethodID jmethodId = env->GetMethodID(dateClazz, "<init>", "()V");
jobject dateObj = env->NewObject(dateClazz, jmethodId);
jmethodID timeMethodId = env->GetMethodID(dateClazz, "getTime", "()J");
jlong time = env->CallLongMethod(dateObj, timeMethodId);
LOGI("当前时间%ld", time);
env->
DeleteLocalRef(dateObj);
}
/**
 * 创建全局引用
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_yly_learnjni_JniRefKt_createGlobalRef(JNIEnv
*env,
jclass clazz
) {
jstring globalStr = env->NewStringUTF("global ref");
globalRef = static_cast<jstring>(env->NewGlobalRef(globalStr));
}
/**
 * 获取全局引用
 */
extern "C"
JNIEXPORT jstring
JNICALL
        Java_com_yly_learnjni_JniRefKt_getGlobalRef(JNIEnv * env, jclass
clazz) {
return
globalRef;
}

/**
 * 删除全局引用
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_yly_learnjni_JniRefKt_deleteGlobalRef(JNIEnv
*env,
jclass clazz
) {
env->
DeleteGlobalRef(globalRef);
}

/**
 * 与全局引用类似，弱引用可以跨方法、线程使用。但与全局引用很重要不同的一点是，弱引用不会阻止 GC 回收它引用的对
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_yly_learnjni_JniRefKt_createWeakGlobalRef(JNIEnv
*env,
jclass clazz
) {
if (dateClazz == nullptr) {
dateClazz = static_cast<jclass>(env->NewWeakGlobalRef(env->FindClass("java/util/Date")));
LOGI("dateClazz init")
}
}
extern "C"
JNIEXPORT void JNICALL
Java_com_yly_learnjni_JniRefKt_deleteWeakGlobalRef(JNIEnv
*env,
jclass clazz
) {
env->
DeleteWeakGlobalRef(dateClazz);
}

/**
 * 错误处理
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_yly_learnjni_Student_errorHandle(JNIEnv
*env,
jobject thiz
) {
jclass studentClazz = env->FindClass("com/yly/learnjni/Student");
jfieldID nameFiled = env->GetFieldID(studentClazz, "name1", "Ljava/lang/String;");
jthrowable throwable = env->ExceptionOccurred();
if (throwable) {
LOGI("发生异常")
env->

ExceptionClear();

nameFiled = env->GetFieldID(studentClazz, "name", "Ljava/lang/String;");
}
env->
SetObjectField(thiz, nameFiled, env
->NewStringUTF("yuliyang"));
}