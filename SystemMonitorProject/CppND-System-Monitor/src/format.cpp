#include <string>

#include "format.h"

using std::string;

//Helper funtion to return the time
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) { 
    //Convert to hours
    int hours = seconds/3600;
    //Convert to minutes
    int minutes = (seconds/60) % 60;
    //Convert to seconds
    int sec = (seconds % 60);
    //Convert to the format hh:mm:ss
    string hh = (hours > 10)? std::to_string(hours): "0"+ std::to_string(hours); 
    string mm = (minutes > 10)?std::to_string(minutes):"0"+ std::to_string(minutes);
    string ss = (sec > 10)? std::to_string(sec): "0"+ std::to_string(sec); 
    return hh+":"+mm+":"+ss; 
    }