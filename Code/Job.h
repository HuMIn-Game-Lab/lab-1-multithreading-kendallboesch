// #pragma once 
// #include <mutex>
// #include <map>
// #include <deque>
// #include <vector>
// #include <thread>
// class Job 
// {
//     friend class JobSystem; 
//     friend class JobWorkerThread;
//     public: 
//         // Job(unsigned long jobChannels = 0xFFFFFFFF, int jobType = -1, std::string path = "make") : m_jobChannels(jobChannels), m_jobType(jobType)
//         // {
//         //static int s_nextJobID = 0; 
//        // m_jobID = s_nextJobID; 
//         // }
//         virtual ~Job() {}
//         virtual void execute() = 0; 
//         virtual void jobCompleteCallback() {}
//         int getUniqueID() const {return m_jobID;}

//         int m_jobID; 
//         int m_jobType; 
//         unsigned long m_jobChannels; 


//     public:
//         // virtual void execute()  = 0; 
//         // virtual ~Job(){}; 

// }; 
#pragma once // What is this? --> prevents circular includes
#include <mutex>
#include <map>
#include <deque>
#include <vector>
#include <thread>

class Job{
    friend class JobSystem; //what is friend class
    friend class JobWorkerThread;

public:
    //What are job channels
    // Inside firsy parenthesis, were defineng parameters for constructor with defaulr values
    Job(unsigned long jobChannels = 0xFFFFFFFF, int jobType = -1) : m_jobChannels(jobChannels), m_jobType(jobType){
        static int s_nextJobID = 0;
        m_jobID = s_nextJobID++;
    }
    std::string compResults; 

    virtual ~Job() {}
    //Virtual = ca
    //pure virtual = must be inherited & have to overload --> cerating an abstraxct class
    virtual void execute() = 0;
    // do not have to implement --> if you dont its going to calll this body (aka do nothing)
    virtual void jobCompleteCallback() {}
    int getUniqueID() const {return m_jobID; }

private:
    int m_jobID = -1;
    int m_jobType = -1;

    unsigned long m_jobChannels = 0xFFFFFFFF;
};


