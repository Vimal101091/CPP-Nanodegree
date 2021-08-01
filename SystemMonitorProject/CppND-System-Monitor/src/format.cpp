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
    string time = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(sec);
    return time; 
    }