#include "ServerListener.h"

#include <iostream>
#include <cstdlib>
#include <list>
#include <future>
#include <chrono>
#include <thread>
#include <sstream>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../parsing/RequestParser.h"

ServerListener::ServerListener(int port, size_t buffer_size) {

    this->port = port;
    this->bufferSize = buffer_size;
    this->isRun = false;
    this->listen_socket = NULL;
    
}

void ServerListener::run(std::function <void (ClientAcceptationExcept)> client_acceptation_error_callback) {

    struct sockaddr_in serv_addr;

    listen_socket = socket (
        AF_INET,
        SOCK_STREAM,
        0
    );
    
    if( listen_socket < 0)
        throw SocketCreationExcept(errno);
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(this->port);

    if (bind(this->listen_socket, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
        throw SocketBindingExcept(errno);
    
    if (listen(this->listen_socket, 128) < 0)
        throw ListenExcept(errno);

    std::map<int, std::thread> threads;

    bool server_running = true;
    while(server_running) {
        int client_socket;

        try {
            client_socket = accept(listen_socket, NULL, NULL);
            if(client_socket == -1) {
                throw ClientAcceptationExcept(errno);
            }
        } catch(ClientAcceptationExcept &e) {
            client_acceptation_error_callback(e);
            continue;
        }
        threads[client_socket] = std::thread(ServerListener::clientHandler, client_socket, this->bufferSize);
    }
}

void ServerListener::stop() {
    this->isRun = false;
    if( this->listen_socket != NULL ) { 
        close(this->listen_socket);
    }
}

void ServerListener::clientHandler(int client_socket, size_t buffer_size) {
    int recvbuflen = buffer_size;
    char recvbuf[recvbuflen];
    int bytes_received;
    RequestParser parser;

    struct sockaddr_in client_info;
    socklen_t client_info_len = sizeof(client_info);
    char *client_ip;

    if(getpeername(client_socket, (sockaddr*)(&client_info), &client_info_len) == -1) {
        goto cleanup;
    }
    client_ip = inet_ntoa(client_info.sin_addr);

    while(1) {
        parser.reset();

        bool headers_ready = false;
        while(!headers_ready) {
            bytes_received = recv(client_socket, recvbuf, recvbuflen, 0);
            if(bytes_received > 0) {
                parser.processChunk(recvbuf, bytes_received);
                if(parser.allHeadersAvailable()) {
                    headers_ready = true;
                }
            } else {
                goto cleanup;
            }
        }

        auto headers = parser.getHeaders();

        auto conn_it = headers.find("Connection");
        if(conn_it != headers.end() && conn_it->second == "close") {
            goto cleanup;
        }

        std::cout << parser.getMethod() << " "
                  << parser.getPath() << " "
                  << parser.getProtocol() << "\n";

        std::cout << "> " << client_ip << "\n";

        auto ua_it = headers.find("User-Agent");
        if(ua_it != headers.end()) {
            std::cout << "> " << ua_it->second << "\n";
        } else {
            std::cout << "> no UAString provided" << "\n";
        }

        std::cout << "\n";

        std::string response_body = "<!DOCTYPE html><html><head>"
            "<title>Request info</title>"
            "<style>"
                "table, th, td { border: 1px solid #333; }"
                "th, td { padding: 3px 5px; }"
                "th { text-align: right; }"
                "td { text-align: left; }"
            "</style>"
        "</head>"
        "<body><h1>Request info</h1>";

        response_body += "<table>";

        response_body += "<tr><th>Method</th><td>" + parser.getMethod() + "</td></tr>";
        response_body += "<tr><th>Path</th><td>" + parser.getPath() + "</td></tr>";
        response_body += "<tr><th>Protocol</th><td>" + parser.getProtocol() + "</td></tr>";

        for(const auto &header : headers) {
            response_body += "<tr><th>" + header.first + "</th><td>" + header.second + "</td></tr>";
        }

        std::stringstream ss;
        ss << std::this_thread::get_id();
        response_body += "<tr><th>Thread ID</th><td>" + ss.str() + "</td></tr>";

        response_body += "</table>";
        response_body += "</body></html>\r\n";


        std::string response_headers = "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Connection: keep-alive\r\n"
        "Content-Length: " + std::to_string(response_body.length()) + "\r\n\r\n";

        std::string response = response_headers + response_body;
        send(client_socket, response.c_str(), strlen(response.c_str()), 0);
    }

cleanup:
    close(client_socket);
}

ServerListener::~ServerListener() {

    
}