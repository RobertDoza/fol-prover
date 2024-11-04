#pragma once

#include <optional>

#include "formula.hpp"
#include "goal.hpp"
#include "proof_state_manager.hpp"

constexpr const char* commands =
	"Commands:\n"
	"* apply - apply a natural deduction rule on current goal (for the list of available rules, see 'list')\n"
	"* shift - rotate the assumptions of current goal (one position to the left)\n"
	"* help - receive this help message\n"
	"* list - show list of natural deduction rules\n"
	"* exit - stop the program";

constexpr const char* list_of_rules =
	"1) Assumption:\n"
	"apply assumption\n"
	"2) Introduction rules:\n"
	"apply rule notI\n"
	"apply rule conjI\n"
	"apply rule disjI1\n"
	"apply rule disjI2\n"
	"apply rule impI\n"
	"apply rule iffI\n"
	"apply rule allI\n"
	"apply rule exI\n"
	"3) Elimination rules:\n"
	"apply erule notE\n"
	"apply erule conjE\n"
	"apply erule disjE\n"
	"apply erule impE\n"
	"apply erule iffE\n"
	"apply erule allE\n"
	"apply erule exE";

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
	Ccontr,
	Classical
};

enum class CommandType {
	Empty,
	ListRequest,
	HelpRequest,
	ExitRequest,
	RuleApplication,
	Done,
	Shift,
	UnknownCommand
};

struct Command {
	CommandType type;
	std::optional<Rule> rule_to_apply;
};

enum class ExecuteStatus {
	Continue,
	StopSuccess,
	StopFailure
};

class Prover {
	public:
		Prover(const std::shared_ptr<Formula>& f)
			:_formula_to_prove(f), _proof_state_manager(f)
		{}
		
		void start();
	private:
		void interact_with_user();
		void print_intro_message();
		Command parse_user_input(const std::string& user_input);
		ExecuteStatus execute(const Command& command);
		ManagerStatus apply_rule(const Rule& rule);
	private:
		std::shared_ptr<Formula> _formula_to_prove;
		ProofStateManager _proof_state_manager;
};

