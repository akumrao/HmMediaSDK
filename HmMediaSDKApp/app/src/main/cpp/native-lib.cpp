#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_harman_hmmediasdkapp_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}



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
 *   hello-jniCallback/app/src/main/java/com/example/hellojnicallback/MainActivity.java
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

   // Logger::instance().add(new ConsoleChannel("debug", Level::Trace ));


    LTrace("OnLoad");

    JNIEnv* env;
    memset(&g_ctx, 0, sizeof(g_ctx));

    g_ctx.javaVM = vm;
    if (vm->GetEnv( (void**)&env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR; // JNI version not supported.
    }

    //jclass  clz = env->FindClass("com/harman/vns/JniHandler");
   // g_ctx.jniHelperClz = (jclass)env->NewGlobalRef( clz);

   // jmethodID  jniHelperCtor = env->GetMethodID( g_ctx.jniHelperClz, "<init>", "()V");


//
//    jobject    handler = env->NewObject( g_ctx.jniHelperClz,
//                                         jniHelperCtor);
//    g_ctx.jniHelperObj = env->NewGlobalRef( handler);
//    queryRuntimeInfo(env, g_ctx.jniHelperObj);

    hm::init();

    g_ctx.done = 0;
    g_ctx.mainActivityObj = NULL;
    return  JNI_VERSION_1_6;
}

/*
 * A helper function to wrap java JniHelper::updateStatus(String msg)
 * JNI allow us to call this function via an instance even it is
 * private function.
 */
void   sendJavaMsg(JNIEnv *env, jobject instance,
                   jmethodID func,const char* msg) {

    jstring javaMsg = env->NewStringUTF( msg);
    env->CallVoidMethod( instance, func, javaMsg);
    env->DeleteLocalRef( javaMsg);
}

/*
 * Main working thread function. From a pthread,
 *     calling back to MainActivity::updateTimer() to display ticks on UI
 *     calling back to JniHelper::updateStatus(String msg) for msg
 */
/*
void*  UpdateTicks(void* context) {
    TickContext *pctx = (TickContext*) context;
    JavaVM *javaVM = pctx->javaVM;
    JNIEnv *env;
    jint res = javaVM->GetEnv((void**)&env, JNI_VERSION_1_6);
    if (res != JNI_OK) {
        res = javaVM->AttachCurrentThread( &env, NULL);
        if (JNI_OK != res) {
            LOGE("Failed to AttachCurrentThread, ErrorCode = %d", res);
            return NULL;
        }
    }

    jmethodID statusId = env->GetMethodID( pctx->jniHelperClz,
                                           "updateStatus",
                                           "(Ljava/lang/String;)V");
    sendJavaMsg(env, pctx->jniHelperObj, statusId,
                "TickerThread status: initializing...");

    // get mainActivity updateTimer function
    jmethodID timerId = env->GetMethodID( pctx->mainActivityClz,
                                          "updateTimer1", "(Ljava/lang/String;)V");
    //jmethodID timerId = (*env)->GetMethodID(env, pctx->mainActivityClz,
    //                                        "updateTimer1", "()V");

    struct timeval beginTime, curTime, usedTime, leftTime;
    const struct timeval kOneSecond = {
            (__kernel_time_t)1,
            (__kernel_suseconds_t) 0
    };

    sendJavaMsg(env, pctx->jniHelperObj, statusId,
                "TickerThread status: start ticking ...");
    while(1) {
        gettimeofday(&beginTime, NULL);
        pthread_mutex_lock(&pctx->lock);
        int done = pctx->done;
        if (pctx->done) {
            pctx->done = 0;
        }
        pthread_mutex_unlock(&pctx->lock);
        if (done) {
            break;
        }
        //(*env)->CallVoidMethod(env, pctx->mainActivityObj, timerId);

        sendJavaMsg(env, pctx->mainActivityObj, timerId,
                    "TickerThread status: initializing...");


        gettimeofday(&curTime, NULL);
        timersub(&curTime, &beginTime, &usedTime);
        timersub(&kOneSecond, &usedTime, &leftTime);
        struct timespec sleepTime;
        sleepTime.tv_sec = leftTime.tv_sec;
        sleepTime.tv_nsec = leftTime.tv_usec * 1000;

        if (sleepTime.tv_sec <= 1) {
            nanosleep(&sleepTime, NULL);
        } else {
            sendJavaMsg(env, pctx->jniHelperObj, statusId,
                        "TickerThread error: processing too long!");
        }
    }

    sendJavaMsg(env, pctx->jniHelperObj, statusId,
                "TickerThread status: ticking stopped");
    javaVM->DetachCurrentThread();
    return context;
}
*/
/*
 * Interface to Java side to start ticks, caller is from onResume()
 */



//Thread *thread = nullptr;


void   start(JNIEnv *env, jobject instance, jstring jdriverid , jstring jmetadata, jstring jpath ) {

    const char *c_driverid = env->GetStringUTFChars(jdriverid, NULL);
    std::string driverid = c_driverid;

    const char *c_metadata = env->GetStringUTFChars(jmetadata, NULL);
    std::string metadata = c_metadata;


    const char *c_path = env->GetStringUTFChars(jpath, NULL);
    std::string path = c_path;


    LTrace("StartTicks ", driverid )

    LTrace("StartTicks ", path )

    static int inc = 0;

    hm::upload(driverid, metadata, path);

//    if (!thread)
//    {
//        if( cmd == std::string("Upload" ))
//            thread = new Upload(url);
//        else {
//            //thread = new PingThread(url);
//            //if(++inc % 2 )
//            //  thread = new PingThread(url); //thread = new Signal(url);
//            //  else
//            //    thread = new Speed();  //  //thread = new Speed();
//        }
//    }
//    else
//        return ;



    jclass clz = env->GetObjectClass(instance);
    g_ctx.mainActivityClz = (jclass)env->NewGlobalRef( clz);
    g_ctx.mainActivityObj = env->NewGlobalRef(instance);

   // thread->start();
}


void  stop(JNIEnv *env, jobject instance) {
    LTrace("Stop Ticks");

//    if( thread) {
//        thread->stop();
//
//        // sleep(1);
//        delete thread;
//        thread = nullptr;
//
//        LTrace("pingThread delete over");
//
//        // release object we allocated from StartTicks() function
//        env->DeleteGlobalRef(g_ctx.mainActivityClz);
//        env->DeleteGlobalRef(g_ctx.mainActivityObj);
//        g_ctx.mainActivityObj = NULL;
//        g_ctx.mainActivityClz = NULL;
//
//        LTrace("Stop Ticks over");
//    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_harman_hmmediasdkapp_MainActivity_startTicks(JNIEnv *env, jobject instance ,jstring driverid , jstring metadata, jstring path ) {
    start(env,instance, driverid, metadata, path );
}


extern "C" JNIEXPORT void JNICALL
Java_com_harman_hmmediasdkapp_MainActivity_next(JNIEnv *env, jobject instance ,jstring jcmd , jstring jurl ) {
//    start(env,instance, jcmd,jurl );
}


/*
 * Interface to Java side to stop ticks:
 *    we need to hold and make sure our native thread has finished before return
 *    for a clean shutdown. The caller is from onPause
 */
extern "C" JNIEXPORT void JNICALL
Java_com_harman_hmmediasdkapp_MainActivity_StopTicks(JNIEnv *env, jobject instance) {

    stop(env,instance);
}