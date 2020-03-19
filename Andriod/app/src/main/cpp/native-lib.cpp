#include <jni.h>
#include <string>

#include "HmSdkUpload.h"

TickContext g_ctx;

#include <android/log.h>


/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located astatic
 * /
  const char* kTAG = "hello-jniCallback";
#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, kTAG, __VA_ARGS__))
/*#define LOGW(...) \
  ((void)__android_log_print(ANDROID_LOG_WARN, kTAG, __VA_ARGS__))
#define LOGE(...) \
  ((void)__android_log_print(ANDROID_LOG_ERROR, kTAG, __VA_ARGS__))t:
 *
 *   hello-jniCallback/app/src/main/java/com/example/hellojnicallback/HmLibrary.java
 */


/*
 *  A helper function to show how to call
 *     java static functions JniHelper::getBuildVersion()
 *     java non-static function JniHelper::getRuntimeMemorySize()
 *  The trivial implementation for these functions are inside file
 *     JniHelper.java
 */
void queryRuntimeInfo(JNIEnv *env, jobject instance) {

}

/*
 * processing one time initialization:
 *     Cache the javaVM into our context
 *     Find class ID for JniHelper
 *     Create an instance of JniHelper
 *     Make global reference since we are using them from a native thread
 * Note:
 *     All resources allocated here are never released by application
 *     we rely on system to free all global refs when it goes away;
 *     the pairing function JNI_OnUnload() never gets called at all.
 */
extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {

    Logger::instance().add(new RemoteChannel("debug", Level::Remote, "10.99.109.11"));


    LTrace("jint");

    JNIEnv* env;
    memset(&g_ctx, 0, sizeof(g_ctx));

    g_ctx.javaVM = vm;
    if (vm->GetEnv( (void**)&env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR; // JNI version not supported.
    }


    g_ctx.done = 0;
    g_ctx.mainActivityObj = NULL;
    return  JNI_VERSION_1_6;
}

/*
 * A helper function to wrap java JniHelper::updateStatus(String msg)
 * JNI allow us to call this function via an instance even it is
 * private function.
 */
void   callbackJavaMsg(JNIEnv *env, jobject instance,
                   jmethodID func,const char* msg) {

    jstring javaMsg = env->NewStringUTF( msg);
    env->CallVoidMethod( instance, func, javaMsg);
    env->DeleteLocalRef( javaMsg);
}


//Thread *thread = nullptr;


void   upload(JNIEnv *env, jobject instance, jstring jdriverid , jstring jmetadata, jobjectArray stringArray ) {

    const char *c_driverid = env->GetStringUTFChars(jdriverid, NULL);
    std::string driverid = c_driverid;

    const char *c_metadata = env->GetStringUTFChars(jmetadata, NULL);
    std::string metadata = c_metadata;

    ////////////////////////////////////////////////////////////////////////

    std::list<std::string > lstFiles;
    size_t stringCount = (size_t)env->GetArrayLength( stringArray);

    int i = 0;
    for(i = 0; i < (int)stringCount; ++i )
    {
        jstring jniString = (jstring) env->GetObjectArrayElement( stringArray, i);
        const char *c_path = env->GetStringUTFChars(jniString, NULL);
        std::string path = c_path;
         LTrace("upload ", path )

         lstFiles.push_back(path);

         env->ReleaseStringUTFChars( jniString, c_path);
    }



    jclass clz = env->GetObjectClass(instance);
    g_ctx.mainActivityClz = (jclass)env->NewGlobalRef( clz);
    g_ctx.mainActivityObj = env->NewGlobalRef(instance);


    hm::upload(driverid, metadata,  lstFiles  );

   // thread->start();
}


void  stop(JNIEnv *env, jobject instance) {
    LTrace("Stop Upload");
    hm::stop();
}


/*
 * Interface to Java side to start uplaod:
 *
 */

extern "C" JNIEXPORT void JNICALL
Java_com_harman_hmmediasdkapp_HmLibrary_upload(JNIEnv *env, jobject instance ,jstring driverid , jstring metadata, jobjectArray stringArray ) {

    LTrace("HmLibrary_upload");

    upload( env, instance, driverid, metadata, stringArray);

}


/*
 * Interface to Java side to stop uplaod:
 *
 */
extern "C" JNIEXPORT void JNICALL
Java_com_harman_hmmediasdkapp_HmLibrary_stop(JNIEnv *env, jobject instance) {
    stop(env,instance);
}
