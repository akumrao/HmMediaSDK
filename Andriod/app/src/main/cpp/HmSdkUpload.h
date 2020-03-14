//
// Created by root on 28/12/19.
//

#ifndef MEDIAAPP_UPLOAD_H
#define MEDIAAPP_UPLOAD_H


#include <string>
#include "Common.h"
#include "base/logger.h"
#include "base/thread.h"

using namespace base;


namespace hm {

    void init( );

    void upload(  const std::string driverId, const std::string metaDataJson, const std::string file);

    void  stop( );

    void  exit( );




}// end hm



#endif //MEDIAAPP_UPLOAD_H