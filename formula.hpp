#pragma once

#include <string>
#include <vector>
#include <memory>
#include <sstream>

// Base formula class
class Formula {
	public:
		virtual std::string to_string() const = 0;
};

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
		
		std::string to_string() const override;
	private:
		std::string _name;
};

class Constant : public Term {
	public:
		Constant(const std::string& name)
			:_name(name)
		{}
		
		std::string to_string() const override;
	private:
		std::string _name;
};

class ComplexTerm : public Term {
	public:
		ComplexTerm(const std::string& f, const std::vector<std::shared_ptr<Term>>& terms)
			:_function_symbol(f), _subterms(terms)
		{}
		
		std::string to_string() const override;
	private:
		std::string _function_symbol;
		std::vector<std::shared_ptr<Term>> _subterms;
};

// Atomic Formula
class AtomicFormula : public Formula {};
class LogicalConstant : public AtomicFormula {};
class True : public LogicalConstant {
	public:
		std::string to_string() const override;
};
class False : public LogicalConstant {
	public:
		std::string to_string() const override;
};

class Atom : public AtomicFormula {
	public:
		Atom(const std::string& p)
			:_predicate_symbol(p)
		{}
	protected:
		std::string _predicate_symbol;
};

class SimpleAtom : public Atom {
	public:
		SimpleAtom(const std::string& p)
			:Atom(p)
		{}
		
		std::string to_string() const override;
};

class ComplexAtom : public Atom {
	public:
		ComplexAtom(const std::string& p, const std::vector<std::shared_ptr<Term>>& terms)
			:Atom(p), _terms(terms)
		{}
		
		std::string to_string() const override;
	private:
		std::vector<std::shared_ptr<Term>> _terms;
};

// Logical Connective
class LogicalConnective : public Formula {};

class UnaryConnective : public LogicalConnective {
	public:
		UnaryConnective(const std::shared_ptr<Formula>& sub)
			:_subformula(sub)
		{}
	protected:
		std::shared_ptr<Formula> _subformula;
};

class Negation : public UnaryConnective {
	public:
		Negation(const std::shared_ptr<Formula>& sub)
			:UnaryConnective(sub)
		{}
		
		std::string to_string() const override;
};

class BinaryConnective : public LogicalConnective {
	public:
		BinaryConnective(const std::shared_ptr<Formula>& l, const std::shared_ptr<Formula>& r)
			:_left_subformula(l), _right_subformula(r)
		{}
	protected:
		std::shared_ptr<Formula> _left_subformula;
		std::shared_ptr<Formula> _right_subformula;
};

class Conjunction : public BinaryConnective {
	public:
		Conjunction(const std::shared_ptr<Formula>& l, const std::shared_ptr<Formula>& r)
			:BinaryConnective(l, r)
		{}
		
		std::string to_string() const override;
};

class Disjunction : public BinaryConnective {
	public:
		Disjunction(const std::shared_ptr<Formula>& l, const std::shared_ptr<Formula>& r)
			:BinaryConnective(l, r)
		{}
		
		std::string to_string() const override;
};

class Implication : public BinaryConnective {
	public:
		Implication(const std::shared_ptr<Formula>& l, const std::shared_ptr<Formula>& r)
			:BinaryConnective(l, r)
		{}
		
		std::string to_string() const override;
};

class Equivalence : public BinaryConnective {
	public:
		Equivalence(const std::shared_ptr<Formula>& l, const std::shared_ptr<Formula>& r)
			:BinaryConnective(l, r)
		{}
		
		std::string to_string() const override;
};

// Quantifier
class Quantifier : public Formula {};
class ForAll : public Quantifier {};
class Exists : public Quantifier {};

