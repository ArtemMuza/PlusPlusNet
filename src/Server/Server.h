#pragma once

#include "connectivity/ServerListener.h"
#include "parsing/UrlParser.h"

namespace ppn {

class ServerSettings;

class Server {

    Server() {}
    Server( Server const&);
    void operator=(Server const&);


    UrlParser*          urlParser;
    ServerListener*     listener;

    bool                isRun = false;
public:

    static Server&  getInstance() {
        static Server   instance;
        return instance;
    }
    
    //workflow
    bool Init(ServerSettings const&);
    void Start();
    void Stop();
    void Shutdown();

    bool IsRun();

    int temp;

};

struct ServerSettings {


    std::string     staticDirPath = "static/";
    unsigned        port = 80;


    //Order of argv parameters:
    // 1st - port
    // 2nd - static dir
    ServerSettings(int argc, char** argv);
};

};