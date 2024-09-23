#pragma once

#include "formula.hpp"
#include "goal.hpp"

constexpr const char* commands =
	"Commands:\n"
	"apply - apply a rule of natural deduction on current goal\n"
	"help - receive this help message\n"
	"list - list available natural deduction rules\n"
	"exit - stop the program\n";

constexpr const char* list_of_rules =
	"assumption\n"
	"Introduction rules:\n"
	"rule notI\n"
	"rule conjI\n"
	"rule disjI1\n"
	"rule disjI2\n"
	"rule impI\n"
	"rule iffI\n"
	"rule allI\n"
	"rule exI\n"
	"Elimination rules:\n"
	"rule notE\n"
	"rule conjE\n"
	"rule disjE\n"
	"rule impE\n"
	"rule iffE\n"
	"rule allE\n"
	"rule exE\n";

class Prover {
	public:
		Prover(const std::shared_ptr<Formula>& f)
			:_formula_to_prove(f), _goal_keeper(f)
		{}
		
		void start();
	private:
		void interact_with_user();
	private:
		std::shared_ptr<Formula> _formula_to_prove;
		GoalKeeper _goal_keeper;
};

