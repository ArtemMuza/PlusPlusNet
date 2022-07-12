#include "ServerListener.h"

#include <iostream>
#include <cstdlib>
#include <list>
#include <future>
#include <chrono>
#include <thread>
#include <sstream>

#include "RequestParser.h"

ServerListener::ServerListener(int port, size_t buffer_size) {

    this->port = port;
    this->bufferSize = buffer_size;
    this->isRun = false;
    this->listen_socket = NULL;
    
}