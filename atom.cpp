#include "atom.hpp"

std::set<std::string> AtomicFormula::get_free_variable_names() const {
	return get_variable_names();
}

bool AtomicFormula::requires_parentheses() const {
	return false;
}

std::set<std::string> LogicalConstant::get_variable_names() const {
	return {};
}

std::string True::to_string() const {
	return "⊤ ";
}

FormulaType True::type() const {
	return FormulaType::True;
}

bool True::operator==(const True& other) const {
	(void) other;
	return true;
}

std::shared_ptr<Formula> True::rename_var(const std::string& old_name, const std::string& new_name) const {
	(void) old_name;
	(void) new_name;
	return std::make_shared<True>(*this);
}

std::string False::to_string() const {
	return "⊥ ";
}

FormulaType False::type() const {
	return FormulaType::False;
}

bool False::operator==(const False& other) const {
	(void) other;
	return true;
}

std::shared_ptr<Formula> False::rename_var(const std::string& old_name, const std::string& new_name) const {
	(void) old_name;
	(void) new_name;
	return std::make_shared<False>(*this);
}

std::string SimpleAtom::to_string() const {
	return _predicate_symbol;
}

FormulaType SimpleAtom::type() const {
	return FormulaType::SimpleAtom;
}

bool SimpleAtom::operator==(const SimpleAtom& other) const {
	return this->_predicate_symbol == other._predicate_symbol;
}

std::set<std::string> SimpleAtom::get_variable_names() const {
	return {};
}

std::shared_ptr<Formula> SimpleAtom::rename_var(const std::string& old_name, const std::string& new_name) const {
	(void) old_name;
	(void) new_name;
	return std::make_shared<SimpleAtom>(*this);
}

std::string ComplexAtom::to_string() const {
	std::stringstream s;
	
	s << _predicate_symbol;
	
	s << "(";
	
	for (size_t i = 0; i < _terms.size(); i++) {
		s << _terms[i]->to_string();
		if (i < _terms.size() - 1) {
			s << ", ";
		}
	}
	
	s << ")";
	
	return s.str();
}

bool ComplexAtom::operator==(const ComplexAtom& other) const {
	if (this->_predicate_symbol != other._predicate_symbol) {
		return false;
	}
	
	if (this->_terms.size() != other._terms.size()) {
		return false;
	}
	
	for (size_t i = 0; i < this->_terms.size(); ++i) {
		if (!are_equal(this->_terms[i], other._terms[i])) {
			return false;
		}
	}
	
	return true;
}

FormulaType ComplexAtom::type() const {
	return FormulaType::ComplexAtom;
}

std::set<std::string> ComplexAtom::get_variable_names() const {
	std::set<std::string> variable_names = {};

	for (const auto& t : _terms) {
		auto sub_vars = t->get_variable_names();
		variable_names.insert(sub_vars.begin(), sub_vars.end());
	}
	
	return variable_names;
}

std::shared_ptr<Formula> ComplexAtom::rename_var(const std::string& old_name, const std::string& new_name) const {
	std::vector<std::shared_ptr<Term>> new_terms = {};
	
	for (const auto& t : _terms) {
		new_terms.push_back(t->rename_var(old_name, new_name));
	}
	
	return std::make_shared<ComplexAtom>(_predicate_symbol, new_terms);
}

