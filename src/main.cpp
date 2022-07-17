#include <iostream>
#include <csignal>
#include "log_system/Log_system.h"
#include "Server/Server.h"

LogSystem logSysInstance;

void sigTerm(int _signum) {
    LogSystem_settings settings;
    settings.dataUsed = false;
    settings.fileUsed = false;
    LogSystemInit(settings)
    ppn::Server*    server = &ppn::Server::getInstance();
    LOG << "System terminated start\t" << server->IsRun() <<std::endl;
    server->Stop();
    server->Shutdown();
    LOG << "System terminated success" << std::endl;
    exit( _signum);
}

int main(int argc, char** argv) {
    LogSystem_settings settings;
    LogSystemInit(settings)

    signal(SIGINT, sigTerm);

    ppn::ServerSettings sst(argc, argv);
    ppn::Server*    server = &ppn::Server::getInstance();
    server->temp = 90;
    server->Init(sst);
    server->Start();
    
    
    
    return 0;
}