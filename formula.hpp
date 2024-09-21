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
		virtual std::set<std::string> get_variable_names() const = 0;
		virtual std::set<std::string> get_free_variable_names() const = 0;
		virtual std::shared_ptr<Formula> replace(const std::string& var_name, const std::shared_ptr<Term>& term) const = 0;
		virtual std::shared_ptr<Formula> rename_var(const std::string& old_name, const std::string& new_name) const = 0;
		
		static std::string generate_new_variable_name(const std::string& old_name, const std::set<std::string>& used_names);
};

bool are_equal(const std::shared_ptr<Formula>& f1, const std::shared_ptr<Formula>& f2);

std::ostream& operator<<(std::ostream& out, const Formula& formula);

// Quantifier
class Quantifier : public Formula {
	public:
		Quantifier(const std::string& var, const std::shared_ptr<Formula>& sub)
			:_variable_name(var), _subformula(sub)
		{}
		
		std::string to_string() const override;
		std::set<std::string> get_variable_names() const override;
		std::set<std::string> get_free_variable_names() const override;
		virtual std::shared_ptr<Quantifier> alpha_convert() const = 0;
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
		std::shared_ptr<Formula> replace(const std::string& var_name, const std::shared_ptr<Term>& term) const override;
		std::shared_ptr<Formula> rename_var(const std::string& old_name, const std::string& new_name) const override;
		std::shared_ptr<Quantifier> alpha_convert() const override;
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
		std::shared_ptr<Formula> replace(const std::string& var_name, const std::shared_ptr<Term>& term) const override;
		std::shared_ptr<Formula> rename_var(const std::string& old_name, const std::string& new_name) const override;
		std::shared_ptr<Quantifier> alpha_convert() const override;
	private:
		std::string symbol() const override;
};

