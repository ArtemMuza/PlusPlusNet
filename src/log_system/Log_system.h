#pragma once

#include <string>
#include <fstream>
#include <iostream>

class LogSystem;
extern LogSystem logSysInstance;

#define LogSystemInit( settings ) logSysInstance.Init( settings );
#define LogSystemShutdown() logSysInstance.Shutdown();

#define ERROR (logSysInstance << "ERROR " << logSysInstance.prefix(__FILE__, __LINE__))
#define DEBUG (logSysInstance << "DEBUG " << logSysInstance.prefix(__FILE__, __LINE__))
#define LOG (logSysInstance << "LOG " << logSysInstance.prefix(__FILE__, __LINE__))
#define FATAL (logSysInstance << "FATAL " << logSysInstance.prefix(__FILE__, __LINE__))


class LogSystem_settings {
public:
    std::string     workingDir = "";
    std::string     logfileName = "server.log";
    bool            isOverwrite = true;

    bool            consoleUsed = true;
    bool            fileUsed = true;

    bool            dataUsed = true;
    bool            lineUsed = true;

    LogSystem_settings() {}
};

class LogSystem{

    bool                isInit;
    std::ofstream*      logFile;
    LogSystem_settings  settings;

public:
    LogSystem();
    ~LogSystem();

    bool Init(const LogSystem_settings& settings);
    void Shutdown();

    template< typename T> LogSystem& operator<<(T t);
    LogSystem& operator<<(std::ostream& (*ost)(std::ostream&));


    std::string prefix(const std::string& file, const int line);
};

template< typename T> inline LogSystem& LogSystem::operator<<(T t) {
   if(isInit){
        if(this->settings.consoleUsed)
            std::cerr << t;
        if(this->settings.fileUsed)
            (*this->logFile) << t;

   }
    return *this;
}

inline LogSystem& LogSystem::operator<<(std::ostream& (*ost)(std::ostream&)) {
    if(isInit){
    if(this->settings.consoleUsed)
        std::cerr << std::endl;
    if(this->settings.fileUsed)
        (*this->logFile) << std::endl;
    }
    return *this;
}