//
// Created by root on 28/12/19.
//

#ifndef HMSDK_UPLOAD_H
#define HMSDK_UPLOAD_H


#include <string>


namespace hm {



    void upload(  const std::string driverId, const std::string metaDataJson, const std::string file);

    void  stop( );

    void UploadedPercentage(const std::string& file, const int& prog);

    void cbFailure(const std::string& file, const std::string &reason, const int &code );
    
    void cbSuccess(const std::string& file, const std::string &reason);
    
 

}// end hm



#endif //MEDIAAPP_UPLOAD_H
