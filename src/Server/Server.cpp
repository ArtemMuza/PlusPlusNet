#include "Server.h"
#include "../log_system/Log_system.h"

//#define SERVER_DEBUG
ppn::ServerSettings::ServerSettings(int argc, char** argv) {


    if(argc < 2)
        return;

    this->port =  atoi( argv[1]);
    if(argc < 3)
        return;
    this->staticDirPath = argv[2];
}



bool ppn::Server::Init(ServerSettings const& _setting) {

    this->listener = new ServerListener(_setting.port);
    this->urlParser = new UrlParser(_setting.staticDirPath);

    return true;
}

void ppn::Server::Start() {

#ifdef  SERVER_DEBUG
    LOG << "Server starting..." << std::endl;
#endif    
    if(!this->isRun) {
        this->isRun = true;
        this->listener->run();
        return;
    }
    
#ifdef  SERVER_DEBUG
    LOG << "\t Server already start" << std::endl;
#endif
}

void ppn::Server::Stop() {

#ifdef  SERVER_DEBUG
    LOG << "Server stopping..." << std::endl;
#endif
    if(this->isRun) {
        this->listener->stop();
        this->isRun = false;
        return;
    }
#ifdef  SERVER_DEBUG
    LOG << "\tServer already stopped" << std::endl;
#endif
}

void ppn::Server::Shutdown() {

    delete this->listener;
    delete this->urlParser;
#ifdef  SERVER_DEBUG
    LOG << "Server shutdowned, must re initialization" << std::endl;
#endif
}

bool ppn::Server::IsRun() {

    return this->isRun;
}