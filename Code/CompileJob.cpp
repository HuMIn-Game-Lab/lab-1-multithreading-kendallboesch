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
    //std::string command = "make demoError";
    std::string command = "make "; 
    //std::string command = "curl -s -X POST -H 'Content-type: application/json' --data "

    //Redirect -> redirects cerr to cout ;
        //Send everything from cerr to cout
    // so errors are usually output to cerr not cout
    // PC: Redirects cerr to cout
    command.append(this->target); 
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
        //std::cout << "CJB return code: " << returnCode << std::endl; 
        //there was an error 
        //std::cout << "CompileJob Results: " << res << std::endl; 
        this->compResults = res; 
       // ParseJob pjb* = new ParseJob(res); 
      // ParseJob* pjb = new ParseJob(0xFFFFFFFF, -1); 
       //pjb->unparsedText = res; 

       //jobs->push_back(pjb); 
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