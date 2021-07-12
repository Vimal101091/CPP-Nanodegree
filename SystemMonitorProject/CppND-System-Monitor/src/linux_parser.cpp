#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// Read OS information
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// Read OS version information
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// Read the list of processes from process directory
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

//Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string label;
  string line;
  long MemTotal,MemFree, data;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
    std::istringstream linestream(line);
    linestream >> label >> data;
    //Extract relevant data
    if(label == "MemTotal:"){
      MemTotal = data;
    } 
    else if(label == "MemFree:")
    {
      MemFree = data;
    }
   }
  }
   //Calculate system memory utilisation and return the result
   float result = (float)(MemTotal - MemFree)/MemTotal;
   return (result >= 0 && result <= 100)? result : 0.0;
 }

//Read and return the system uptime
long LinuxParser::UpTime() { 
  float data1, uptime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >>data1 >> uptime;
  }
  return (long)uptime;
 }

// Read and return the number of jiffies for the system
// NOT USED
long LinuxParser::Jiffies() { return 0; }

// Read and return the number of active jiffies for a PID
// NOT USED
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

// Read and return the number of active jiffies for the system
// NOT USED
long LinuxParser::ActiveJiffies() { return 0; }

// Read and return the number of idle jiffies for the system
// NOT USED
long LinuxParser::IdleJiffies() { return 0; }

//Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  string label;
  string line;
  string user, nice, system, idle;
  string ioWait, irq, softIrq, steal; 
  vector<string> CpuUtil;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
    std::istringstream linestream(line);
    linestream >> label >> user >> nice >> system >> idle >> ioWait >> irq >> softIrq >> steal;
    //Extract relevant data
    if(label == "cpu"){
      CpuUtil.push_back(user);
      CpuUtil.push_back(nice);
      CpuUtil.push_back(system);
      CpuUtil.push_back(idle);
      CpuUtil.push_back(ioWait);
      CpuUtil.push_back(irq);
      CpuUtil.push_back(softIrq);
      CpuUtil.push_back(steal);
      break;
    } 
   }
  } 
  return CpuUtil; 
}

//Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string label;
  string line;
  int totalprocess, data;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
    std::istringstream linestream(line);
    linestream >> label >> data;
    //Extract relevant data
    if(label == "processes"){
      totalprocess = data;
     } 
    } 
   }
   return totalprocess; 
 }

//Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string label;
  string line;
  int runningprocess, data;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
    std::istringstream linestream(line);
    linestream >> label >> data;
    //Extract relevant data
    if(label == "procs_running"){
      runningprocess = data;
     } 
    } 
   }
   return runningprocess; 
  }

//Read and return the Cpu utilization of a process 
vector<string> LinuxParser::CpuUtilization(int pid) {
  string line, data;
  int count = 0;
  vector<string> ProcCpuUtil;
  string utime, stime, cutime, cstime, starttime;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
    std::stringstream linestream(line);
    //Extract relevant data
    while(linestream >> data){
        count++;
        if(count == 14){
          utime  = data;
        } else if(count == 15){
          stime = data; 
        } else if(count == 16){
          cutime = data;
        } else if(count == 17){
          cstime = data;
        }else if(count == 22){
          starttime = data;
        }
       }
      } 
    }
    ProcCpuUtil.push_back(utime);
    ProcCpuUtil.push_back(stime);
    ProcCpuUtil.push_back(cutime);
    ProcCpuUtil.push_back(cstime);
    ProcCpuUtil.push_back(starttime);
    return ProcCpuUtil;
  }

//Read and return the command associated with a process
string LinuxParser::Command(int pid) { 
  string line, command;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
      std::stringstream linestream(line);
      //Extract relevant data
      linestream >> command;
     } 
    }
    return command; 
  }

//Read and return the memory used by a process
string LinuxParser::Ram(int pid) { 
  string label;
  string line;
  string RamInfo;
  string data1, data2;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
    std::istringstream linestream(line);
    linestream >> label >> data1 >> data2;
    //Extract relevant data
    if(label == "VmSize:"){
      RamInfo = data1;
      break;
     } 
    } 
   }
   return RamInfo; 
  }

//Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) { 
  string label;
  string line;
  string data, uid;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
    std::istringstream linestream(line);
    linestream >> label >> data;
    //Extract relevant data
    if(label == "Uid:"){
      uid = data;
     } 
    } 
   }
  return uid; 
  }

// Read and return the user associated with a process
string LinuxParser::User(int pid) { 
  string label, data1, data2;
  string username;
  string line;
  string uid = LinuxParser::Uid(pid);
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
    std::replace(line.begin(), line.end(), ':', ' ');  
    std::istringstream linestream(line);
    linestream >> label >> data1 >> data2;
    //Extract relevant data
    if(data1 == "x" && data2 == uid){
      username = label;
     } 
    } 
   }
  return username; 
  }

// Read and return the uptime of a process
long LinuxParser::UpTime(int pid[[maybe_unused]]) { 
  string line;
  float data1, data2;
  long uptimesec;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
    std::stringstream linestream(line);
    //Extract relevant data
    linestream >> data1 >> data2; 
    }
    //Calculate process Uptime in seconds
    uptimesec = (long)data1;
    }
    return uptimesec;
   }
