#include "prover.hpp"

#include <iostream>

extern std::shared_ptr<Term> parse_term(const std::string&);

void Prover::start_interactive_proof(const std::shared_ptr<Formula>& formula_to_prove) {
	Prover prover(formula_to_prove);
	prover.start();
}

Prover::Prover(const std::shared_ptr<Formula>& f)
	:_formula_to_prove(f), _proof_state_manager(f)
{}

void Prover::start() {
    print_intro_message();
	
	std::string user_input;

	while (true) {
		std::cout << std::endl;
		std::cout << _proof_state_manager.to_string() << std::endl;
		std::cout << "> ";
		
		std::getline(std::cin, user_input);
		
		Command command = Command::parse_command(user_input);
		
		ExecuteStatus status = execute(command);
		
		if (status != ExecuteStatus::Continue) {
			break;
		}
	}
}

void Prover::print_intro_message() {
	std::cout << "Welcome!" << std::endl;
	std::cout << "Formula to prove:" << std::endl;
	std::cout << *_formula_to_prove << std::endl;
	std::cout << commands << std::endl;
}

ExecuteStatus Prover::execute(const Command& command) {
	CommandType command_type = command.type;
	
	switch (command_type) {
		case CommandType::Empty:
			return ExecuteStatus::Continue;
		case CommandType::UnknownCommand:
			std::cout << "Unknown command!" << std::endl;
			return ExecuteStatus::Continue;
		case CommandType::ListRequest:
			std::cout << list_of_rules << std::endl;
			return ExecuteStatus::Continue;
		case CommandType::HelpRequest:
			std::cout << commands << std::endl;
			return ExecuteStatus::Continue;
		case CommandType::ExitRequest:
			return ExecuteStatus::StopSuccess;
		case CommandType::Done:
			if (!_proof_state_manager.goals_solved()) {
				std::cout << "There are still goals to solve!" << std::endl;
				return ExecuteStatus::Continue;
			}
			
			return ExecuteStatus::StopSuccess;
		case CommandType::RuleApplication: {
			auto rule = command.rule_to_apply;
			
			if (!rule.has_value()) {
				throw std::logic_error("CommandType::RuleApplication requires a rule, but none was provided.");
			}
			
			ManagerStatus manager_status = apply_rule(rule.value());
			
			switch (manager_status.code) {
				case ManagerStatusCode::Success:
					break;
				case ManagerStatusCode::Failure:
					std::cout << "Unable to apply rule to goal." << std::endl;
					break;
				case ManagerStatusCode::EmptyGoalList:
					std::cout << "There are no goals to be solved." << std::endl;
					break;
			}
			
			return ExecuteStatus::Continue;
		}
		case CommandType::Shift:
			ManagerStatus manager_status = _proof_state_manager.shift();
			
			if (manager_status.code == ManagerStatusCode::EmptyGoalList) {
				std::cout << "There are no goals to apply shift to." << std::endl;
			}
			
			return ExecuteStatus::Continue;
	}
	
	return ExecuteStatus::StopFailure;
}

ManagerStatus Prover::apply_rule(const Rule& rule) {
	switch (rule) {
		case Rule::Assumption:
			return _proof_state_manager.apply_assumption();
		case Rule::NotI:
			return _proof_state_manager.apply_rule_not_i();
		case Rule::NotE:
			return _proof_state_manager.apply_erule_not_e();
		case Rule::ConjI:
			return _proof_state_manager.apply_rule_conj_i();
		case Rule::ConjE:
			return _proof_state_manager.apply_erule_conj_e();
		case Rule::DisjI1:
			return _proof_state_manager.apply_rule_disj_i_1();
		case Rule::DisjI2:
			return _proof_state_manager.apply_rule_disj_i_2();
		case Rule::DisjE:
			return _proof_state_manager.apply_erule_disj_e();
		case Rule::ImpI:
			return _proof_state_manager.apply_rule_imp_i();
		case Rule::ImpE:
			return _proof_state_manager.apply_erule_imp_e();
		case Rule::IffI:
			return _proof_state_manager.apply_rule_iff_i();
		case Rule::IffE:
			return _proof_state_manager.apply_erule_iff_e();
		case Rule::AllI:
			return _proof_state_manager.apply_rule_all_i();
		case Rule::AllE: {
				std::shared_ptr<Term> term = get_term_from_user();
				return _proof_state_manager.apply_erule_all_e(term);
			}
		case Rule::ExI: {
				std::shared_ptr<Term> term = get_term_from_user();
				return _proof_state_manager.apply_rule_ex_i(term);
			}
		case Rule::ExE:
			return _proof_state_manager.apply_erule_ex_e();
		case Rule::Ccontr:
			return _proof_state_manager.apply_rule_ccontr();
		case Rule::Classical:
			return _proof_state_manager.apply_rule_classical();
	}
	
	return ManagerStatus(ManagerStatusCode::Failure);
}

std::shared_ptr<Term> Prover::get_term_from_user() {
	std::string user_input;
    std::shared_ptr<Term> term;

	do {
		std::cout << "Instantiate variable: ";
		std::getline(std::cin, user_input);
		
		try {
			term = parse_term(user_input);
			return term;
		} catch (const std::exception&) {
			std::cout << "Error parsing term! Please try again." << std::endl;
			continue;
		}
	} while (true);
}
