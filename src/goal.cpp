#include <algorithm>

#include "goal.hpp"
#include "atom.hpp"
#include "connective.hpp"
#include "quantifier.hpp"

std::string Goal::to_string() const {
	if (_solved) {
		return "<solved goal>";
	}
	
	std::string body = body_to_string();
	
	if (_meta_variables.empty()) {
		return body;
	}

	std::stringstream s;
	
	s << "∧ ";
	
	for (auto it = _meta_variables.begin(); it != _meta_variables.end(); it++) {
		s << *it;
		if (std::next(it) != _meta_variables.end()) {
			s << " ";
		}
	}
	
	s << ". ";
	s << body;
	
	return s.str();
}

std::string Goal::body_to_string() const {
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

std::set<std::string> Goal::get_free_vars_in_assumptions() const {
	std::set<std::string> free_vars = {};
	
	for (const auto& assumption : _assumptions) {
		auto free_vars_assumption = assumption->get_free_variable_names();
		free_vars.insert(free_vars_assumption.begin(), free_vars_assumption.end());
	}
	
	return free_vars;
}

std::set<std::string> Goal::get_free_vars_in_target_formula() const {
	return _target_formula->get_free_variable_names();
}

std::set<std::string> Goal::get_free_variables() const {
	auto free_vars = get_free_vars_in_assumptions();
	auto free_vars_target = get_free_vars_in_target_formula();
	
	free_vars.insert(free_vars_target.begin(), free_vars_target.end());
	
	return free_vars;
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
	if (_target_formula->type() != FormulaType::ForAll) {
		return RuleStatus::Failure;
	}
	
	auto target_forall_formula = std::dynamic_pointer_cast<ForAll>(_target_formula);
	
	std::set<std::string> used_variables = _meta_variables;
	std::set<std::string> free_variables = get_free_variables();
	used_variables.insert(free_variables.begin(), free_variables.end());
	
	std::string old_variable_name = target_forall_formula->get_variable_name();
	std::string new_variable_name = Formula::generate_new_variable_name(old_variable_name, used_variables);
	
	auto subformula = target_forall_formula->get_subformula();
	
	auto new_target = subformula->rename_var(old_variable_name, new_variable_name);
	
	set_target(new_target);
	
	_meta_variables.insert(new_variable_name);
	
	return RuleStatus::Success;
}

RuleStatus Goal::apply_erule_all_e(const std::shared_ptr<Term>& replacement_term) {
	for (size_t i = 0; i < _assumptions.size(); i++) {
		if (_assumptions[i]->type() == FormulaType::ForAll) {
			auto forall_formula = std::dynamic_pointer_cast<ForAll>(_assumptions[i]);
			
			auto quantified_variable = forall_formula->get_variable_name();
			auto subformula = forall_formula->get_subformula();
			
			auto new_assumption = subformula->replace(quantified_variable, replacement_term);
			
			remove_assumption(i);
			add_assumption(new_assumption);
			
			return RuleStatus::Success;
		}
	}
	
	return RuleStatus::Failure;
}

RuleStatus Goal::apply_rule_ex_i(const std::shared_ptr<Term>& replacement_term) {
	if (_target_formula->type() != FormulaType::Exists) {
		return RuleStatus::Failure;
	}
	
	auto target_exists_formula = std::dynamic_pointer_cast<Exists>(_target_formula);
	
	auto quantified_variable = target_exists_formula->get_variable_name();
	auto subformula = target_exists_formula->get_subformula();
	
	auto new_target = subformula->replace(quantified_variable, replacement_term);
	
	set_target(new_target);
	
	return RuleStatus::Success;
}

RuleStatus Goal::apply_erule_ex_e() {
	for (size_t i = 0; i < _assumptions.size(); i++) {
		if (_assumptions[i]->type() == FormulaType::Exists) {
			auto exists_formula = std::dynamic_pointer_cast<Exists>(_assumptions[i]);
			
			std::set<std::string> used_variables = _meta_variables;
			std::set<std::string> free_variables = get_free_variables();
			used_variables.insert(free_variables.begin(), free_variables.end());
			
			std::string old_variable_name = exists_formula->get_variable_name();
			std::string new_variable_name = Formula::generate_new_variable_name(old_variable_name, used_variables);
			
			auto subformula = exists_formula->get_subformula();
			
			auto new_assumption = subformula->rename_var(old_variable_name, new_variable_name);
			
			remove_assumption(i);
			add_assumption(new_assumption);
			
			_meta_variables.insert(new_variable_name);
			
			return RuleStatus::Success;
		}
	}
	
	return RuleStatus::Failure;
}

RuleStatus Goal::apply_rule_ccontr() {
	// TODO: implement me
	return RuleStatus::Failure;
}

RuleStatus Goal::apply_rule_classical() {
	// TODO: implement me
	return RuleStatus::Failure;
}

void Goal::shift_assumptions(unsigned n) {
	if (n > 0 && !_assumptions.empty()) {
		n %= _assumptions.size();
		std::rotate(_assumptions.begin(), _assumptions.begin() + n, _assumptions.end());
	}
}

