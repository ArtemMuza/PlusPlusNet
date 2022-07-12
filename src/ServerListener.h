#pragma once

#include <stdexcept>
#include <string.h>
#include <functional>

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include "ServerExcept.h"

class ServerListener {

    int     port;
    bool    isRun;
    size_t  bufferSize;
    int     listen_socket;

    static void clientHandler(int client_socket, size_t buffer_size);
public:

    ServerListener(int port = 80, size_t buffer_size = 255);
    virtual ~ServerListener();

    void run(std::function<void(ClientAcceptationExcept)> client_acceptation_error_callback = [](ClientAcceptationExcept) {});
    void stop();

};