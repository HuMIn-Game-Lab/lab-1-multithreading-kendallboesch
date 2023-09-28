#include "CompileJob.h"
#include <iostream> 
#include <string> 
#include <array> 

void CompileJob::execute(std::string com) 
{
    std::array<char, 128> buffer; 
    std::string command = com; 

    command.append(" 2>&1"); 

    FILE* pipe = popen(command.c_str(), "r"); 

    if(!pipe) 
    {
        std::cout << "popen filed: failed to open pipe" << std::endl; 
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