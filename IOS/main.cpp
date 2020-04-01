

#include "HmSdkUpload.h"
#include <unistd.h>
#include <iostream>

int main(int argc, char** argv) {

    hm::stop();


    std::string file = "./test.mp4"; //complete path
    
    std::string  metadata ="{\"filename\":\"1.mp4\",\"gps-latitude\":\"28.674109\",\"gps-longitude\":\"77.438009\",\"timestamp\":\"20200309194530\",\"uploadmode\":\"normal\"}";

    hm::upload("driver-1234", metadata, file);

    usleep(9000000);
    std::cout << "first upload done" << std::endl;
    hm::stop();
    std::cout << "stop done" << std::endl;

    usleep(900000);

    std::cout << "second upload start" << std::endl;

    hm::upload("driver-1234", metadata, file);

    usleep(9000000);

    std::cout << "second upload done" << std::endl;

    hm::stop();


    return 0;
}


