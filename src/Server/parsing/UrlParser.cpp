#include "UrlParser.h"

ppn::UrlParser::UrlParser() {


}

ppn::UrlParser::UrlParser(std::string _staticDirPath) :
    staticDirPath(_staticDirPath) {

    this->parserList = new url_map();
    
}