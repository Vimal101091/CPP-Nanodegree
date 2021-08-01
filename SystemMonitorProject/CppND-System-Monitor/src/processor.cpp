#include "processor.h"

//Constrcutor of Process Class
Processor::Processor(){
    std::vector<std::string> CpuData = LinuxParser::CpuUtilization();
    user_   = std::stof(CpuData[0]);
    nice_   = std::stof(CpuData[1]);
    system_ = std::stof(CpuData[2]);
    idle_   = std::stof(CpuData[3]);
    ioWait_ = std::stof(CpuData[4]);
    irq_    = std::stof(CpuData[5]);
    softIrq_= std::stof(CpuData[6]);
    steal_  = std::stof(CpuData[7]);
}
  
//Return the aggregate CPU utilization
float Processor::Utilization() { 
    //Read various CPU parameters
    std::vector<std::string> CpuData = LinuxParser::CpuUtilization();
    float user    = std::stof(CpuData[0]);
    float nice    = std::stof(CpuData[1]);
    float system  = std::stof(CpuData[2]);
    float idle    = std::stof(CpuData[3]);
    float ioWait  = std::stof(CpuData[4]);
    float irq     = std::stof(CpuData[5]);
    float softIrq = std::stof(CpuData[6]);
    float steal   = std::stof(CpuData[7]);
 
    float Idle    = idle + ioWait;
    float NonIdle = user + nice + system + irq + softIrq + steal; 
    float Total   = Idle + NonIdle;
    float prevIdle    = idle_ + ioWait_;
    float prevNonIdle = user_ + nice_ + system_ + irq_ + softIrq_ + steal_; 
    float prevTotal   = prevIdle + prevNonIdle; 

    float totald  = Total - prevTotal;
    float idled   = Idle - prevIdle;
    
    if(totald > 0){
         cpu_utilization_ = (totald - idled)/totald;  //CPU Utilization calculation     
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