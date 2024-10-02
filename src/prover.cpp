#include "prover.hpp"

#include <iostream>

// TODO: move to a more appropriate place
std::vector<std::string> split_into_words(const std::string& input) {
    std::vector<std::string> words;
    std::istringstream stream(input);
    std::string word;
    
    while (stream >> word) {
        words.push_back(word);
    }
    
    return words;
}

void Prover::start() {
	print_intro_message();
	
	// TODO...
	interact_with_user();
}

void Prover::print_intro_message() {
	std::cout << "Welcome!" << std::endl;
	std::cout << "Formula to prove:" << std::endl;
	std::cout << *_formula_to_prove << std::endl;
	std::cout << commands << std::endl;
}

Command Prover::parse_user_input(const std::string& user_input) {
	std::vector<std::string> words = split_into_words(user_input);
	
	auto length = words.size();
	
	if (length == 0) {
		return {CommandType::Empty, {}};
	}
	
	std::string command_word = words[0];
	
	if (command_word == "apply") {
		if (length == 1 or length > 3) {
			return {CommandType::UnknownCommand, {}};
		}
		
		if (words[1] == "assumption") {
			if (length > 2) {
				return {CommandType::UnknownCommand, {}};
			}
		
			return {CommandType::RuleApplication, {Rule::Assumption}};
		}
		
		if (words[1] == "rule") {
			if (length == 2) {
				return {CommandType::UnknownCommand, {}};
			}
			
			if (words[2] == "notI") {
				return {CommandType::RuleApplication, {Rule::NotI}};
			} else if (words[2] == "conjI") {
				return {CommandType::RuleApplication, {Rule::ConjI}};
			} else if (words[2] == "disjI1") {
				return {CommandType::RuleApplication, {Rule::DisjI1}};
			} else if (words[2] == "disjI2") {
				return {CommandType::RuleApplication, {Rule::DisjI2}};
			} else if (words[2] == "impI") {
				return {CommandType::RuleApplication, {Rule::ImpI}};
			} else if (words[2] == "iffI") {
				return {CommandType::RuleApplication, {Rule::IffI}};
			} else if (words[2] == "allI") {
				return {CommandType::RuleApplication, {Rule::AllI}};
			} else if (words[2] == "exI") {
				return {CommandType::RuleApplication, {Rule::ExI}};
			}
			
			return {CommandType::UnknownCommand, {}};
		}
		
		if (words[1] == "erule") {
			if (length == 2) {
				return {CommandType::UnknownCommand, {}};
			}
			
			if (words[2] == "notE") {
				return {CommandType::RuleApplication, {Rule::NotE}};
			} else if (words[2] == "conjE") {
				return {CommandType::RuleApplication, {Rule::ConjE}};
			} else if (words[2] == "disjE") {
				return {CommandType::RuleApplication, {Rule::DisjE}};
			} else if (words[2] == "impE") {
				return {CommandType::RuleApplication, {Rule::ImpE}};
			} else if (words[2] == "iffE") {
				return {CommandType::RuleApplication, {Rule::IffE}};
			} else if (words[2] == "allE") {
				return {CommandType::RuleApplication, {Rule::AllE}};
			} else if (words[2] == "exE") {
				return {CommandType::RuleApplication, {Rule::ExE}};
			}
			
			return {CommandType::UnknownCommand, {}};
		}
		
		return {CommandType::UnknownCommand, {}};
	} else if (command_word == "exit") {
		if (length > 1) {
			return {CommandType::UnknownCommand, {}};
		}
		
		return {CommandType::ExitRequest, {}};
	} else if (command_word == "list") {
		if (length > 1) {
			return {CommandType::UnknownCommand, {}};
		}
		
		return {CommandType::ListRequest, {}};
	} else if (command_word == "help") {
		if (length > 1) {
			return {CommandType::UnknownCommand, {}};
		}
		
		return {CommandType::HelpRequest, {}};
	} else if (command_word == "done") {
		if (length > 1) {
			return {CommandType::UnknownCommand, {}};
		}
		
		return {CommandType::Done, {}};
	}
	
	return {CommandType::UnknownCommand, {}};
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
		case CommandType::RuleApplication:
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
			// TODO
			return ManagerStatus(ManagerStatusCode::Failure);
		case Rule::DisjI2:
			// TODO
			return ManagerStatus(ManagerStatusCode::Failure);
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
				std::string user_input;
				
				std::cout << "Instantiate variable: ";
				std::getline(std::cin, user_input);
				
				if (user_input.empty()) {
					std::cout << "Error: Variable name cannot be empty." << std::endl;
					return ManagerStatus(ManagerStatusCode::Failure);
				}
				
				// TODO: parse term from user input
				Variable var(user_input);
				
				// TODO: use parsed term as argument for apply_erule_all_e
				return _proof_state_manager.apply_erule_all_e(std::make_shared<Variable>(var));
			}
		case Rule::ExI: {
				std::string user_input;
				
				std::cout << "Instantiate variable: ";
				std::getline(std::cin, user_input);
				
				if (user_input.empty()) {
					std::cout << "Error: Variable name cannot be empty." << std::endl;
					return ManagerStatus(ManagerStatusCode::Failure);
				}
				
				// TODO: parse term from user input
				Variable var(user_input);
				
				// TODO: use parsed term as argument for apply_rule_ex_i
				return _proof_state_manager.apply_rule_ex_i(std::make_shared<Variable>(var));
			}
		case Rule::ExE:
			return _proof_state_manager.apply_erule_ex_e();
	}
	
	return ManagerStatus(ManagerStatusCode::Failure);
}

void Prover::interact_with_user() {
	std::string user_input;

	while (true) {
		std::cout << std::endl;
		std::cout << _proof_state_manager.to_string() << std::endl;
		std::cout << "> ";
		
		std::getline(std::cin, user_input);
		
		Command command = parse_user_input(user_input);
		
		// TODO
		
		ExecuteStatus status = execute(command);
		
		if (status != ExecuteStatus::Continue) {
			break;
		}
	}
}

