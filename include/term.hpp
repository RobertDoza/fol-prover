#pragma once

#include <string>
#include <memory>
#include <vector>
#include <set>

enum class TermType {
	Variable,
	Constant,
	ComplexTerm
};

class Term {
	public:
		virtual std::string to_string() const = 0;
		virtual TermType type() const = 0;
		virtual std::set<std::string> get_variable_names() const = 0;
		virtual std::shared_ptr<Term> replace(const std::string& var_name, const std::shared_ptr<Term>& term) const = 0;
		virtual std::shared_ptr<Term> rename_var(const std::string& old_name, const std::string& new_name) const = 0;
};

bool are_equal(const std::shared_ptr<Term>& t1, const std::shared_ptr<Term>& t2);

std::ostream& operator<<(std::ostream& out, const Term& term);

class Variable : public Term {
	public:
		Variable(const std::string& name)
			:_name(name)
		{}
		
		std::string to_string() const override;
		TermType type() const override;
		bool operator==(const Variable& other) const;
		std::set<std::string> get_variable_names() const override;
		std::shared_ptr<Term> replace(const std::string& var_name, const std::shared_ptr<Term>& term) const override;
		std::shared_ptr<Term> rename_var(const std::string& old_name, const std::string& new_name) const override;
	private:
		std::string _name;
};

class Constant : public Term {
	public:
		Constant(const std::string& name)
			:_name(name)
		{}
		
		std::string to_string() const override;
		TermType type() const override;
		bool operator==(const Constant& other) const;
		std::set<std::string> get_variable_names() const override;
		std::shared_ptr<Term> replace(const std::string& var_name, const std::shared_ptr<Term>& term) const override;
		std::shared_ptr<Term> rename_var(const std::string& old_name, const std::string& new_name) const override;
	private:
		std::string _name;
};

class ComplexTerm : public Term {
	public:
		ComplexTerm(const std::string& f, const std::vector<std::shared_ptr<Term>>& terms)
			:_function_symbol(f), _subterms(terms)
		{}
		
		std::string to_string() const override;
		TermType type() const override;
		bool operator==(const ComplexTerm& other) const;
		std::set<std::string> get_variable_names() const override;
		std::shared_ptr<Term> replace(const std::string& var_name, const std::shared_ptr<Term>& term) const override;
		std::shared_ptr<Term> rename_var(const std::string& old_name, const std::string& new_name) const override;
	private:
		std::string _function_symbol;
		std::vector<std::shared_ptr<Term>> _subterms;
};

