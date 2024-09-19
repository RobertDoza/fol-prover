#pragma once

#include <deque>

#include "formula.hpp"

enum class RuleStatus {
	Success,
	Failure
};

struct ConjIResult {
	RuleStatus status;
	std::shared_ptr<Formula> new_target_1;
	std::shared_ptr<Formula> new_target_2;
};

struct DisjEResult {
	RuleStatus status;
	std::shared_ptr<Formula> new_assumption_1;
	std::shared_ptr<Formula> new_assumption_2;
};

class Goal {
	public:
		Goal(const std::vector<std::shared_ptr<Formula>>& a, const std::shared_ptr<Formula>& f)
			:_assumptions(a), _target_formula(f), _solved(false)
		{}		
		
		std::string to_string() const;
		void set_target(const std::shared_ptr<Formula>& formula);
		RuleStatus apply_assumption();
		RuleStatus apply_rule_imp_i();
		ConjIResult apply_rule_conj_i();
		ConjIResult apply_erule_disj_e();
	private:
		void add_assumption(const std::shared_ptr<Formula>& formula);
	private:
		std::vector<std::shared_ptr<Formula>> _assumptions;
		std::shared_ptr<Formula> _target_formula;
		bool _solved;
};

class GoalKeeper {
	public:
		GoalKeeper(const Goal& initial_goal)
			:_goals({initial_goal})
		{}
		
		std::string to_string() const;
		
		// TODO: implement
		void apply_assumption();
		void apply_rule_not_i();
		void apply_erule_not_e();
		void apply_rule_conj_i();
		void apply_erule_conj_e();
		void apply_rule_disj_i_1();
		void apply_rule_disj_i_2();
		void apply_erule_disj_e();
		void apply_rule_imp_i();
		void apply_erule_imp_e();
		void apply_rule_iff_i();
		void apply_erule_iff_e();
	private:
		std::deque<Goal> _goals;
};

