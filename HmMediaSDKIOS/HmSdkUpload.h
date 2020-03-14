//
// Created by root on 28/12/19.
//

#ifndef MEDIAAPP_UPLOAD_H
#define MEDIAAPP_UPLOAD_H


#include <string>


namespace hm {
    //const std::string ip = "52.14.171.173";

    void init( );

    void upload(  const std::string driverId, const std::string metaDataJson, const std::string file);

    void  stop( );

    void  exit( );


}// end hm



#endif //MEDIAAPP_UPLOAD_H
