#include "goal.hpp"

std::string Goal::to_string() const {
	if (_solved) {
		return "<solved goal>";
	}

	std::stringstream s;
	
	s << "[";
	
	for (size_t i = 0; i < _assumptions.size(); i++) {
		s << *_assumptions[i];
		if (i < _assumptions.size() - 1) {
			s << ", ";
		}
	}
	
	s << "]";
	
	s << " ⊢  ";
	
	s << *_target_formula;
	
	return s.str();
}

void Goal::addAssumption(const std::shared_ptr<Formula>& formula) {
	for (const auto& assumption : _assumptions) {
		if (are_equal(assumption, formula)) {
			return;
		}
	}

	_assumptions.push_back(formula);
}

void Goal::applyAssumption() {
	for (const auto& assumption : _assumptions) {
		if (are_equal(assumption, _target_formula)) {
			_solved = true;
		}
	}
}

