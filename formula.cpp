#include "formula.hpp"
#include "atom.hpp"

bool are_equal(const std::shared_ptr<Formula>& f1, const std::shared_ptr<Formula>& f2) {
	FormulaType type = f1->type();

	if (type != f2->type()) {
		return false;
	}
	
	switch (type) {
		case FormulaType::True: {
			auto t1 = std::dynamic_pointer_cast<True>(f1);
			auto t2 = std::dynamic_pointer_cast<True>(f2);
			return *t1 == *t2;
		}
		case FormulaType::False: {
			auto x1 = std::dynamic_pointer_cast<False>(f1);
			auto x2 = std::dynamic_pointer_cast<False>(f2);
			return *x1 == *x2;
		}
		case FormulaType::SimpleAtom: {
			auto s1 = std::dynamic_pointer_cast<SimpleAtom>(f1);
			auto s2 = std::dynamic_pointer_cast<SimpleAtom>(f2);
			return *s1 == *s2;
		}
		case FormulaType::ComplexAtom: {
			auto c1 = std::dynamic_pointer_cast<ComplexAtom>(f1);
			auto c2 = std::dynamic_pointer_cast<ComplexAtom>(f2);
			return *c1 == *c2;
		}
		case FormulaType::Negation: {
			auto n1 = std::dynamic_pointer_cast<Negation>(f1);
			auto n2 = std::dynamic_pointer_cast<Negation>(f2);
			return *n1 == *n2;
		}
		case FormulaType::Conjunction: {
			auto c1 = std::dynamic_pointer_cast<Conjunction>(f1);
			auto c2 = std::dynamic_pointer_cast<Conjunction>(f2);
			return *c1 == *c2;
		}
		case FormulaType::Disjunction: {
			auto d1 = std::dynamic_pointer_cast<Disjunction>(f1);
			auto d2 = std::dynamic_pointer_cast<Disjunction>(f2);
			return *d1 == *d2;
		}
		case FormulaType::Implication: {
			auto i1 = std::dynamic_pointer_cast<Implication>(f1);
			auto i2 = std::dynamic_pointer_cast<Implication>(f2);
			return *i1 == *i2;
		}
		case FormulaType::Equivalence: {
			auto e1 = std::dynamic_pointer_cast<Equivalence>(f1);
			auto e2 = std::dynamic_pointer_cast<Equivalence>(f2);
			return *e1 == *e2;
		}
		case FormulaType::ForAll: {
			auto fa1 = std::dynamic_pointer_cast<ForAll>(f1);
			auto fa2 = std::dynamic_pointer_cast<ForAll>(f2);
			return *fa1 == *fa2;
		}
		case FormulaType::Exists: {
			auto ex1 = std::dynamic_pointer_cast<Exists>(f1);
			auto ex2 = std::dynamic_pointer_cast<Exists>(f2);
			return *ex1 == *ex2;
		}
	}

	return false;
}

std::ostream& operator<<(std::ostream& out, const Formula& formula) {
	out << formula.to_string();
	return out;
}

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

std::string Quantifier::to_string() const {
	std::string sub;

	if (_subformula->requires_parentheses()) {
		sub = "(" + _subformula->to_string() + ")";
	} else {
		sub = _subformula->to_string();
	}
	
	return symbol() + _variable_name + ". " + sub;
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

std::shared_ptr<Formula> ForAll::rename_var(const std::string& old_name, const std::string& new_name) const {
	if (_variable_name == old_name or _variable_name == new_name) {
		return std::make_shared<ForAll>(*this);
	}
	
	return std::make_shared<ForAll>(_variable_name, _subformula->rename_var(old_name, new_name));
}

void ForAll::alpha_convert(const std::string& new_var_name) {
	// TODO: implement properly
	_variable_name = new_var_name;
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

std::shared_ptr<Formula> Exists::rename_var(const std::string& old_name, const std::string& new_name) const {
	if (_variable_name == old_name or _variable_name == new_name) {
		return std::make_shared<Exists>(*this);
	}
	
	return std::make_shared<Exists>(_variable_name, _subformula->rename_var(old_name, new_name));
}

void Exists::alpha_convert(const std::string& new_var_name) {
	// TODO: implement properly
	_variable_name = new_var_name;
}

