#pragma once 
#include <mutex> 
#include <map> 
#include <deque> 
#include <vector> 
#include <thread> 
#include "JobSystem.h"
#include "Job.h" 

class JobSystem; 

class JobWorkerThread
{
    friend class JobSystem; 

    public: 
        JobWorkerThread(const char* uniqueName, unsigned long workerJobChannels, JobSystem* jobsystem);
        ~JobWorkerThread(); 

        void startUp(); 
        void work(); 
        void shutDown(); 
        void wait(); 

        bool isStopping() const; 
        void setWorkerJobChannels(unsigned long workerJobChannels); 
        static void workerThreadMain(void* workerThreadObject);
        std::thread*        m_thread = nullptr; 

        
    private: 
        const char *        m_uniqueName; 
        unsigned long       m_workerJobChannels = 0xFFFFFFFF;
        bool                m_isStopping = false; 
        JobSystem*          m_jobSystem = nullptr; 
        //std::thread*        m_thread = nullptr; 
        mutable std::mutex  m_workerStatusMutex;
        
};