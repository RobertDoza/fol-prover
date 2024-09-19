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

void Goal::remove_assumption(unsigned index) {
	if (index < _assumptions.size()) {
		_assumptions.erase(_assumptions.begin() + index);
	} else {
		throw std::runtime_error("Index out of bounds!");
	}
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

RuleStatus Goal::apply_erule_conj_e() {
	for (size_t i = 0; i < _assumptions.size(); i++) {
		if (_assumptions[i]->type() == FormulaType::Conjunction) {
			auto conjunction = std::dynamic_pointer_cast<Conjunction>(_assumptions[i]);
			
			auto left = conjunction->get_left_subformula();
			auto right = conjunction->get_right_subformula();
			
			remove_assumption(i);
			
			add_assumption(left);
			add_assumption(right);
			
			return RuleStatus::Success;
		}
	}
	
	return RuleStatus::Failure;
}

DisjEResult Goal::apply_erule_disj_e() {
	for (size_t i = 0; i < _assumptions.size(); i++) {
		if (_assumptions[i]->type() == FormulaType::Disjunction) {
			auto disjunction = std::dynamic_pointer_cast<Disjunction>(_assumptions[i]);
			
			auto left = disjunction->get_left_subformula();
			auto right = disjunction->get_right_subformula();
			
			remove_assumption(i);
			
			return {RuleStatus::Success, left, right};
		}
	}
	
	return {RuleStatus::Failure, NULL, NULL};
}

std::string GoalKeeper::to_string() const {
	if (_goals.empty()) {
		return "No goals!";
	}

	std::stringstream s;
	
	auto size = _goals.size();
	
	s << "Goals to prove: " << size << "\n";
	
	for (size_t i = 0; i < size; i++) {
		s << (i + 1) << ". " << _goals[i].to_string();
		if (i < size - 1) {
			s << "\n";
		}
	}
	
	return s.str();
}

void GoalKeeper::apply_assumption() {
	// TODO: handle empty goal list

	RuleStatus status = _goals[0].apply_assumption();
	
	if (status == RuleStatus::Failure) {
		// TODO: handle failure
	}
}

void GoalKeeper::apply_rule_imp_i() {
	// TODO: handle empty goal list

	RuleStatus status = _goals[0].apply_rule_imp_i();
	
	if (status == RuleStatus::Failure) {
		// TODO: handle failure
	}
}

void GoalKeeper::apply_rule_conj_i() {
	ConjIResult result = _goals[0].apply_rule_conj_i();
	
	RuleStatus status = result.status;
	
	if (status == RuleStatus::Failure) {
		// TODO: handle failure
		return;
	}
	
	auto target_1 = result.new_target_1;
	auto target_2 = result.new_target_2;
	
	Goal new_goal_1 = _goals[0];
	Goal new_goal_2 = _goals[0];
	
	new_goal_1.set_target(target_1);
	new_goal_2.set_target(target_2);
	
	_goals.pop_front();
	
	_goals.push_front(new_goal_2);
	_goals.push_front(new_goal_1);
}

void GoalKeeper::apply_erule_conj_e() {
	// TODO: handle empty goal list

	RuleStatus status = _goals[0].apply_erule_conj_e();
	
	if (status == RuleStatus::Failure) {
		// TODO: handle failure
	}
}

void GoalKeeper::apply_erule_disj_e() {
	DisjEResult result = _goals[0].apply_erule_disj_e();
	
	RuleStatus status = result.status;
	
	if (status == RuleStatus::Failure) {
		// TODO: handle failure
		return;
	}
	
	auto disj_left = result.new_assumption_1;
	auto disj_right = result.new_assumption_2;
	
	Goal new_goal_1 = _goals[0];
	Goal new_goal_2 = _goals[0];
	
	new_goal_1.add_assumption(disj_left);
	new_goal_2.add_assumption(disj_right);
	
	_goals.pop_front();
	
	_goals.push_front(new_goal_2);
	_goals.push_front(new_goal_1);
}

