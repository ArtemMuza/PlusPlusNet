#include <iostream>
#include "log_system/Log_system.h"
#include "Server/connectivity/ServerListener.h"

LogSystem logSysInstance;

int main() {
    LogSystem_settings settings;
    LogSystemInit(settings)

    ServerListener sl;
    sl.run();

    return 0;
}