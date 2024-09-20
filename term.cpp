#include <sstream>

#include "term.hpp"

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
