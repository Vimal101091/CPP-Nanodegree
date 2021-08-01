#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

//Defining constructor for Process class
Process :: Process(int pid) : pid_(pid),
  uid_ (LinuxParser::Uid(pid_)),
  username_(LinuxParser::User(pid_)),
  RamInfo_ (LinuxParser::Ram(pid_)),
  command_ (LinuxParser::Command(pid_)),
  uptime_ (LinuxParser::UpTime(pid_)),
  CpuUtilization_(this->CpuUtilization()){}
  
//Return this process's ID
int Process::Pid() { return pid_; }

//Return this process's CPU utilization
float Process::CpuUtilization() { 
  //Extract the processes' CPU parameters
  std::vector<std::string> ParamCpu = LinuxParser::CpuUtilization(pid_);
  float utime      =  std::stoi(ParamCpu[0]);
  float stime      =  std::stoi(ParamCpu[1]);
  float cutime     =  std::stoi(ParamCpu[2]);
  float cstime     =  std::stoi(ParamCpu[3]);
  float starttime  =  std::stoi(ParamCpu[4]);
  float totaltime  =  utime + stime + cutime + cstime;
  float  uptime  = LinuxParser::UpTime();
  float seconds    =  uptime - (starttime / sysconf(_SC_CLK_TCK));
  CpuUtilization_ =   (totaltime/sysconf(_SC_CLK_TCK))/seconds; //Calculation of process CPU utilization
  return CpuUtilization_; }

//Return the command that generated this process
string Process::Command() { return command_; }

//Return this process's memory utilization
string Process::Ram() { 
  long RamInfoKb = std::stol(RamInfo_);
  int RamInfoMb = (int)RamInfoKb*0.001; //Convert RamInfo from Kb to MB
  return std::to_string(RamInfoMb); 
  }

//Return the user (name) that generated this process
string Process::User() { return username_; }

//Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

//Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process& a){ 
  return (this->CpuUtilization_ > a.CpuUtilization_);
   }