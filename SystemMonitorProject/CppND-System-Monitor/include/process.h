#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  //Constructor instantiation for Process class
  Process(int);
  //Move constructor
  //Process(Process&&);
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  //Declare any necessary private members
 private:
  int pid_; 
  std::string uid_;
  std::string username_;
  std::string RamInfo_;
  std::string command_;
  long uptime_;
};

#endif