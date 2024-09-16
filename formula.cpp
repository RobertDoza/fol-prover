#include "formula.hpp"

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

std::string True::to_string() const {
	return "⊤";
}

std::string False::to_string() const {
	return "⊥";
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

std::string UnaryConnective::to_string() const {
	return symbol() + " (" + _subformula->to_string() + ")";
}

std::string BinaryConnective::to_string() const {
	return "(" + _left_subformula->to_string() + ") " + symbol() + " (" + _right_subformula->to_string() + ")";
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
	return symbol() + _variable_name + ". " + _subformula->to_string();
}

std::string ForAll::symbol() const {
	return "∀ ";
}

std::string Exists::symbol() const {
	return "∃ ";
}

