#ifndef PROCESSOR_H
#define PROCESSOR_H

#include<vector>
#include<string>
#include "linux_parser.h"

class Processor {
 public:
  float Utilization();  //See src/processor.cpp

  Processor();
  
  //Declare any necessary private members
 private:
 float user_ = 0;
 float nice_ = 0;
 float system_ = 0;
 float idle_ = 0;
 float ioWait_ = 0;
 float irq_ = 0;
 float softIrq_ = 0;
 float steal_ = 0;
 float cpu_utilization_ = 0.0;
};

#endif