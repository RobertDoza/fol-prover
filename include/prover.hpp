#pragma once

#include <optional>

#include "formula.hpp"
#include "goal.hpp"

constexpr const char* commands =
	"Commands:\n"
	"apply - apply a rule of natural deduction on current goal\n"
	"help - receive this help message\n"
	"list - list available natural deduction rules\n"
	"exit - stop the program";

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
	"rule exE";

enum class Rule {
	Assumption,
	NotI,
	NotE,
	ConjI,
	ConjE,
	DisjI1,
	DisjI2,
	DisjE,
	ImpI,
	ImpE,
	IffI,
	IffE,
	AllI,
	AllE,
	ExI,
	ExE,
	Done
};

enum class CommandType {
	Empty,
	ListRequest,
	HelpRequest,
	ExitRequest,
	RuleApplication,
	UnknownCommand
};

struct Command {
	CommandType type;
	std::optional<Rule> rule_to_apply;
};

class Prover {
	public:
		Prover(const std::shared_ptr<Formula>& f)
			:_formula_to_prove(f), _goal_keeper(f)
		{}
		
		void start();
	private:
		void interact_with_user();
		void print_intro_message();
		Command parse_user_input(const std::string& user_input);
		void execute(const Command& command);
	private:
		std::shared_ptr<Formula> _formula_to_prove;
		GoalKeeper _goal_keeper;
};

