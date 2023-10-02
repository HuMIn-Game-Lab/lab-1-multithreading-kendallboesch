// #include "CompileJob.h"
// #include <iostream> 
// #include <string> 
// #include <array> 
// #include "ParseJob.h"
// #include "JobSystem.h"
// #include <atomic>



// CompileJob::CompileJob(int jobID, int jobType, std::string path)
// {
//     this->m_jobChannels = 0xFFFFFFFF; 
//     this->m_jobType = jobType;
//     this->m_jobID = jobID;
//     this->command = path; 

// }
// void CompileJob::execute() 
// {
//     std::cout << "in execute" << std::endl;
//     std::array<char, 128> buffer; 
//    // std::string pipeCommand = "make " + this->command; 
//     std::string res; 
//     std::string pipeCommand = "make automated";

//     pipeCommand.append(" 2>&1"); 

//     FILE* pipe = popen(pipeCommand.c_str(), "r"); 

//     if(!pipe) 
//     {
//         std::cerr << "popen filed: failed to open pipe" << std::endl; 
//         this->returnCode = 1; // abnormal termination 
//         return; 
//     }

//     while(fgets(buffer.data(), 128, pipe) != NULL)
//     {
//         this->output.append(buffer.data()); 
//         res+=buffer.data(); 
//     }

//     this->returnCode = pclose(pipe);
//     std::cout << res << std::endl; 

//     if(returnCode != 0)
//     {
//         ParseJob *job = new ParseJob(2,res ); 
//     }
    

//     std::cout << "Job " << this->getUniqueID() << " has been executed" << std::endl;

// //     std::cout << "Compile job " << this->getUniqueID() << " Return Code: " << this->returnCode << std::endl; 
// //     std::cout << "Compile job " << this->getUniqueID() << " output : \n" << this->output << std::endl; 
// //    // this->jobCompleteCallback(); 
//     return; 
// }

// void CompileJob::setID(int id)
// {
//     m_jobID = id;
// }
// void CompileJob::jobCompleteCallback()
// {
//     std::cout << "in JobCompletreCallback" << std::endl;
//     std::cout << "Compile job " << this->getUniqueID() << " Return Code: " << this->returnCode << std::endl; 
//     std::cout << "Compile job " << this->getUniqueID() << " output : \n" << this->output << std::endl; 
// }
#include "CompileJob.h"
#include "ParseJob.h"
#include <iostream>
#include <string>
#include <array>

/*********
 *  why not just include these ^^ in the .h?
 *
 * in general, you should put your dependencies ____
 *
 * downside of includes in .h instead of .cpp?
 *
 */


// thread will grab cide, compile it, and return the results
void CompileJob::execute() {
    std::array<char, 128> buffer;
    std::string command = "make test";
    //std::string command = "curl -s -X POST -H 'Content-type: application/json' --data "

    //Redirect -> redirects cerr to cout ;
        //Send everything from cerr to cout
    // so errors are usually output to cerr not cout
    // PC: Redirects cerr to cout
    command.append(" 2>&1");

  // basically gives me terminal to work on, but opening this terminal inside a thread
        // everything that happens on that cout will now come back to me on this threstd:ad
    //PC: open pipe and run command
    FILE* pipe = popen(command.c_str(), "r");

    if(!pipe)
    {
        std::cout << "popen failed: failed to open pipe" << std::endl;
        return;
    }
    //capture everything that happens on the screen if my code compiles wothout errors
    // PROF COM: read till end of process
    std::string res; 
    while(fgets(buffer.data(), 128, pipe) != NULL)
    {
        this->output.append(buffer.data());
        res.append(buffer.data());
    }

    //PC: close pipe & get retyrn code
    this->returnCode = pclose(pipe);    // will return to me what the return code is

    if(returnCode != 0)
    {
        //there was an error 
        std::cout << "CompileJob Results: " << res << std::endl; 
       // ParseJob pjb* = new ParseJob(res); 
       ParseJob* pjb = new ParseJob(0xFFFFFFFF, -1); 
    }

    std::cout << "Job " << this->getUniqueID() << " has been executed " << std::endl;
}

//have code automatically compile -> hoe could you use somehting like that
    // automated regression testing

void CompileJob::jobCompleteCallback()
{
    std::cout << "Compile job " << this->getUniqueID() << " Return Code " << this->returnCode << std::endl;
    std::cout << "Compile job " << this->getUniqueID() << " output \n" << this->output << std::endl;
}