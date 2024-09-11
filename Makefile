MAIN = main
EXECUTABLE = test
FORMULA = formula

$(EXECUTABLE): $(MAIN).o $(FORMULA).o
	g++ $^ -o $@

$(MAIN).o: $(MAIN).cpp
	g++ -c $< -o $@

$(FORMULA).o: $(FORMULA).cpp $(FORMULA).hpp
	g++ -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o $(EXECUTABLE)

