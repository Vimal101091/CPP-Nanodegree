#ifndef PROCESSOR_H
#define PROCESSOR_H

#include<vector>
#include<string>
#include "linux_parser.h"

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  Processor();
  
  //Declare any necessary private members
 private:
 long user_ = 0;
 long nice_ = 0;
 long system_ = 0;
 long idle_ = 0;
 long ioWait_ = 0;
 long irq_ = 0;
 long softIrq_ = 0;
 long steal_ = 0;
 float cpu_utilization_ = 0.0;
};

#endif