#pragma once

#include <deque>

#include "formula.hpp"

enum class RuleStatus {
	Success,
	Failure
};

struct ConjIResult {
	RuleStatus status;
	std::shared_ptr<Formula> new_target_1;
	std::shared_ptr<Formula> new_target_2;
};

struct DisjEResult {
	RuleStatus status;
	std::shared_ptr<Formula> new_assumption_1;
	std::shared_ptr<Formula> new_assumption_2;
};

struct IffIResult {
	RuleStatus status;
	std::shared_ptr<Formula> left_subformula;
	std::shared_ptr<Formula> right_subformula;
};

struct ImpEResult {
	RuleStatus status;
	std::shared_ptr<Formula> left_subformula;
	std::shared_ptr<Formula> right_subformula;
};

class Goal {
	public:
		Goal(const std::shared_ptr<Formula>& f)
			:_meta_variables({}), _assumptions({}), _target_formula(f), _solved(false)
		{}
		
		Goal(const std::deque<std::shared_ptr<Formula>>& a, const std::shared_ptr<Formula>& f)
			:_meta_variables({}), _assumptions(a), _target_formula(f), _solved(false)
		{}
		
		std::string to_string() const;
		void set_target(const std::shared_ptr<Formula>& formula);
		void add_assumption(const std::shared_ptr<Formula>& formula);
		void remove_assumption(unsigned index);
		std::set<std::string> get_free_vars_in_assumptions() const;
		std::set<std::string> get_free_vars_in_target_formula() const;
		std::set<std::string> get_free_variables() const;
		RuleStatus apply_assumption();
		RuleStatus apply_rule_not_i();
		RuleStatus apply_erule_not_e();
		ConjIResult apply_rule_conj_i();
		RuleStatus apply_erule_conj_e();
		RuleStatus apply_rule_disj_i_1();
		RuleStatus apply_rule_disj_i_2();
		DisjEResult apply_erule_disj_e();
		RuleStatus apply_rule_imp_i();
		ImpEResult apply_erule_imp_e();
		IffIResult apply_rule_iff_i();
		RuleStatus apply_erule_iff_e();
		RuleStatus apply_rule_all_i();
		RuleStatus apply_erule_all_e(const std::shared_ptr<Term>& replacement_term);
		RuleStatus apply_rule_ex_i(const std::shared_ptr<Term>& replacement_term);
		RuleStatus apply_erule_ex_e();
		RuleStatus apply_rule_ccontr();
		RuleStatus apply_rule_classical();
		void shift_assumptions(unsigned n);
	private:
		std::string body_to_string() const;
	private:
		std::set<std::string> _meta_variables;
		std::deque<std::shared_ptr<Formula>> _assumptions;
		std::shared_ptr<Formula> _target_formula;
		bool _solved;
};

