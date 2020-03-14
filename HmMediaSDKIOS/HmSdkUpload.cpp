//
// Created by root on 28/12/19.
//

#include "HmSdkUpload.h"
#include "../awsupload/hmTcpClient.h"
#include "base/logger.h"
#include "base/thread.h"

using namespace base;

/*****************************************************************************************/

namespace hm {


    //const std::string ip = "52.14.171.173";
    const std::string ip = "127.0.0.1";
    //const std::string ip = "10.99.234.1";

    const int port = 47001;


    hmTcpClient *thread = nullptr ;

    void init( )
    {

        Logger::instance().add(new ConsoleChannel("debug", Level::Trace));

        thread = new hmTcpClient(ip, port);
    }


    void upload(  const std::string driverId, const std::string metaDataJson, const std::string file)
    {
        thread->upload( file, driverId, metaDataJson);
        thread->start();

        thread->fnUpdateProgess = [&](const std::string str, int progess) {

            SInfo << "Percentage uploaded " <<progess;

        };

    }

    void  stop( )
    {

        thread->stop();

    }



    void  exit( )
    {
        delete thread;
    }

}// end hm


