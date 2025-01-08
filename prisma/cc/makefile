# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = `root-config --cflags`

# Linker flags
LDFLAGS = `root-config --glibs`

# Name of the source file and output executable
SRC = main.cc
EXE = prismar

# Default target to compile and run the program
all: $(EXE)
	./$(EXE)

# Rule to compile the program
$(EXE): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(SRC) $(LDFLAGS)

# Clean target to remove the executable and PDF file
clean:
	rm -f $(EXE) grafico.pdf
