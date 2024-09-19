MAIN = main
EXECUTABLE = test
FORMULA = formula
GOAL = goal

CPPFLAGS = -g

$(EXECUTABLE): $(MAIN).o $(FORMULA).o $(GOAL).o
	g++ $(CPPFLAGS) $^ -o $@

$(MAIN).o: $(MAIN).cpp
	g++ $(CPPFLAGS) -c $< -o $@

$(FORMULA).o: $(FORMULA).cpp $(FORMULA).hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(GOAL).o: $(GOAL).cpp $(GOAL).hpp
	g++ $(CPPFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o $(EXECUTABLE)

