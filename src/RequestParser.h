#pragma once

#include <string>
#include <map>


class RequestParser {
bool half_end_of_line;
    bool end_of_line;
    bool first_line;
    bool beginning;

    std::string method;
    std::string path;
    std::string proto_ver;

    std::string tmp_header_name;
    std::string tmp_header_value;

    char previous_char;

    std::map<std::string, std::string> headers;
    bool headers_available;

public:

    RequestParser();

    void processChunk(const char *buf, size_t size);

    bool allHeadersAvailable();

    std::map<std::string, std::string> getHeaders();

    std::string getMethod();

    std::string getPath();

    std::string getProtocol();

    void reset();

    virtual ~RequestParser() = default;
};