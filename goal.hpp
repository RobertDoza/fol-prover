#pragma once

#include "formula.hpp"

class Goal {
	public:
		std::string to_string() const;
	private:
		std::vector<std::shared_ptr<Formula>> _assumptions;
		std::shared_ptr<Formula> _goal;
};

