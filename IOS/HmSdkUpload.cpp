//
// Created by root on 28/12/19.
//

#include "HmSdkUpload.h"
#include "../awsupload/hmTcpClient.h"
#include "base/logger.h"
#include "base/thread.h"
#include <functional>
#include <thread>

using namespace base;

/*****************************************************************************************/

namespace hm {


    const std::string ip = "18.228.58.178";
    //const std::string ip = "127.0.0.1";
    //const std::string ip = "192.168.0.6";

    const int port = 47001;


    hmTcpClient *thread = nullptr ;


    
    void UploadedPercentage(const std::string& file, const int& prog)
    {
        SInfo << "Percentage uploaded " << prog;
    }


    void cbFailure(const std::string& file, const std::string &reason, const int &code )
    {
        SInfo << "Uploade failure. "  <<  reason;

    }

    void cbSuccess(const std::string& file, const std::string &reason)
    {
        SInfo << "Uploade Suceess. "  << reason;
    }


    void upload(  const std::string driverId, const std::string metaDataJson, const std::string file)
    {
        using namespace std::placeholders;


        Logger::instance().add(new ConsoleChannel("debug", Level::Trace));

        if(!thread)
        {

            SInfo << "driverId " << driverId  <<  " metaDataJson " << metaDataJson  <<  " file "  << file;

            thread = new hmTcpClient(ip, port);
            
            thread->upload( file, driverId, metaDataJson);
            thread->start();

      
            thread->fnUpdateProgess = std::bind(&UploadedPercentage, _1, _2);
            
            thread->fnSuccess = std::bind(&cbSuccess, _1, _2);
            thread->fnFailure = std::bind(&cbFailure, _1, _2, _3);

        }

    }
     
    void exitit()
    {
	if(thread)
	{
          SInfo << "hm::exit() ";
          thread->shutdown();
          thread->join();
          delete thread;
          thread = nullptr;
        }
    }

    void  stop( )
    {
        if(thread)
        {
           std::thread th(&exitit) ;
           th.detach();     
        }
    }



   

}// end hm


