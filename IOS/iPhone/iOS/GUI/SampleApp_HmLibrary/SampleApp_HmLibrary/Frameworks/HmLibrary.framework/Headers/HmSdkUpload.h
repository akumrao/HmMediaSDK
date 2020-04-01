//
// Created by root on 28/12/19.
//

#ifndef HMSDK_UPLOAD_H
#define HMSDK_UPLOAD_H


#include <string>


namespace hm {


    void init( );

    void upload(  const std::string driverId, const std::string metaDataJson, const std::string file);

    void  stop( );

    void  exit( );

    void UploadedPercentage(const std::string& file, const int& prog);
 

}// end hm



#endif //MEDIAAPP_UPLOAD_H
