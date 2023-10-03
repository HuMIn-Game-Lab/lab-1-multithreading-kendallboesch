// #include "JSONJob.h"
// #include <iostream> 
// #include <fstream> 
// #include <string> 
// using namespace rapidjson; 

// void JSONJob::execute() 
// {
//     Document doc(kObjectType); 
//     Document::AllocatorType& allocator = doc.GetAllocator(); 

//    for(const auto& file : errorMap)
//    {
//     Value fileErrorsArray(kArrayType); 
//     for(const auto& error : file.second)
//     {
//         Value errorObj(kObjectType);
//         errorObj.AddMember("file", Value().SetString(error.file.c_str(), static_cast<SizeType>(error.file.length()), allocator), allocator); 
//         errorObj.AddMember("errorMessage", Value().SetString(error.errorMessage.c_str(), static_cast<SizeType>(error.errorMessage.length()), allocator), allocator);
//         errorObj.AddMember("lineNum", error.lineNum, allocator);
//         errorObj.AddMember("colNum", error.colNum, allocator);
//         errorObj.AddMember("src", Value().SetString(error.src.c_str(), static_cast<SizeType>(error.src.length()), allocator), allocator);
//         fileErrorsArray.PushBack(errorObj, allocator);
//     }
//     doc.AddMember(Value().SetString(file.first.c_str(), static_cast<SizeType>(file.first.length()), allocator),fileErrorsArray, allocator);

//     StringBuffer buffer;
//     Writer<StringBuffer> writer(buffer);
//     doc.Accept(writer);

//     std::string jsonString = buffer.GetString();

//     std::ofstream outputFile("errors.json");
//     if (outputFile.is_open()) {
//         outputFile << jsonString << std::endl;
//         outputFile.close();
//         std::cout << "JSON data written to errors.json" << std::endl;
//     }

//    }
// }