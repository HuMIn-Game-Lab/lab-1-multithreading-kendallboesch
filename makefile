compile: 
		clang++ -g -std=c++14 Code/CompileJob.cpp Code/JobSystem.cpp Code/JobWorkerThread.cpp Code/RenderJob.cpp Code/main.cpp Code/ParseJob.cpp Code/JSONJob.cpp -o output
		./output $(ARGS)

automated: 
		  clang++ -g -std=c++14 Code/toCompile/automated.cpp -o auto_out
		  ./auto_out

demoError: 
		   clang++ -g -std=c++14 Code/toCompile/demoError.cpp -o error_out
		   ./error_out 

demoWorking: 
			clang++ -g -std=c++14 Code/toCompile/demoWorkingJob.cpp -o working_out
			./working_out