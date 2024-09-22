SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

MAIN = main
TERM = term
FORMULA_BASE = formula
FORMULA_ATOM = atom
FORMULA_CONN = connective
GOAL = goal
EXECUTABLE = test

CPPFLAGS = -g -Wall -Wextra -Werror -pedantic

$(EXECUTABLE): $(BIN_DIR)/$(MAIN).o $(BIN_DIR)/$(FORMULA_BASE).o $(BIN_DIR)/$(FORMULA_ATOM).o $(BIN_DIR)/$(FORMULA_CONN).o $(BIN_DIR)/$(GOAL).o $(BIN_DIR)/$(TERM).o
	g++ $(CPPFLAGS) $^ -o $@

$(BIN_DIR)/$(MAIN).o: $(SRC_DIR)/$(MAIN).cpp
	g++ $(CPPFLAGS) -c $< -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(FORMULA_BASE).o: $(SRC_DIR)/$(FORMULA_BASE).cpp $(INC_DIR)/$(FORMULA_BASE).hpp $(INC_DIR)/$(FORMULA_ATOM).hpp $(INC_DIR)/$(FORMULA_CONN).hpp
	g++ $(CPPFLAGS) -c $< -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(FORMULA_ATOM).o: $(SRC_DIR)/$(FORMULA_ATOM).cpp $(INC_DIR)/$(FORMULA_ATOM).hpp
	g++ $(CPPFLAGS) -c $< -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(FORMULA_CONN).o: $(SRC_DIR)/$(FORMULA_CONN).cpp $(INC_DIR)/$(FORMULA_CONN).hpp
	g++ $(CPPFLAGS) -c $< -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(TERM).o: $(SRC_DIR)/$(TERM).cpp $(INC_DIR)/$(TERM).hpp
	g++ $(CPPFLAGS) -c $< -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(GOAL).o: $(SRC_DIR)/$(GOAL).cpp $(INC_DIR)/$(GOAL).hpp $(INC_DIR)/$(FORMULA_ATOM).hpp $(INC_DIR)/$(FORMULA_CONN).hpp
	g++ $(CPPFLAGS) -c $< -o $@ -I$(INC_DIR)

.PHONY: clean

clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/$(EXECUTABLE)

