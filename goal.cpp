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

void Goal::add_assumption(const std::shared_ptr<Formula>& formula) {
	for (const auto& assumption : _assumptions) {
		if (are_equal(assumption, formula)) {
			return;
		}
	}

	_assumptions.push_back(formula);
}

void Goal::apply_assumption() {
	for (const auto& assumption : _assumptions) {
		if (are_equal(assumption, _target_formula)) {
			_solved = true;
		}
	}
	
	// TODO: handle failure
}

#include <iostream> // TODO: remove me

void Goal::apply_rule_imp_i() {
	if (_target_formula->type() != FormulaType::Implication) {
		std::cerr << "!!!\n"; // TODO: handle failure
	}
	
	auto target_implication = std::dynamic_pointer_cast<Implication>(_target_formula);
	
	auto left = target_implication->get_left_subformula();
	auto right = target_implication->get_right_subformula();
	
	_target_formula = right;
	
	add_assumption(left);
}

void Goal::apply_rule_conj_i() {
	if (_target_formula->type() != FormulaType::Conjunction) {
		std::cerr << "!!!\n"; // TODO: handle failure
	}
	
	auto target_conjunction = std::dynamic_pointer_cast<Conjunction>(_target_formula);
	
	auto left = target_conjunction->get_left_subformula();
	auto right = target_conjunction->get_right_subformula();
	
	Goal new_goal_1 = *this;
	Goal new_goal_2 = *this;
	
	new_goal_1._target_formula = left;
	new_goal_2._target_formula = right;
	
	std::cout << new_goal_1.to_string() << std::endl;
	std::cout << new_goal_2.to_string() << std::endl;
}

