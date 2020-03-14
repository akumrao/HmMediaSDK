//
// Created by root on 28/12/19.
//

#ifndef MEDIAAPP_UPLOAD_H
#define MEDIAAPP_UPLOAD_H

#include "base/logger.h"
#include "base/thread.h"

#include "Common.h"

using namespace base;


namespace hm {
    //const std::string ip = "52.14.171.173";

    void init( );

    void upload(  const std::string driverId, const std::string metaDataJson, const std::string file);

    void  stop( );

    void  exit( );


}// end hm


//using namespace base;
//using namespace net;
//
//class Upload : public Thread {
//public:
//
//    Upload(std::string url);
//
//    ~Upload();
//
//
//    void run();
//    void stop(bool flag = true);
//    URL _url;
//    ClientConnecton *client{nullptr};
//
//    Application app;
//    FormWriter *form;
//
//    uv_async_t async;
//    uv_async_t asyncUpdate;
//
//};

#endif //MEDIAAPP_UPLOAD_H
