MAIN = main
EXECUTABLE = test
FORMULA = formula
TERM = term
GOAL = goal

CPPFLAGS = -g -Wall -Wextra -Werror -pedantic

$(EXECUTABLE): $(MAIN).o $(FORMULA).o $(GOAL).o $(TERM).o
	g++ $(CPPFLAGS) $^ -o $@

$(MAIN).o: $(MAIN).cpp
	g++ $(CPPFLAGS) -c $< -o $@

$(FORMULA).o: $(FORMULA).cpp $(FORMULA).hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(TERM).o: $(TERM).cpp $(TERM).hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(GOAL).o: $(GOAL).cpp $(GOAL).hpp
	g++ $(CPPFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o $(EXECUTABLE)

