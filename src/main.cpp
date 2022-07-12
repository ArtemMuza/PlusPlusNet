#include <iostream>
#include "utils/Utils.h"
#include "log_system/Log_system.h"


LogSystem logSysInstance;

int main() {
    LogSystem_settings settings;
    LogSystemInit(settings)
    ERROR << "You are gae"<<42<<std::endl;
    DEBUG << "You are smart gae"<<69<<std::endl;
    LOG <<"You are my favourite gae"<<1337<<std::endl;

    return 0;
}