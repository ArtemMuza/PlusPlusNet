#include "Utils.h"
#include <ctime>
#include <iostream>
std::string getCurrentTime(){
    time_t rawtime;
    struct tm* timeinfo;
 
    time(&rawtime);
    timeinfo=localtime(&rawtime);
    
    int hour = timeinfo->tm_hour;
    int min = timeinfo->tm_min;
    int sec = timeinfo->tm_sec;

    std::string buff = "";
    buff=buff+std::to_string(hour)+':'+std::to_string(min)+':'+std::to_string(sec);
    return buff;
    
}
std::string getCurrentDate(){
    time_t rawtime;
    struct tm* timeinfo;
 
    time(&rawtime);
    timeinfo=localtime(&rawtime);

    int day = timeinfo->tm_mday;
    int mon = timeinfo->tm_mon + 1;
    int year = timeinfo->tm_year + 1900;

    std::string buff = "";
    buff=buff+std::to_string(day)+'.'+std::to_string(mon)+'.'+std::to_string(year);
    return buff;
    
}
std::string getCurrentTimeDate(){
    time_t rawtime;
    struct tm* timeinfo;
 
    time(&rawtime);
    timeinfo=localtime(&rawtime);
    std::string buff(asctime(timeinfo));
    buff[buff.length()-1]=' ';

    return buff;
   
}
std::string getCurrentDateFile(){
    time_t rawtime;
    struct tm* timeinfo;
 
    time(&rawtime);
    timeinfo=localtime(&rawtime);
    std::string buff(asctime(timeinfo));

    for(int i=0; i<buff.length(); i++){
        if(buff[i]==' '){
        buff[i]='_';
        }
    }
    return buff;
}