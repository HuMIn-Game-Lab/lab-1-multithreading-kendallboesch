#include "CompileJob.h"
#include <iostream> 
#include <string> 
#include <array> 
#include "ParseJob.h"
#include "JobSystem.h"
#include <atomic>



CompileJob::CompileJob(int jobID, int jobType, std::string path)
{
    this->m_jobChannels = 0xFFFFFFFF; 
    this->m_jobType = jobType;
    this->m_jobID = jobID;
    this->command = path; 

}
void CompileJob::execute() 
{
    std::cout << "in execute" << std::endl;
    std::array<char, 128> buffer; 
    std::string pipeCommand = "make " + this->command; 
    std::string res; 

    pipeCommand.append(" 2>&1"); 

    FILE* pipe = popen(pipeCommand.c_str(), "r"); 

    if(!pipe) 
    {
        std::cerr << "popen filed: failed to open pipe" << std::endl; 
        this->returnCode = 1; // abnormal termination 
        return; 
    }

    while(fgets(buffer.data(), 128, pipe) != NULL)
    {
        this->output.append(buffer.data()); 
        res+=buffer.data(); 
    }

    this->returnCode = pclose(pipe);

    if(returnCode != 0)
    {
        //ParseJob *job = new ParseJob(JobSystem::NEXT_JOB_ID,res ); 
    }
    

    std::cout << "Job " << this->getUniqueID() << " has been executed" << std::endl;

    std::cout << "Compile job " << this->getUniqueID() << " Return Code: " << this->returnCode << std::endl; 
    std::cout << "Compile job " << this->getUniqueID() << " output : \n" << this->output << std::endl; 
   // this->jobCompleteCallback(); 
    return; 
}

void CompileJob::setID(int id)
{
    m_jobID = id;
}
// void CompileJob::jobCompleteCallback()
// {
//     std::cout << "in JobCompletreCallback" << std::endl;
//     std::cout << "Compile job " << this->getUniqueID() << " Return Code: " << this->returnCode << std::endl; 
//     std::cout << "Compile job " << this->getUniqueID() << " output : \n" << this->output << std::endl; 
// }