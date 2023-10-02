compile: 
	clang++ -g -std=c++14 ./Code/*.cpp -o output

automated: 
	clang++ -g -std=c++14 ./Code/toCompile/automated.cpp -o auto_out
	./auto_out

CXX = clang++ # or the appropriate C++ compiler

# Flags for the C++ compiler
CXXFLAGS += -I//Users/kendallboesch/Desktop/CS3341-FoundationsOfModernComputing/Lab-1/lab-1-multithreading-kendallboesch/Code/json-develop/single_include/nlohmann

# Source files and the output executable
SRC = ./Code/*.cpp
EXE = output

all: $(EXE)

$(EXE): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXE)

clean:
	rm -f $(EXE)
