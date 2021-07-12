#include "processor.h"

//Constrcutor of Process Class
Processor::Processor(){
    std::vector<std::string> CpuData = LinuxParser::CpuUtilization();
    user_   = std::stol(CpuData[0], nullptr, 10);
    nice_   = std::stol(CpuData[1], nullptr, 10);
    system_ = std::stol(CpuData[2], nullptr, 10);
    idle_   = std::stol(CpuData[3], nullptr, 10);
    ioWait_ = std::stol(CpuData[4], nullptr, 10);
    irq_    = std::stol(CpuData[5], nullptr, 10);
    softIrq_= std::stol(CpuData[6], nullptr, 10);
    steal_  = std::stol(CpuData[7], nullptr, 10);
}
  
//Return the aggregate CPU utilization
float Processor::Utilization() { 
    //Read various CPU parameters
    std::vector<std::string> CpuData = LinuxParser::CpuUtilization();
    long user    = std::stol(CpuData[0]);
    long nice    = std::stol(CpuData[1]);
    long system  = std::stol(CpuData[2]);
    long idle    = std::stol(CpuData[3]);
    long ioWait  = std::stol(CpuData[4]);
    long irq     = std::stol(CpuData[5]);
    long softIrq = std::stol(CpuData[6]);
    long steal   = std::stol(CpuData[7]);
 
    long Idle    = idle + ioWait;
    long NonIdle = user + nice + system + irq + softIrq + steal; 
    long Total   = Idle + NonIdle; 

    long prevIdle    = idle_ + ioWait_;
    long prevNonIdle = user_ + nice_ + system_ + irq_ + softIrq_ + steal_; 
    long prevTotal   = prevIdle + prevNonIdle; 

    long totald  = Total - prevTotal;
    long idled   = Idle - prevIdle;
    
    if(totald > 0){
         cpu_utilization_ = (float)(totald - idled)/totald;  //CPU Utilization calculation     
    }
    //Update the most recent CPU parameter values
    user_   = user;
    nice_   = nice;
    system_ = system;
    idle_   = idle;
    ioWait_ = ioWait;
    irq_    = irq;
    softIrq_= softIrq;
    steal_  = steal;

    return cpu_utilization_;}