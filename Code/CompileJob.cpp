#include "CompileJob.h"
#include <iostream> 
#include <string> 
#include <array> 

CompileJob::CompileJob(unsigned long channel, int jobType, std::string path)
{
    this->m_jobChannels = channel; 
    this->m_jobType = jobType;
    this->command = path; 
    
}
void CompileJob::execute() 
{
    std::array<char, 128> buffer; 
    std::string pipeCommand = "make " + this->command; 

    pipeCommand.append(" 2>&1"); 

    FILE* pipe = popen(pipeCommand.c_str(), "r"); 

    if(!pipe) 
    {
        std::cout << "popen filed: failed to open pipe" << std::endl; 
        this->returnCode = 1; // abnormal termination 
        return; 
    }

    while(fgets(buffer.data(), 128, pipe) != NULL)
    {
        this->output.append(buffer.data()); 
    }

    this->returnCode = pclose(pipe);

    std::cout << "Job " << this->getUniqueID() << "has been executed" << std::endl;
}
void CompileJob::jobCompleteCallback()
{
    std::cout << "Compile job " << this->getUniqueID() << " Return Code: " << this->returnCode << std::endl; 
    std::cout << "Compile job " << this->getUniqueID() << " output : \n" << this->output << std::endl; 
}