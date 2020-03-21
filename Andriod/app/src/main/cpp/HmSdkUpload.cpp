//
// Created by root on 28/12/19.
//

#include "HmSdkUpload.h"
#include "base/filesystem.h"
#include "base/platform.h"
#include "../awsupload/hmTcpClient.h"

extern TickContext g_ctx;

void callbackJavaUploadProgess(JNIEnv *env, jobject instance,  jmethodID func,const char* file, int );

void callbackJavaFailure(JNIEnv *env, jobject instance,  jmethodID func,const char* file, const char *msg, int );

void callbackJavaSuccess(JNIEnv *env, jobject instance,  jmethodID func,const char* file, const char *msg );

/*****************************************************************************************/

namespace hm {


    const std::string ip = "18.228.58.178";
   // const std::string ip = "192.168.0.2";

    const int port = 47001;

    std::list<hmTcpClient*> listThread ;


    void cbFailure(const std::string& file, const std::string &reason, const int &code )
    {
        TickContext *pctx = (TickContext*) &g_ctx;
        JavaVM *javaVM = pctx->javaVM;
        JNIEnv *env;
        jint res = javaVM->GetEnv((void**)&env, JNI_VERSION_1_6);
        if (res != JNI_OK) {
            res = javaVM->AttachCurrentThread( &env, NULL);
            if (JNI_OK != res) {
                LOGE("Failed to AttachCurrentThread, ErrorCode = %d", res);
                return ;
            }
        }

        std::string percent = file + ", Failure : " +  reason ;

        jmethodID timerId = env->GetMethodID( pctx->mainActivityClz,
                                              "uploadFailure", "(Ljava/lang/String;Ljava/lang/String;I)V");

        if (timerId)
            callbackJavaFailure(env, pctx->mainActivityObj, timerId, file.c_str(),  reason.c_str(), code );


    }

    void cbSuccess(const std::string& file, const std::string &reason)
    {
        TickContext *pctx = (TickContext*) &g_ctx;
        JavaVM *javaVM = pctx->javaVM;
        JNIEnv *env;
        jint res = javaVM->GetEnv((void**)&env, JNI_VERSION_1_6);
        if (res != JNI_OK) {
            res = javaVM->AttachCurrentThread( &env, NULL);
            if (JNI_OK != res) {
                LOGE("Failed to AttachCurrentThread, ErrorCode = %d", res);
                return ;
            }
        }

        std::string percent = file + ", Success : " +  reason ;

        jmethodID timerId = env->GetMethodID( pctx->mainActivityClz,
                                              "uploadSuccess", "(Ljava/lang/String;Ljava/lang/String;)V");

        if (timerId)
            callbackJavaSuccess(env, pctx->mainActivityObj, timerId, file.c_str(),  reason.c_str() );


    }


    void cbUploadProgess(const std::string& file, const int& prog)
    {
        SInfo << "Percentage uploaded " <<prog;


        TickContext *pctx = (TickContext*) &g_ctx;
        JavaVM *javaVM = pctx->javaVM;
        JNIEnv *env;
        jint res = javaVM->GetEnv((void**)&env, JNI_VERSION_1_6);
        if (res != JNI_OK) {
            res = javaVM->AttachCurrentThread( &env, NULL);
            if (JNI_OK != res) {
                LOGE("Failed to AttachCurrentThread, ErrorCode = %d", res);
                return ;
            }
        }

        std::string percent = file + " :" +  std::to_string(prog );

        jmethodID timerId = env->GetMethodID( pctx->mainActivityClz,
                                              "uploadProgress", "(Ljava/lang/String;I)V" );

        if (timerId)
            callbackJavaUploadProgess(env, pctx->mainActivityObj, timerId, file.c_str(), prog  );


    }


    void upload(  const std::string driverId, const std::string metaDataJson, std::list < std::string > fileList  )
    {
        using namespace std::placeholders;

        if(!listThread.size())
            for (std::list<std::string>::iterator it=fileList.begin(); it != fileList.end(); ++it) {

                SInfo << "File uploading " << *it;

                hmTcpClient *thread = new hmTcpClient(ip, port);

                thread->upload(*it, driverId, metaDataJson);
                thread->start();

                listThread.push_back(thread);
                thread->fnUpdateProgess = std::bind(&cbUploadProgess, _1, _2);
                thread->fnSuccess = std::bind(&cbSuccess, _1, _2);
                thread->fnFailure = std::bind(&cbFailure, _1, _2, _3);
            }


    }

    void  stop( )
    {

        for (std::list<hmTcpClient*>::iterator it=listThread.begin(); it != listThread.end(); ++it) {

            hmTcpClient *hm =   *it;
            hm->shutdown();
            delete hm;
        }
        listThread.clear();

    }





}// end hm

