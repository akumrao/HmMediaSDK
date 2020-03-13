

#include "HmSdkUpload.h"

using namespace base;


int main(int argc, char** argv) {
    Logger::instance().add(new ConsoleChannel("debug", Level::Trace));

    hm::init();

    std::string file = "./test.mp4"; //complete path
    std::string metadata = "{filename:driver-1234-1232323.mp4, gps-latitude:28.674109, gps-longitude:77.438009, timestamp:20200309194530, uploadmode:normal}";

    hm::upload("driver-1234", metadata, file);



    sleep(444444444);

    hm::exit();

    return 0;
}


