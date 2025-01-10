# Variabili
CXX = g++
CXXFLAGS = -O2 -Wall `root-config --cflags`
LDFLAGS = `root-config --libs`
SRC = main.cc
EXEC = main

# Obiettivo di compilazione
all: $(EXEC)

# Regola per creare l'eseguibile
$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Regola per pulire i file generati
clean:
	rm -f $(EXEC) grafico.png

# Regola per eseguire il programma
run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run
