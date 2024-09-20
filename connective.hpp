#pragma once

#include "formula.hpp"

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
		std::shared_ptr<Formula> rename_var(const std::string& old_name, const std::string& new_name) const override;
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
		std::shared_ptr<Formula> rename_var(const std::string& old_name, const std::string& new_name) const override;
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
		std::shared_ptr<Formula> rename_var(const std::string& old_name, const std::string& new_name) const override;
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
		std::shared_ptr<Formula> rename_var(const std::string& old_name, const std::string& new_name) const override;
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
		std::shared_ptr<Formula> rename_var(const std::string& old_name, const std::string& new_name) const override;
	private:
		std::string symbol() const override;
};

