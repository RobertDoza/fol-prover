MAIN = main
EXECUTABLE = test
FORMULA_BASE = formula
FORMULA_ATOM = atom
FORMULA_CONN = connective
TERM = term
GOAL = goal

CPPFLAGS = -g -Wall -Wextra -Werror -pedantic

$(EXECUTABLE): $(MAIN).o $(FORMULA_BASE).o $(FORMULA_ATOM).o $(FORMULA_CONN).o $(GOAL).o $(TERM).o
	g++ $(CPPFLAGS) $^ -o $@

$(MAIN).o: $(MAIN).cpp
	g++ $(CPPFLAGS) -c $< -o $@

$(FORMULA_BASE).o: $(FORMULA_BASE).cpp $(FORMULA_BASE).hpp $(FORMULA_ATOM).hpp $(FORMULA_CONN).hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(FORMULA_ATOM).o: $(FORMULA_ATOM).cpp $(FORMULA_ATOM).hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(FORMULA_CONN).o: $(FORMULA_CONN).cpp $(FORMULA_CONN).hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(TERM).o: $(TERM).cpp $(TERM).hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(GOAL).o: $(GOAL).cpp $(GOAL).hpp $(FORMULA_ATOM).hpp $(FORMULA_CONN).hpp
	g++ $(CPPFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o $(EXECUTABLE)

