SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

MAIN = main
TERM = term
FORMULA_BASE = formula
FORMULA_ATOM = atom
FORMULA_CONN = connective
FORMULA_QUAN = quantifier
GOAL = goal
PROOF_MANAGER = proof_state_manager
PROVER = prover
EXECUTABLE = test

LEXER = lex.yy
PARSER = parser.tab

CPPFLAGS = -g -Wall -Wextra -Werror -pedantic --std=c++17

$(EXECUTABLE): $(BIN_DIR)/$(MAIN).o $(BIN_DIR)/$(FORMULA_BASE).o $(BIN_DIR)/$(FORMULA_QUAN).o $(BIN_DIR)/$(FORMULA_CONN).o $(BIN_DIR)/$(FORMULA_ATOM).o $(BIN_DIR)/$(TERM).o $(BIN_DIR)/$(GOAL).o $(BIN_DIR)/$(PROOF_MANAGER).o $(BIN_DIR)/$(PROVER).o $(BIN_DIR)/$(LEXER).o $(BIN_DIR)/$(PARSER).o
	g++ $(CPPFLAGS) $^ -o $@

$(BIN_DIR):
	mkdir $@ -p

$(BIN_DIR)/$(MAIN).o: $(SRC_DIR)/$(MAIN).cpp | $(BIN_DIR)
	g++ $(CPPFLAGS) -c $< -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(FORMULA_BASE).o: $(SRC_DIR)/$(FORMULA_BASE).cpp $(INC_DIR)/$(FORMULA_BASE).hpp $(INC_DIR)/$(FORMULA_ATOM).hpp $(INC_DIR)/$(FORMULA_CONN).hpp $(INC_DIR)/$(FORMULA_QUAN).hpp
	g++ $(CPPFLAGS) -c $< -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(FORMULA_ATOM).o: $(SRC_DIR)/$(FORMULA_ATOM).cpp $(INC_DIR)/$(FORMULA_ATOM).hpp
	g++ $(CPPFLAGS) -c $< -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(FORMULA_CONN).o: $(SRC_DIR)/$(FORMULA_CONN).cpp $(INC_DIR)/$(FORMULA_CONN).hpp
	g++ $(CPPFLAGS) -c $< -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(FORMULA_QUAN).o: $(SRC_DIR)/$(FORMULA_QUAN).cpp $(INC_DIR)/$(FORMULA_QUAN).hpp
	g++ $(CPPFLAGS) -c $< -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(TERM).o: $(SRC_DIR)/$(TERM).cpp $(INC_DIR)/$(TERM).hpp
	g++ $(CPPFLAGS) -c $< -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(GOAL).o: $(SRC_DIR)/$(GOAL).cpp $(INC_DIR)/$(GOAL).hpp $(INC_DIR)/$(FORMULA_ATOM).hpp $(INC_DIR)/$(FORMULA_CONN).hpp $(INC_DIR)/$(FORMULA_QUAN).hpp
	g++ $(CPPFLAGS) -c $< -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(PROOF_MANAGER).o: $(SRC_DIR)/$(PROOF_MANAGER).cpp $(INC_DIR)/$(PROOF_MANAGER).hpp
	g++ $(CPPFLAGS) -c $< -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(PROVER).o: $(SRC_DIR)/$(PROVER).cpp $(INC_DIR)/$(PROVER).hpp $(INC_DIR)/$(PROOF_MANAGER).hpp
	g++ $(CPPFLAGS) -c $< -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(LEXER).o: $(SRC_DIR)/generated/$(LEXER).c $(SRC_DIR)/generated/$(PARSER).hpp
	g++ $(CPPFLAGS) -c $< -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(PARSER).o: $(SRC_DIR)/generated/$(PARSER).cpp
	g++ $(CPPFLAGS) -c $< -o $@ -I$(INC_DIR)

$(SRC_DIR)/generated/$(LEXER).c: $(SRC_DIR)/parser/lexer.lpp | generated_dir
	flex -o $@ $<

$(SRC_DIR)/generated/$(PARSER).cpp $(SRC_DIR)/generated/$(PARSER).hpp: $(SRC_DIR)/parser/parser.ypp | generated_dir
	bison -d $< -o $(SRC_DIR)/generated/$(PARSER).cpp

generated_dir:
	mkdir -p src/generated

.PHONY: clean

clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/$(EXECUTABLE) $(SRC_DIR)/generated/*

