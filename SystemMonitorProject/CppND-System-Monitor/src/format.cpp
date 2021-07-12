#include <string>

#include "format.h"

using std::string;

//Helper funtion to return the time
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) { 
    //Convert to hours
    static int hours = 0;
    static int minutes = 0;
    static int sec = 0;
    hours = seconds/3600;
    //Convert to minutes
    minutes = (seconds - hours * 3600)/60;
    //Convert to seconds
    sec = (seconds - hours * 3600) - minutes*60;
    //Convert to the format hh:mm:ss
    string time = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(sec);
    return time; }