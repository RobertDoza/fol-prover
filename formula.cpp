#include "formula.hpp"

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

bool are_equal(const std::shared_ptr<Term>& t1, const std::shared_ptr<Term>& t2) {
	TermType type = t1->type();

	if (type != t2->type()) {
		return false;
	}
	
	switch (type) {
		case TermType::Variable: {
			auto v1 = std::dynamic_pointer_cast<Variable>(t1);
			auto v2 = std::dynamic_pointer_cast<Variable>(t2);
			return *v1 == *v2;
		}
		case TermType::Constant: {
			auto c1 = std::dynamic_pointer_cast<Constant>(t1);
			auto c2 = std::dynamic_pointer_cast<Constant>(t2);
			return *c1 == *c2;
		}
		case TermType::ComplexTerm: {
			auto ct1 = std::dynamic_pointer_cast<ComplexTerm>(t1);
			auto ct2 = std::dynamic_pointer_cast<ComplexTerm>(t2);
			return *ct1 == *ct2;
		}
	}

	return false;
}

std::ostream& operator<<(std::ostream& out, const Formula& formula) {
	out << formula.to_string();
	return out;
}

std::ostream& operator<<(std::ostream& out, const Term& term) {
	out << term.to_string();
	return out;
}

std::string Variable::to_string() const {
	return _name;
}

TermType Variable::type() const {
	return TermType::Variable;
}

bool Variable::operator==(const Variable& other) const {
	return this->_name == other._name;
}

std::string Constant::to_string() const {
	return _name;
}

TermType Constant::type() const {
	return TermType::Constant;
}

bool Constant::operator==(const Constant& other) const {
	return this->_name == other._name;
}

std::string ComplexTerm::to_string() const {
	std::stringstream s;
	
	s << _function_symbol;
	
	s << "(";
	
	for (size_t i = 0; i < _subterms.size(); i++) {
		s << _subterms[i]->to_string();
		if (i < _subterms.size() - 1) {
			s << ", ";
		}
	}
	
	s << ")";
	
	return s.str();
}

TermType ComplexTerm::type() const {
	return TermType::ComplexTerm;
}

bool ComplexTerm::operator==(const ComplexTerm& other) const {
	if (this->_function_symbol != other._function_symbol) {
		return false;
	}
	
	if (this->_subterms.size() != other._subterms.size()) {
		return false;
	}
	
	for (size_t i = 0; i < this->_subterms.size(); ++i) {
		if (!are_equal(this->_subterms[i], other._subterms[i])) {
			return false;
		}
	}
	
	return true;
}

bool AtomicFormula::requires_parentheses() const {
	return false;
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

std::string SimpleAtom::to_string() const {
	return _predicate_symbol;
}

FormulaType SimpleAtom::type() const {
	return FormulaType::SimpleAtom;
}

bool SimpleAtom::operator==(const SimpleAtom& other) const {
	return this->_predicate_symbol == other._predicate_symbol;
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

std::string Negation::symbol() const {
	return "¬";
}

FormulaType Negation::type() const {
	return FormulaType::Negation;
}

bool Negation::operator==(const Negation& other) const {
	return are_equal(this->_subformula, other._subformula);
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

std::string Disjunction::symbol() const {
	return "∨";
}

FormulaType Disjunction::type() const {
	return FormulaType::Disjunction;
}

bool Disjunction::operator==(const Disjunction& other) const {
	return are_equal(this->_left_subformula, other._left_subformula) and are_equal(this->_right_subformula, other._right_subformula);
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

std::string Equivalence::symbol() const {
	return "↔";
}

FormulaType Equivalence::type() const {
	return FormulaType::Equivalence;
}

bool Equivalence::operator==(const Equivalence& other) const {
	return are_equal(this->_left_subformula, other._left_subformula) and are_equal(this->_right_subformula, other._right_subformula);
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

std::string Exists::symbol() const {
	return "∃ ";
}

FormulaType Exists::type() const {
	return FormulaType::Exists;
}

bool Exists::operator==(const Exists& other) const {
	return this->_variable_name == other._variable_name and are_equal(this->_subformula, other._subformula);
}

