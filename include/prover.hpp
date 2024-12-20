#pragma once

#include "formula.hpp"
#include "goal.hpp"
#include "proof_state_manager.hpp"
#include "command.hpp"

constexpr const char* commands =
	"Commands:\n"
	"* apply - apply a natural deduction rule on current goal (for the list of available rules, see 'list')\n"
	"* shift - rotate the assumptions of current goal (one position to the left)\n"
	"* help - display this help message\n"
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
	"apply erule exE\n"
	"4) Rules of classical logic:\n"
	"apply rule ccontr\n"
	"apply rule classical";

enum class ExecuteStatus {
	Continue,
	StopSuccess,
	StopFailure
};

class Prover {
	public:
		static void start_interactive_proof(const std::shared_ptr<Formula>&);
	private:
		Prover(const std::shared_ptr<Formula>&);
		void start();
		void print_intro_message();
		ExecuteStatus execute(const Command&);
		ManagerStatus apply_rule(const Rule&);
		std::shared_ptr<Term> get_term_from_user();
	private:
		std::shared_ptr<Formula> _formula_to_prove;
		ProofStateManager _proof_state_manager;
};

