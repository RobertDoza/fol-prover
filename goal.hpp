#pragma once

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
	private:
		void add_assumption(const std::shared_ptr<Formula>& formula);
	private:
		std::vector<std::shared_ptr<Formula>> _assumptions;
		std::shared_ptr<Formula> _target_formula;
		bool _solved;
};

class GoalKeeper {
	public:
		std::string to_string() const;
	private:
		std::vector<Goal> _goals;
};

