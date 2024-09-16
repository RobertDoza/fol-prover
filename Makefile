MAIN = main
EXECUTABLE = test
FORMULA = formula
GOAL = goal

$(EXECUTABLE): $(MAIN).o $(FORMULA).o $(GOAL).o
	g++ $^ -o $@

$(MAIN).o: $(MAIN).cpp
	g++ -c $< -o $@

$(FORMULA).o: $(FORMULA).cpp $(FORMULA).hpp
	g++ -c $< -o $@

$(GOAL).o: $(GOAL).cpp $(GOAL).hpp
	g++ -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o $(EXECUTABLE)

