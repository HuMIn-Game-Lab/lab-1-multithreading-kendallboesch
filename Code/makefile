compile: 
		clang++ -g -std=c++14 Code/CompileJob.cpp Code/JobSystem.cpp Code/JobWorkerThread.cpp Code/RenderJob.cpp Code/JSONJob.cpp Code/main.cpp Code/ParseJob.cpp -o output
		./output

automated: 
		  clang++ -g -std=c++14 ./toCompile/automated.cpp -o auto_out
		  ./auto_out

demoError: 
		   clang++ -g -std=c++14 ./toCompile/demoError.cpp -o error_out
		   ./error_out 

demoWorking: 
			clang++ -g -std=c++14 ./toCompile/demoWorkingJob.cpp -o working_out
			./working_out