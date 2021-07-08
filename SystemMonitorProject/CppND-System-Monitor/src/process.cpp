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
Process :: Process(int pid) : pid_(pid){
  uid_     = LinuxParser::Uid(pid_);
  username_= LinuxParser::User(pid_);
  vector<string> CpuUtil = LinuxParser::CpuUtilization(pid_);
  RamInfo_ = LinuxParser::Ram(pid_);
  command_ = LinuxParser::Command(pid_);
  uptime_ = LinuxParser::UpTime();
}

// TODO: Return this process's ID
int Process::Pid() { return 0; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return 0; }

// TODO: Return the command that generated this process
string Process::Command() { return string(); }

// TODO: Return this process's memory utilization
string Process::Ram() { return string(); }

// TODO: Return the user (name) that generated this process
string Process::User() { return string(); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

//Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { 
  return (this->pid_ < a.pid_); }