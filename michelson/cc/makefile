# Nome dell'eseguibile
EXEC = graphlambda
EXEC1 = graphnaria
EXEC2 = graphluce
EXEC3 = graphsdio

# File sorgente
SRC = lambdalaser.cc
SRC1 = naria.cc
SRC2 = pacchettoluce.cc
SRC3 = doppiettosodio.cc

# Comandi e flag per ROOT
ROOTCFLAGS := $(shell root-config --cflags)
ROOTLIBS := $(shell root-config --libs)

# Compilatore
CXX = g++

# Flags di compilazione
CXXFLAGS = -Wall -O2 $(ROOTCFLAGS)

# Regola per creare l'eseguibile
make: $(EXEC) $(EXEC1) $(EXEC2) $(EXEC3)

$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(SRC) $(ROOTLIBS)
$(EXEC1): $(SRC1)
	$(CXX) $(CXXFLAGS) -o $(EXEC1) $(SRC1) $(ROOTLIBS)
$(EXEC2): $(SRC2)
	$(CXX) $(CXXFLAGS) -o $(EXEC2) $(SRC2) $(ROOTLIBS)
$(EXEC3): $(SRC3)
	$(CXX) $(CXXFLAGS) -o $(EXEC3) $(SRC3) $(ROOTLIBS)

# Regola per eseguire il programma
run: $(EXEC) $(EXEC1) $(EXEC2) $(EXEC3)
	./$(EXEC)
	./$(EXEC1)
	./$(EXEC2)
	./$(EXEC3)

# Regola per pulire i file generati
clean:
	rm -f $(EXEC) *.o *.pdf

# Regola per compilare e eseguire in un solo comando
all: $(EXEC) run
