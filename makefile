compile: 
		clang++ -g -std=c++14 Code/CompileJob.cpp Code/JobSystem.cpp Code/JobWorkerThread.cpp Code/RenderJob.cpp Code/main.cpp Code/ParseJob.cpp -o output
		./output
automated: 
		clang++ -g -std=c++14 Code/toCompile/automated.cpp -o auto_out
		./auto_out