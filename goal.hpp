#pragma once

#include "formula.hpp"

class Goal {
	public:
		Goal(const std::vector<std::shared_ptr<Formula>>& a, const std::shared_ptr<Formula>& f)
			:_assumptions(a), _target_formula(f), _solved(false)
		{}		
		
		std::string to_string() const;
		void apply_assumption();
		void apply_rule_imp_i();
	private:
		void add_assumption(const std::shared_ptr<Formula>& formula);
	private:
		std::vector<std::shared_ptr<Formula>> _assumptions;
		std::shared_ptr<Formula> _target_formula;
		bool _solved;
};

