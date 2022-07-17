#pragma once

#include <string>
#include <unordered_map>

namespace ppn {

typedef std::string (*view) (void);
typedef std::unordered_map<std::string, view> url_map;


class UrlParser {

    url_map*     parserList;
    std::string                         staticDirPath;
public:

    UrlParser();
    UrlParser(std::string _staticDirPath);
    
    void ChangeStaticDirPath();

    void AddUrlPair();

};

};