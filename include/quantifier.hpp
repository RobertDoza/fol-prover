#pragma once

#include "formula.hpp"

class Quantifier : public Formula {
	public:
		Quantifier(const std::string& var, const std::shared_ptr<Formula>& sub)
			:_variable_name(var), _subformula(sub)
		{}
		
		std::string to_string() const override;
		std::string get_variable_name() const;
		std::shared_ptr<Formula> get_subformula() const;
		std::set<std::string> get_variable_names() const override;
		std::set<std::string> get_free_variable_names() const override;
		virtual std::shared_ptr<Quantifier> alpha_convert() const = 0;
		virtual std::shared_ptr<Quantifier> alpha_convert(const std::string& new_var_name) const = 0;
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
		std::shared_ptr<Quantifier> alpha_convert(const std::string& new_var_name) const override;
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
		std::shared_ptr<Quantifier> alpha_convert(const std::string& new_var_name) const override;
	private:
		std::string symbol() const override;
};

