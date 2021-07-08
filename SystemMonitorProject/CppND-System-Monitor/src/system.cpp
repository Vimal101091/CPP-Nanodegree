#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

//Defining constructor for system class
/*System::System() : pids_(LinuxParser::Pids()){

for(auto pid : pids_){
      processes_.push_back((Process)pid);  
    }
}*/


// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
  for(auto pid: LinuxParser::Pids()){
    processes_.push_back(Process{pid});
  } 
  std::sort(std::begin(processes_), std::end(processes_));
  return processes_; }

//Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

//Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

//Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

//Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

//Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

//Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }