#pragma once

#include <string>
#include <vector>
#include <memory>
#include <sstream>

// Base formula class
class Formula {};

// Term
class Term {
	public:
		virtual std::string to_string() const = 0;
};

class Variable : public Term {
	public:
		Variable(const std::string& name)
			:_name(name)
		{}
		
		std::string to_string() const override {
			return _name;
		}
	private:
		std::string _name;
};

class Constant : public Term {
	public:
		Constant(const std::string& name)
			:_name(name)
		{}
		
		std::string to_string() const override {
			return _name;
		}
	private:
		std::string _name;
};

class ComplexTerm : public Term {
	public:
		ComplexTerm(const std::string& f, const std::vector<std::shared_ptr<Term>>& terms)
			:_function_symbol(f), _subterms(terms)
		{}
		
		std::string to_string() const override {
			std::stringstream s;
			
			s << _function_symbol;
			
			s << "(";
			
			for (size_t i = 0; i < _subterms.size(); ++i) {
				s << _subterms[i]->to_string();
				if (i < _subterms.size() - 1) {
					s << ", ";
				}
			}
			
			s << ")";
			
			return s.str();
		}
	private:
		std::string _function_symbol;
		std::vector<std::shared_ptr<Term>> _subterms;
};

// Atomic Formula
class AtomicFormula : public Formula {};

// Logical Connective
class LogicalConnective : public Formula {};

class UnaryConnective : public LogicalConnective {};
class Negation : public UnaryConnective {};

class BinaryConnective : public LogicalConnective {};
class Conjunction : public BinaryConnective {};
class Disjunction : public BinaryConnective {};
class Implication : public BinaryConnective {};
class Equivalence : public BinaryConnective {};

// Quantifier
class Quantifier : public Formula {};
class ForAll : public Quantifier {};
class Exists : public Quantifier {};

