#pragma once

#include <string>
#include <vector>
#include <memory>
#include <sstream>

#include "term.hpp"

enum class FormulaType {
	True,
	False,
	SimpleAtom,
	ComplexAtom,
	Negation,
	Conjunction,
	Disjunction,
	Implication,
	Equivalence,
	ForAll,
	Exists
};

// Base formula class
class Formula {
	public:
		virtual std::string to_string() const = 0;
		virtual bool requires_parentheses() const = 0;
		virtual FormulaType type() const = 0;
		virtual std::set<std::string> get_free_variable_names() const = 0;
};

bool are_equal(const std::shared_ptr<Formula>& f1, const std::shared_ptr<Formula>& f2);

std::ostream& operator<<(std::ostream& out, const Formula& formula);

// Logical Connective
class LogicalConnective : public Formula {
	protected:
		virtual std::string symbol() const = 0;
		bool requires_parentheses() const override;
};

class UnaryConnective : public LogicalConnective {
	public:
		UnaryConnective(const std::shared_ptr<Formula>& sub)
			:_subformula(sub)
		{}
		
		std::string to_string() const override;
		std::shared_ptr<Formula> get_subformula() const;
		std::set<std::string> get_free_variable_names() const override;
	protected:
		std::shared_ptr<Formula> _subformula;
};

class Negation : public UnaryConnective {
	public:
		Negation(const std::shared_ptr<Formula>& sub)
			:UnaryConnective(sub)
		{}
		
		FormulaType type() const override;
		bool operator==(const Negation& other) const;
	private:
		std::string symbol() const override;
};

class BinaryConnective : public LogicalConnective {
	public:
		BinaryConnective(const std::shared_ptr<Formula>& l, const std::shared_ptr<Formula>& r)
			:_left_subformula(l), _right_subformula(r)
		{}
		
		std::string to_string() const override;
		std::shared_ptr<Formula> get_left_subformula() const;
		std::shared_ptr<Formula> get_right_subformula() const;
		std::set<std::string> get_free_variable_names() const override;
	protected:
		std::shared_ptr<Formula> _left_subformula;
		std::shared_ptr<Formula> _right_subformula;
};

class Conjunction : public BinaryConnective {
	public:
		Conjunction(const std::shared_ptr<Formula>& l, const std::shared_ptr<Formula>& r)
			:BinaryConnective(l, r)
		{}
		
		FormulaType type() const override;
		bool operator==(const Conjunction& other) const;
	private:
		std::string symbol() const override;
};

class Disjunction : public BinaryConnective {
	public:
		Disjunction(const std::shared_ptr<Formula>& l, const std::shared_ptr<Formula>& r)
			:BinaryConnective(l, r)
		{}
		
		FormulaType type() const override;
		bool operator==(const Disjunction& other) const;
	private:
		std::string symbol() const override;
};

class Implication : public BinaryConnective {
	public:
		Implication(const std::shared_ptr<Formula>& l, const std::shared_ptr<Formula>& r)
			:BinaryConnective(l, r)
		{}
		
		FormulaType type() const override;
		bool operator==(const Implication& other) const;
	private:
		std::string symbol() const override;
};

class Equivalence : public BinaryConnective {
	public:
		Equivalence(const std::shared_ptr<Formula>& l, const std::shared_ptr<Formula>& r)
			:BinaryConnective(l, r)
		{}
		
		FormulaType type() const override;
		bool operator==(const Equivalence& other) const;
	private:
		std::string symbol() const override;
};

// Quantifier
class Quantifier : public Formula {
	public:
		Quantifier(const std::string& var, const std::shared_ptr<Formula>& sub)
			:_variable_name(var), _subformula(sub)
		{}
		
		std::string to_string() const override;
		std::set<std::string> get_free_variable_names() const override;
		virtual void alpha_convert(const std::string& new_var_name) = 0;
	protected:
		virtual std::string symbol() const = 0;
		bool requires_parentheses() const override;
	protected:
		std::string _variable_name;
		std::shared_ptr<Formula> _subformula;
};

class ForAll : public Quantifier {
	public:
		ForAll(const std::string& var, const std::shared_ptr<Formula>& sub)
			:Quantifier(var, sub)
		{}
		
		FormulaType type() const override;
		bool operator==(const ForAll& other) const;
		void alpha_convert(const std::string& new_var_name) override;
	private:
		std::string symbol() const override;
};

class Exists : public Quantifier {
	public:
		Exists(const std::string& var, const std::shared_ptr<Formula>& sub)
			:Quantifier(var, sub)
		{}
		
		FormulaType type() const override;
		bool operator==(const Exists& other) const;
		void alpha_convert(const std::string& new_var_name) override;
	private:
		std::string symbol() const override;
};

