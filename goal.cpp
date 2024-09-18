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
	
	// TODO: handle failure
}

#include <iostream> // TODO: remove me

void Goal::applyRuleImpI() {
	if (_target_formula->type() != FormulaType::Implication) {
		std::cerr << "!!!\n"; // TODO: handle failure
	}
	
	auto target_implication = std::dynamic_pointer_cast<Implication>(_target_formula);
	
	auto left = target_implication->get_left_subformula();
	auto right = target_implication->get_right_subformula();
	
	_target_formula = right;
	
	addAssumption(left);
}

