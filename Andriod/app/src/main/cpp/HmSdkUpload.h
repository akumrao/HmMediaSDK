//
// Created by root on 28/12/19.
//

#ifndef MEDIAAPP_UPLOAD_H
#define MEDIAAPP_UPLOAD_H


#include <string>
#include <list>
#include "Common.h"
#include "base/logger.h"
#include "base/thread.h"

using namespace base;


namespace hm {

    //void init( );

    void upload(  const std::string driverId, const std::string metaDataJson, std::list < std::string > fileList  );

    void cbUploadProgess(const std::string& file, const int& prog);

    void cbFailure(const std::string& file, const std::string &reason, const int &code );

    void cbSuccess(const std::string& file, const std::string &reason);
    void  stop( );

   // void  exit( );




}// end hm



#endif //MEDIAAPP_UPLOAD_H
