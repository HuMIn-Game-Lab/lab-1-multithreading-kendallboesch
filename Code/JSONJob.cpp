#include "JSONJob.h"
#include <iostream> 
#include <fstream> 
#include <string> 
#include <sstream> 

using namespace rapidjson; 

void JSONJob::execute() 
{

    Document doc(kObjectType); 
    Document::AllocatorType& allocator = doc.GetAllocator(); 
    std::ifstream prev("errors.json");
    bool jsonReadError = false; 
    if(prev.is_open() && prev.peek() != std::ifstream::traits_type::eof())
    {
        std::cout << "EXISTING JSON" << std::endl; 
        std::ostringstream ss; 
        ss << prev.rdbuf(); 
        std::string existingJson = ss.str(); 
        if(doc.Parse(existingJson.c_str()).HasParseError())
        {
            std::cout << "EXISTING JSON PARSE ERROR" << std::endl; 
            jsonReadError = true; 
        }
        else
        {
            prev.close(); 
            std::ofstream prev("errors.json"); 
            prev << ""; 
            prev.close(); 
            std::cout << "Cleared contents" << std::endl; 
        }
    }
    if(!jsonReadError)
    {
        for(const auto& file : errorMap)
        {
                Value fileErrorsArray(kArrayType); 
                for(const auto& error : file.second)
                {
                    Value errorObj(kObjectType);
                // errorObj.AddMember("file", Value().SetString(error.file.c_str(), static_cast<SizeType>(error.file.length()), allocator), allocator); 
                    errorObj.AddMember("errorMessage", Value().SetString(error.errorMessage.c_str(), static_cast<SizeType>(error.errorMessage.length()), allocator), allocator);
                    errorObj.AddMember("lineNum", error.lineNum, allocator);
                    errorObj.AddMember("colNum", error.colNum, allocator);
                    errorObj.AddMember("src", Value().SetString(error.src.c_str(), static_cast<SizeType>(error.src.length()), allocator), allocator);
                    fileErrorsArray.PushBack(errorObj, allocator);
                }
                doc.AddMember(Value().SetString(file.first.c_str(), static_cast<SizeType>(file.first.length()), allocator),fileErrorsArray, allocator);
            // Value key(file.first.c_str(), static_cast<SizeType>(file.first.length()), allocator); 
            // doc[key] = fileErrorsArray;
            //doc[file.first.c_str()] = fileErrorsArray; 
                StringBuffer buffer;
            //Writer<StringBuffer> writer(buffer);
                PrettyWriter<StringBuffer> writer(buffer); 
                writer.SetIndent(' ', 2); 
                writer.SetFormatOptions(PrettyFormatOptions::kFormatDefault);
                doc.Accept(writer);

                std::string jsonString = buffer.GetString();
                // std::ifstream prev("errors.json"); 
                // if(prev)
                // {
                //     //There is previous information in the error.json file
                //     std::ostringstream ss; 
                //     ss << prev.rdbuf(); 
                //     std::string existingJson = ss.str(); 

                //     if(doc.Parse(existingJson.c_str()).HasParseError())
                //     {
                //         std::cout << "Error parsing existing json " <<std::endl; 
                //     }
                // }
                // else 
                // {
                    std::ofstream outputFile("errors.json", std::ios::app);
                    if (outputFile.is_open()) 
                    {
                        outputFile << jsonString << std::endl;
                        outputFile.close();
                        std::cout << "JSON data written to errors.json" << std::endl;
                    }
                    else 
                    {
                        std::cout << "failed to open 'errors.json'" << std::endl; 
                    }
            // }
            

        }
    }
}