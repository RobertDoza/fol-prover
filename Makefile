MAIN = main
EXECUTABLE = test
FORMULA = formula
TERM = term
GOAL = goal
ATOM = atom

CPPFLAGS = -g -Wall -Wextra -Werror -pedantic

$(EXECUTABLE): $(MAIN).o $(FORMULA).o $(ATOM).o $(GOAL).o $(TERM).o
	g++ $(CPPFLAGS) $^ -o $@

$(MAIN).o: $(MAIN).cpp
	g++ $(CPPFLAGS) -c $< -o $@

$(FORMULA).o: $(FORMULA).cpp $(FORMULA).hpp $(ATOM).hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(ATOM).o: $(ATOM).cpp $(ATOM).hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(TERM).o: $(TERM).cpp $(TERM).hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(GOAL).o: $(GOAL).cpp $(GOAL).hpp $(ATOM).hpp
	g++ $(CPPFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o $(EXECUTABLE)

