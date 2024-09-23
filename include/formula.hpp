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

