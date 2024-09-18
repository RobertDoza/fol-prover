#include "formula.hpp"

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

std::string Constant::to_string() const {
	return _name;
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

bool AtomicFormula::requires_parentheses() const {
	return false;
}

std::string True::to_string() const {
	return "⊤ ";
}

std::string False::to_string() const {
	return "⊥ ";
}

std::string SimpleAtom::to_string() const {
	return _predicate_symbol;
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

std::string Negation::symbol() const {
	return "¬";
}

std::string Conjunction::symbol() const {
	return "∧";
}

std::string Disjunction::symbol() const {
	return "∨";
}

std::string Implication::symbol() const {
	return "→";
}

std::string Equivalence::symbol() const {
	return "↔";
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

std::string Exists::symbol() const {
	return "∃ ";
}

