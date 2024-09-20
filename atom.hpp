#pragma once

#include "formula.hpp"

class AtomicFormula : public Formula {
	public:
		virtual std::set<std::string> get_variable_names() const = 0;
		std::set<std::string> get_free_variable_names() const override;
	protected:
		bool requires_parentheses() const override;
};

class LogicalConstant : public AtomicFormula {
	public:
		std::set<std::string> get_variable_names() const override;
};

class True : public LogicalConstant {
	public:
		std::string to_string() const override;
		FormulaType type() const override;
		bool operator==(const True& other) const;
		std::shared_ptr<Formula> rename_var(const std::string& old_name, const std::string& new_name) const override;
};

class False : public LogicalConstant {
	public:
		std::string to_string() const override;
		FormulaType type() const override;
		bool operator==(const False& other) const;
		std::shared_ptr<Formula> rename_var(const std::string& old_name, const std::string& new_name) const override;
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
		FormulaType type() const override;
		bool operator==(const SimpleAtom& other) const;
		std::set<std::string> get_variable_names() const override;
		std::shared_ptr<Formula> rename_var(const std::string& old_name, const std::string& new_name) const override;
};

class ComplexAtom : public Atom {
	public:
		ComplexAtom(const std::string& p, const std::vector<std::shared_ptr<Term>>& terms)
			:Atom(p), _terms(terms)
		{}
		
		std::string to_string() const override;
		FormulaType type() const override;
		bool operator==(const ComplexAtom& other) const;
		std::set<std::string> get_variable_names() const override;
		std::shared_ptr<Formula> rename_var(const std::string& old_name, const std::string& new_name) const override;
	private:
		std::vector<std::shared_ptr<Term>> _terms;
};

