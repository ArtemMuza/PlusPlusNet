#pragma once 

#include <string>
#include <stdexcept>
#include "../../../src/log_system/Log_system.h"

class ServerExcept  {

public:

    ServerExcept(std::string info) {
       ERROR<<info<<'\n';
    }
    virtual ~ServerExcept() {}
};

class ServerStartUpExcept : public ServerExcept {

public:
    ServerStartUpExcept() :
        ServerExcept("Socket Init failed") {}
    virtual ~ServerStartUpExcept() {}
};


class AddrInfoExcept : public ServerExcept {

public:
    AddrInfoExcept(int err_no) :
        ServerExcept ( 
            std::string("addrinfo() failed with error: ") +
            std::to_string(err_no)) {}
    virtual ~AddrInfoExcept() {}
};

class SocketCreationExcept : public ServerExcept {
public:
    SocketCreationExcept(int error_no)
        : ServerExcept(
              std::string("socket() failed with error: ") +
              std::to_string(error_no)
        ) {}
    virtual ~SocketCreationExcept() {}
};


class SocketBindingExcept : public ServerExcept {
public:
    SocketBindingExcept(int error_no)
        : ServerExcept(
              std::string("bind() is failed with error: ") +
              std::to_string(error_no)
        ) {}
    virtual ~SocketBindingExcept() {}
};


class ListenExcept : public ServerExcept {
public:
    ListenExcept(int error_no)
        : ServerExcept(
              std::string("listen() failed with error: ") +
              std::to_string(error_no)
        ) {}
    virtual ~ListenExcept() {}
};


class ClientAcceptationExcept : public ServerExcept {
public:
    ClientAcceptationExcept(int error_no)
        : ServerExcept(
              std::string("accept() failed with error: ") +
              std::to_string(error_no)
        ) {}
    virtual ~ClientAcceptationExcept() {}
};
