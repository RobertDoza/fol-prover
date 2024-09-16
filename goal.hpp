#pragma once

#include "formula.hpp"

class Goal {
	public:
		Goal(const std::vector<std::shared_ptr<Formula>>& a, const std::shared_ptr<Formula>& g)
			:_assumptions(a), _goal(g)
		{}
		
		std::string to_string() const;
	private:
		std::vector<std::shared_ptr<Formula>> _assumptions;
		std::shared_ptr<Formula> _goal;
};

