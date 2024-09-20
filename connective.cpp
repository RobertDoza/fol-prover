#include "connective.hpp"

bool LogicalConnective::requires_parentheses() const {
	return true;
}

std::string UnaryConnective::to_string() const {
	if (_subformula->requires_parentheses()) {
		return symbol() + " (" + _subformula->to_string() + ")";
	} else {
		return symbol() + " " + _subformula->to_string();
	}
}

std::shared_ptr<Formula> UnaryConnective::get_subformula() const {
	return _subformula;
}

std::set<std::string> UnaryConnective::get_variable_names() const {
	return _subformula->get_variable_names();
}

std::set<std::string> UnaryConnective::get_free_variable_names() const {
	return _subformula->get_free_variable_names();
}

std::string BinaryConnective::to_string() const {
	std::string left;
	std::string right;
	
	if (_left_subformula->requires_parentheses()) {
		left = "(" + _left_subformula->to_string() + ")";
	} else {
		left = _left_subformula->to_string();
	}
	
	if (_right_subformula->requires_parentheses()) {
		right = "(" + _right_subformula->to_string() + ")";
	} else {
		right = _right_subformula->to_string();
	}

	return left + " " + symbol() + " " + right;
}

std::shared_ptr<Formula> BinaryConnective::get_left_subformula() const {
	return _left_subformula;
}

std::shared_ptr<Formula> BinaryConnective::get_right_subformula() const {
	return _right_subformula;
}

std::set<std::string> BinaryConnective::get_variable_names() const {
	auto vars_left = _left_subformula->get_variable_names();
	auto vars_right = _right_subformula->get_variable_names();
	
	vars_left.insert(vars_right.begin(), vars_right.end());
	
	return vars_left;
}

std::set<std::string> BinaryConnective::get_free_variable_names() const {
	auto free_vars_left = _left_subformula->get_free_variable_names();
	auto free_vars_right = _right_subformula->get_free_variable_names();
	
	free_vars_left.insert(free_vars_right.begin(), free_vars_right.end());
	
	return free_vars_left;
}

std::string Negation::symbol() const {
	return "¬";
}

FormulaType Negation::type() const {
	return FormulaType::Negation;
}

bool Negation::operator==(const Negation& other) const {
	return are_equal(this->_subformula, other._subformula);
}

std::shared_ptr<Formula> Negation::rename_var(const std::string& old_name, const std::string& new_name) const {
	return std::make_shared<Negation>(_subformula->rename_var(old_name, new_name));
}

std::string Conjunction::symbol() const {
	return "∧";
}

FormulaType Conjunction::type() const {
	return FormulaType::Conjunction;
}

bool Conjunction::operator==(const Conjunction& other) const {
	return are_equal(this->_left_subformula, other._left_subformula) and are_equal(this->_right_subformula, other._right_subformula);
}

std::shared_ptr<Formula> Conjunction::rename_var(const std::string& old_name, const std::string& new_name) const {
	return std::make_shared<Conjunction>(_left_subformula->rename_var(old_name, new_name), _right_subformula->rename_var(old_name, new_name));
}

std::string Disjunction::symbol() const {
	return "∨";
}

FormulaType Disjunction::type() const {
	return FormulaType::Disjunction;
}

bool Disjunction::operator==(const Disjunction& other) const {
	return are_equal(this->_left_subformula, other._left_subformula) and are_equal(this->_right_subformula, other._right_subformula);
}

std::shared_ptr<Formula> Disjunction::rename_var(const std::string& old_name, const std::string& new_name) const {
	return std::make_shared<Disjunction>(_left_subformula->rename_var(old_name, new_name), _right_subformula->rename_var(old_name, new_name));
}

std::string Implication::symbol() const {
	return "→";
}

FormulaType Implication::type() const {
	return FormulaType::Implication;
}

bool Implication::operator==(const Implication& other) const {
	return are_equal(this->_left_subformula, other._left_subformula) and are_equal(this->_right_subformula, other._right_subformula);
}

std::shared_ptr<Formula> Implication::rename_var(const std::string& old_name, const std::string& new_name) const {
	return std::make_shared<Implication>(_left_subformula->rename_var(old_name, new_name), _right_subformula->rename_var(old_name, new_name));
}

std::string Equivalence::symbol() const {
	return "↔";
}

FormulaType Equivalence::type() const {
	return FormulaType::Equivalence;
}

bool Equivalence::operator==(const Equivalence& other) const {
	return are_equal(this->_left_subformula, other._left_subformula) and are_equal(this->_right_subformula, other._right_subformula);
}

std::shared_ptr<Formula> Equivalence::rename_var(const std::string& old_name, const std::string& new_name) const {
	return std::make_shared<Equivalence>(_left_subformula->rename_var(old_name, new_name), _right_subformula->rename_var(old_name, new_name));
}

