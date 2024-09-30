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
		case CommandType::RuleApplication:
			// TODO: check if command.rule_to_apply has value
			
			apply_rule(command.rule_to_apply.value());
			
			// TODO: if rule is AllE or ExI, user needs to provide "replacement term"
			
			return ExecuteStatus::Continue;
	}
	
	return ExecuteStatus::StopFailure;
}

void Prover::apply_rule(const Rule& rule) {
	switch (rule) {
		case Rule::Assumption:
			_proof_state_manager.apply_assumption();
			return;
		case Rule::NotI:
			// TODO
			return;
		case Rule::NotE:
			// TODO
			return;
		case Rule::ConjI:
			// TODO
			return;
		case Rule::ConjE:
			_proof_state_manager.apply_erule_conj_e();
			return;
		case Rule::DisjI1:
			// TODO
			return;
		case Rule::DisjI2:
			// TODO
			return;
		case Rule::DisjE:
			// TODO
			return;
		case Rule::ImpI:
			_proof_state_manager.apply_rule_imp_i();
			return;
		case Rule::ImpE:
			// TODO
			return;
		case Rule::IffI:
			// TODO
			return;
		case Rule::IffE:
			// TODO
			return;
		case Rule::AllI:
			// TODO
			//_proof_state_manager.apply_rule_all_i();
			return;
		case Rule::AllE:
			// TODO
			return;
		case Rule::ExI:
			// TODO
			return;
		case Rule::ExE:
			// TODO
			return;
		case Rule::Done:
			// TODO handle or remove Done from Rule
			return;
	}
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

