TT=scientificonvert.cc
EE=digitseparator.cc
BB=prog
MM=prog1

$(BB): $(TT)
	g++ -o $(BB) $(TT)

$(MM): $(EE)
	g++ -o $(MM) $(EE)

run:
	./$(BB)

run1:
	./$(MM)

clean:
	rm $(BB) $(MM)
