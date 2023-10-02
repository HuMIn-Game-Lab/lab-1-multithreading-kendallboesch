#include "RenderJob.h"
#include <iostream>

void RenderJob::execute(){
    int total = 0;

    std::vector<int>::iterator it = data.begin();
    for(; it != data.end(); ++it){
        total += *it;
    }

    it = data.begin();
    for(; it != data.end(); ++it){
        total += *it;
    }
    data[0] = total;
    std::cout<< "Job " << this->getUniqueID() << " Has Been Executed" << std::endl;
}

void RenderJob::jobCompleteCallback() {
    std::cout << "Job " << this->getUniqueID() << "  Calculated Sum: " << this->data[0] << std::endl;
}