#include "quantifier.hpp"

std::string Quantifier::to_string() const {
	std::string sub;

	if (_subformula->requires_parentheses()) {
		sub = "(" + _subformula->to_string() + ")";
	} else {
		sub = _subformula->to_string();
	}
	
	return symbol() + _variable_name + ". " + sub;
}

std::string Quantifier::get_variable_name() const {
	return _variable_name;
}

std::shared_ptr<Formula> Quantifier::get_subformula() const {
	return _subformula;
}

std::set<std::string> Quantifier::get_variable_names() const {
	auto sub_vars = _subformula->get_variable_names();
	
	sub_vars.insert(_variable_name);
	
	return sub_vars;
}

std::set<std::string> Quantifier::get_free_variable_names() const {
	auto sub_vars = _subformula->get_free_variable_names();
	
	sub_vars.erase(_variable_name);
	
	return sub_vars;
}

bool Quantifier::requires_parentheses() const {
	return true;
}

std::string ForAll::symbol() const {
	return "∀ ";
}

FormulaType ForAll::type() const {
	return FormulaType::ForAll;
}

bool ForAll::operator==(const ForAll& other) const {
	return this->_variable_name == other._variable_name and are_equal(this->_subformula, other._subformula);
}

std::shared_ptr<Formula> ForAll::replace(const std::string& var_name, const std::shared_ptr<Term>& term) const {
	if (_variable_name == var_name) {
		return std::make_shared<ForAll>(*this);
	}
	
	auto term_variables = term->get_variable_names();
	
	if (term_variables.find(_variable_name) == term_variables.end()) {
		return std::make_shared<ForAll>(_variable_name, _subformula->replace(var_name, term));
	}
	
	auto used_variables = _subformula->get_variable_names();
	used_variables.insert(term_variables.begin(), term_variables.end());
	
	std::string new_variable_name = Formula::generate_new_variable_name(_variable_name, used_variables);
	
	auto alpha_converted = this->alpha_convert(new_variable_name);
	
	return alpha_converted->replace(var_name, term);
}

std::shared_ptr<Formula> ForAll::rename_var(const std::string& old_name, const std::string& new_name) const {
	if (_variable_name == old_name or _variable_name == new_name) {
		return std::make_shared<ForAll>(*this);
	}
	
	return std::make_shared<ForAll>(_variable_name, _subformula->rename_var(old_name, new_name));
}

std::shared_ptr<Quantifier> ForAll::alpha_convert() const {
	std::string old_var_name = _variable_name;
	std::string new_var_name;
	
	auto subformula_var_names = _subformula->get_variable_names();
	
	unsigned i = 1;
	while (true) {
		new_var_name = old_var_name + std::to_string(i);
		
		if (subformula_var_names.find(new_var_name) == subformula_var_names.end()) {
			break;
		}
		
		i++;
	}
	
	auto new_subformula = _subformula->rename_var(old_var_name, new_var_name);
	
	return std::make_shared<ForAll>(new_var_name, new_subformula);
}

std::shared_ptr<Quantifier> ForAll::alpha_convert(const std::string& new_var_name) const {
	std::string old_var_name = _variable_name;
	
	auto subformula_var_names = _subformula->get_variable_names();
	
	if (subformula_var_names.find(new_var_name) != subformula_var_names.end()) {
		throw std::runtime_error("Can't preform alpha conversion - variable in use!");
	}
	
	auto new_subformula = _subformula->rename_var(old_var_name, new_var_name);
	
	return std::make_shared<ForAll>(new_var_name, new_subformula);
}

std::string Exists::symbol() const {
	return "∃ ";
}

FormulaType Exists::type() const {
	return FormulaType::Exists;
}

bool Exists::operator==(const Exists& other) const {
	return this->_variable_name == other._variable_name and are_equal(this->_subformula, other._subformula);
}

std::shared_ptr<Formula> Exists::replace(const std::string& var_name, const std::shared_ptr<Term>& term) const {
	if (_variable_name == var_name) {
		return std::make_shared<Exists>(*this);
	}
	
	auto term_variables = term->get_variable_names();
	
	if (term_variables.find(_variable_name) == term_variables.end()) {
		return std::make_shared<Exists>(_variable_name, _subformula->replace(var_name, term));
	}
	
	auto used_variables = _subformula->get_variable_names();
	used_variables.insert(term_variables.begin(), term_variables.end());
	
	std::string new_variable_name = Formula::generate_new_variable_name(_variable_name, used_variables);
	
	auto alpha_converted = this->alpha_convert(new_variable_name);
	
	return alpha_converted->replace(var_name, term);
}

std::shared_ptr<Formula> Exists::rename_var(const std::string& old_name, const std::string& new_name) const {
	if (_variable_name == old_name or _variable_name == new_name) {
		return std::make_shared<Exists>(*this);
	}
	
	return std::make_shared<Exists>(_variable_name, _subformula->rename_var(old_name, new_name));
}

std::shared_ptr<Quantifier> Exists::alpha_convert() const {
	std::string old_var_name = _variable_name;
	std::string new_var_name;
	
	auto subformula_var_names = _subformula->get_variable_names();
	
	unsigned i = 1;
	while (true) {
		new_var_name = old_var_name + std::to_string(i);
		
		if (subformula_var_names.find(new_var_name) == subformula_var_names.end()) {
			break;
		}
		
		i++;
	}
	
	auto new_subformula = _subformula->rename_var(old_var_name, new_var_name);
	
	return std::make_shared<Exists>(new_var_name, new_subformula);
}

std::shared_ptr<Quantifier> Exists::alpha_convert(const std::string& new_var_name) const {
	std::string old_var_name = _variable_name;
	
	auto subformula_var_names = _subformula->get_variable_names();
	
	if (subformula_var_names.find(new_var_name) != subformula_var_names.end()) {
		throw std::runtime_error("Can't preform alpha conversion - variable in use!");
	}
	
	auto new_subformula = _subformula->rename_var(old_var_name, new_var_name);
	
	return std::make_shared<Exists>(new_var_name, new_subformula);
}

