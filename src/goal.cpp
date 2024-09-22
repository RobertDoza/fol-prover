#include "goal.hpp"
#include "atom.hpp"
#include "connective.hpp"

std::string Goal::to_string() const {
	if (_solved) {
		return "<solved goal>";
	}

	std::stringstream s;
	
	size_t num_assumptions = _assumptions.size();
	
	if (num_assumptions == 0) {
		return _target_formula->to_string();
	}
	
	if (num_assumptions == 1) {
		s << *_assumptions[0];
	} else {
		s << "[";
		for (size_t i = 0; i < num_assumptions; i++) {
			s << *_assumptions[i];
			if (i < num_assumptions - 1) {
				s << ", ";
			}
		}
		s << "]";
	}
	
	s << " ⊢  ";
	s << *_target_formula;
	
	return s.str();
}

void Goal::set_target(const std::shared_ptr<Formula>& formula) {
	_target_formula = formula;
}

void Goal::add_assumption(const std::shared_ptr<Formula>& formula) {
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

RuleStatus Goal::apply_rule_not_i() {
	if (_target_formula->type() != FormulaType::Negation) {
		return RuleStatus::Failure;
	}
	
	auto target_negation = std::dynamic_pointer_cast<Negation>(_target_formula);
	
	auto subformula = target_negation->get_subformula();
	
	_target_formula = std::make_shared<False>();
	
	add_assumption(subformula);
	
	return RuleStatus::Success;
}

RuleStatus Goal::apply_erule_not_e() {
	for (size_t i = 0; i < _assumptions.size(); i++) {
		if (_assumptions[i]->type() == FormulaType::Negation) {
			auto negation = std::dynamic_pointer_cast<Negation>(_assumptions[i]);
			
			auto subformula = negation->get_subformula();
			
			remove_assumption(i);
			
			set_target(subformula);
			
			return RuleStatus::Success;
		}
	}
	
	return RuleStatus::Failure;
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

RuleStatus Goal::apply_rule_disj_i_1() {
	if (_target_formula->type() != FormulaType::Disjunction) {
		return RuleStatus::Failure;
	}
	
	auto target_disjunction = std::dynamic_pointer_cast<Disjunction>(_target_formula);
	
	_target_formula = target_disjunction->get_left_subformula();
	
	return RuleStatus::Success;
}

RuleStatus Goal::apply_rule_disj_i_2() {
	if (_target_formula->type() != FormulaType::Disjunction) {
		return RuleStatus::Failure;
	}
	
	auto target_disjunction = std::dynamic_pointer_cast<Disjunction>(_target_formula);
	
	_target_formula = target_disjunction->get_right_subformula();
	
	return RuleStatus::Success;
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

ImpEResult Goal::apply_erule_imp_e() {
	for (size_t i = 0; i < _assumptions.size(); i++) {
		if (_assumptions[i]->type() == FormulaType::Implication) {
			auto implication = std::dynamic_pointer_cast<Implication>(_assumptions[i]);
			
			auto left = implication->get_left_subformula();
			auto right = implication->get_right_subformula();
			
			remove_assumption(i);
			
			return {RuleStatus::Success, left, right};
		}
	}
	
	return {RuleStatus::Failure, NULL, NULL};
}

IffIResult Goal::apply_rule_iff_i() {
	if (_target_formula->type() != FormulaType::Equivalence) {
		return {RuleStatus::Failure, NULL, NULL};
	}
	
	auto target_equivalence = std::dynamic_pointer_cast<Equivalence>(_target_formula);
	
	auto left = target_equivalence->get_left_subformula();
	auto right = target_equivalence->get_right_subformula();
	
	return {RuleStatus::Success, left, right};
}

RuleStatus Goal::apply_erule_iff_e() {
	for (size_t i = 0; i < _assumptions.size(); i++) {
		if (_assumptions[i]->type() == FormulaType::Equivalence) {
			auto equivalence = std::dynamic_pointer_cast<Equivalence>(_assumptions[i]);
			
			auto left = equivalence->get_left_subformula();
			auto right = equivalence->get_right_subformula();
			
			remove_assumption(i);
			
			auto left_to_right = std::make_shared<Implication>(left, right);
			auto right_to_left = std::make_shared<Implication>(right, left);
			
			add_assumption(left_to_right);
			add_assumption(right_to_left);
			
			return RuleStatus::Success;
		}
	}
	
	return RuleStatus::Failure;
}

RuleStatus Goal::apply_rule_all_i() {
	// TODO: implement
	return RuleStatus::Success;
}

RuleStatus Goal::apply_erule_all_e() {
	// TODO: implement
	return RuleStatus::Success;
}

RuleStatus Goal::apply_rule_ex_i() {
	// TODO: implement
	return RuleStatus::Success;
}

RuleStatus Goal::apply_erule_ex_e() {
	// TODO: implement
	return RuleStatus::Success;
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
		return;
	}
	
	_goals.pop_front();
}

void GoalKeeper::apply_rule_not_i() {
	// TODO: handle empty goal list

	RuleStatus status = _goals[0].apply_rule_not_i();
	
	if (status == RuleStatus::Failure) {
		// TODO: handle failure
	}
}

void GoalKeeper::apply_erule_not_e() {
	// TODO: handle empty goal list

	RuleStatus status = _goals[0].apply_erule_not_e();
	
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

void GoalKeeper::apply_rule_disj_i_1() {
	// TODO: handle empty goal list
	
	RuleStatus status = _goals[0].apply_rule_disj_i_1();
	
	if (status == RuleStatus::Failure) {
		// TODO: handle failure
	}
}

void GoalKeeper::apply_rule_disj_i_2() {
	// TODO: handle empty goal list
	
	RuleStatus status = _goals[0].apply_rule_disj_i_2();
	
	if (status == RuleStatus::Failure) {
		// TODO: handle failure
	}
}

void GoalKeeper::apply_erule_disj_e() {
	// TODO: handle empty goal list
	
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

void GoalKeeper::apply_rule_imp_i() {
	// TODO: handle empty goal list

	RuleStatus status = _goals[0].apply_rule_imp_i();
	
	if (status == RuleStatus::Failure) {
		// TODO: handle failure
	}
}

void GoalKeeper::apply_erule_imp_e() {
	// TODO: handle empty goal list
	
	ImpEResult result = _goals[0].apply_erule_imp_e();
	
	RuleStatus status = result.status;
	
	if (status == RuleStatus::Failure) {
		// TODO: handle failure
		return;
	}
	
	auto left_subformula = result.left_subformula;
	auto right_subformula = result.right_subformula;
	
	Goal new_goal_1 = _goals[0];
	Goal new_goal_2 = _goals[0];
	
	new_goal_1.set_target(left_subformula);
	
	new_goal_2.add_assumption(right_subformula);
	
	_goals.pop_front();
	
	_goals.push_front(new_goal_2);
	_goals.push_front(new_goal_1);
}

void GoalKeeper::apply_rule_iff_i() {
	// TODO: handle empty goal list
	
	IffIResult result = _goals[0].apply_rule_iff_i();
	
	RuleStatus status = result.status;
	
	if (status == RuleStatus::Failure) {
		// TODO: handle failure
		return;
	}
	
	auto left_subformula = result.left_subformula;
	auto right_subformula = result.right_subformula;
	
	Goal new_goal_1 = _goals[0];
	Goal new_goal_2 = _goals[0];
	
	new_goal_1.add_assumption(left_subformula);
	new_goal_1.set_target(right_subformula);
	
	new_goal_2.add_assumption(right_subformula);
	new_goal_2.set_target(left_subformula);
	
	_goals.pop_front();
	
	_goals.push_front(new_goal_2);
	_goals.push_front(new_goal_1);
}

void GoalKeeper::apply_erule_iff_e() {
	// TODO: handle empty goal list
	
	RuleStatus status = _goals[0].apply_erule_iff_e();
	
	if (status == RuleStatus::Failure) {
		// TODO: handle failure
	}
}
