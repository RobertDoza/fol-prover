#pragma once

#include <string>
#include <memory>
#include <deque>

#include "formula.hpp"
#include "goal.hpp"

class GoalKeeper {
	public:
		GoalKeeper(const std::shared_ptr<Formula>& formula_to_prove)
			:_goals({Goal(formula_to_prove)})
		{}
		
		GoalKeeper(const Goal& initial_goal)
			:_goals({initial_goal})
		{}
		
		std::string to_string() const;
		
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

