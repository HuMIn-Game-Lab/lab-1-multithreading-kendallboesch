#include "Job.h"
#include <unordered_map>
#include <fstream> 
#include <regex> 
//#include "/Users/kendallboesch/Desktop/CS3341-FoundationsOfModernComputing/Lab-1/lab-1-multithreading-kendallboesch/vcpkg/ports/nlohmann-json"
//#include <nlohmann/json.hpp>
//#include "/Users/kendallboesch/Desktop/CS3341-FoundationsOfModernComputing/Lab-1/lab-1-multithreading-kendallboesch/Code/json-develop/include/nlohmann/json.hpp"
//#include "/Users/kendallboesch/Desktop/CS3341-FoundationsOfModernComputing/Lab-1/lab-1-multithreading-kendallboesch/Code/json-develop/single_include/nlohmann/json.hpp"
// #include "/Users/kendallboesch/Desktop/CS3341-FoundationsOfModernComputing/Lab-1/lab-1-multithreading-kendallboesch/Code/json-develop/include/nlohmann/json.hpp"
// #include "/Users/kendallboesch/Desktop/CS3341-FoundationsOfModernComputing/Lab-1/lab-1-multithreading-kendallboesch/Code/json-develop/include/nlohmann/json_fwd.hpp
//using json = nlohmann::json;

// //#include "rapidjson/document.h"
// #include "/Users/kendallboesch/Desktop/CS3341-FoundationsOfModernComputing/Lab-1/lab-1-multithreading-kendallboesch/Code/rapidjson-master/include/rapidjson/document.h"
// //include "rapidjson/writer.h"
// #include "/Users/kendallboesch/Desktop/CS3341-FoundationsOfModernComputing/Lab-1/lab-1-multithreading-kendallboesch/Code/rapidjson-master/include/rapidjson/writer.h"
// //#include "rapidjson/stringbuffer.h"
// #include "/Users/kendallboesch/Desktop/CS3341-FoundationsOfModernComputing/Lab-1/lab-1-multithreading-kendallboesch/Code/rapidjson-master/include/rapidjson/stringbuffer.h"
// #include "/Users/kendallboesch/Desktop/CS3341-FoundationsOfModernComputing/Lab-1/lab-1-multithreading-kendallboesch/Code/rapidjson-master/include/rapidjson/uri.h"
struct Error
{
    std::string file; 
    std::string errorMessage; 
    int lineNum;
    int colNum;//
};
class ParseJob : public Job 
{
    public: 
        ParseJob(int id, std::string unparsedText); 
        std::string getFile(); 
        std::string getErrorMessage(); 
        void execute() override; 
        int getLineNum(); 
        int getColNum(); 
        std::unordered_map<std::string, std::vector<Error>> jobErrors; 
        std::string unparsedText; 
        int jobId; 
    private: 
        

};