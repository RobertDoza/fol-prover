#pragma once

#include <string>
#include <vector>
#include <memory>

// Base formula class
class Formula {};

// Term
class Term {};

class Variable : public Term {
	public:
		Variable(const std::string& name)
			:_name(name)
		{}
	private:
		std::string _name;
};

class Constant : public Term {
	public:
		Constant(const std::string& name)
			:_name(name)
		{}
	private:
		std::string _name;
};

class ComplexTerm : public Term {
	public:
		ComplexTerm(const std::string& f, const std::vector<std::shared_ptr<Term>>& terms)
			:_function_symbol(f), _subterms(terms)
		{}
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

