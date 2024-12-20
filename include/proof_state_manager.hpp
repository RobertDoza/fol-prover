#pragma once

#include <string>
#include <memory>
#include <deque>

#include "formula.hpp"
#include "goal.hpp"

enum class ManagerStatusCode {
	Success,
	Failure,
	EmptyGoalList
};

struct ManagerStatus {
	ManagerStatusCode code;
	std::string message;
	
	ManagerStatus(const ManagerStatusCode& c, const std::string& m = "")
		:code(c), message(m)
	{}
};

class ProofStateManager {
	public:
		ProofStateManager(const std::shared_ptr<Formula>& formula_to_prove)
			:_goals({Goal(formula_to_prove)})
		{}
		
		ProofStateManager(const Goal& initial_goal)
			:_goals({initial_goal})
		{}
		
		std::string to_string() const;
		ManagerStatus apply_assumption();
		ManagerStatus apply_rule_not_i();
		ManagerStatus apply_erule_not_e();
		ManagerStatus apply_rule_conj_i();
		ManagerStatus apply_erule_conj_e();
		ManagerStatus apply_rule_disj_i_1();
		ManagerStatus apply_rule_disj_i_2();
		ManagerStatus apply_erule_disj_e();
		ManagerStatus apply_rule_imp_i();
		ManagerStatus apply_erule_imp_e();
		ManagerStatus apply_rule_iff_i();
		ManagerStatus apply_erule_iff_e();
		ManagerStatus apply_rule_all_i();
		ManagerStatus apply_erule_all_e(const std::shared_ptr<Term>& replacement_term);
		ManagerStatus apply_rule_ex_i(const std::shared_ptr<Term>& replacement_term);
		ManagerStatus apply_erule_ex_e();
		ManagerStatus apply_rule_ccontr();
		ManagerStatus apply_rule_classical();
		bool goals_solved() const;
		ManagerStatus shift();
	private:
		std::deque<Goal> _goals;
};

