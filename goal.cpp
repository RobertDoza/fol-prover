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

void Goal::set_target(const std::shared_ptr<Formula>& formula) {
	_target_formula = formula;
}

void Goal::add_assumption(const std::shared_ptr<Formula>& formula) {
	for (const auto& assumption : _assumptions) {
		if (are_equal(assumption, formula)) {
			return;
		}
	}

	_assumptions.push_back(formula);
}

RuleStatus Goal::apply_assumption() {
	for (const auto& assumption : _assumptions) {
		if (are_equal(assumption, _target_formula)) {
			_solved = true;
			return RuleStatus::Success;
		}
	}
	
	return RuleStatus::Failure;
}

RuleStatus Goal::apply_rule_imp_i() {
	if (_target_formula->type() != FormulaType::Implication) {
		return RuleStatus::Failure;
	}
	
	auto target_implication = std::dynamic_pointer_cast<Implication>(_target_formula);
	
	auto left = target_implication->get_left_subformula();
	auto right = target_implication->get_right_subformula();
	
	_target_formula = right;
	
	add_assumption(left);
	
	return RuleStatus::Success;
}

ConjIResult Goal::apply_rule_conj_i() {
	if (_target_formula->type() != FormulaType::Conjunction) {
		return {RuleStatus::Failure, NULL, NULL};
	}
	
	auto target_conjunction = std::dynamic_pointer_cast<Conjunction>(_target_formula);
	
	auto left = target_conjunction->get_left_subformula();
	auto right = target_conjunction->get_right_subformula();
	
	return {RuleStatus::Success, left, right};
}

std::string GoalKeeper::to_string() const {
	if (_goals.empty()) {
		return "No goals!";
	}

	std::stringstream s;
	
	auto size = _goals.size();
	
	s << "Goals to prove:" << size << "\n";
	
	for (size_t i = 0; i < size; i++) {
		s << (i + 1) << ". " << _goals[i].to_string() << "\n";
	}
	
	return s.str();
}

