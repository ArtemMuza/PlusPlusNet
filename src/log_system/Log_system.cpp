 #include "Log_system.h"
 #include "../utils/Utils.h"

LogSystem::LogSystem() {
    isInit = false;
}

LogSystem::~LogSystem() {
    if( isInit ) {
        this->Shutdown();
    }
}

bool LogSystem::Init(const LogSystem_settings& settings) {
    //TODO: add correctly path verify
    this->settings = settings;
    this->logFile = new std::ofstream();

    if( !isInit ) {
        if( settings.isOverwrite ) {
            this->logFile->open( this->settings.workingDir + this->settings.logfileName);  
        }
        else{
           this->logFile->open( this->settings.workingDir + getCurrentDateFile() + this->settings.logfileName);
        }

        if(this->logFile->is_open()){
            this->isInit=true;
            return true;
        }
        else{
            return false;
        }
    }
    return true;
}

void LogSystem::Shutdown(){
    if( !isInit ){
        this->logFile->close();
        delete logFile;
        this->isInit=false;
    }
}

std::string LogSystem::prefix(const std::string& file, const int line){
    std::string buff = "";
    if (this->settings.dataUsed){
        buff=buff+getCurrentTimeDate();
        
        if(!this->settings.lineUsed){
            buff=buff+':';
        }
        else{
            buff=buff+',';
        }
    }
    if(this->settings.lineUsed){
        buff=buff+file+'('+std::to_string(line)+"):";
    }

    return buff;
}

