#include <vector>
#include <sstream>

#include "command.hpp"

std::vector<std::string> split_into_words(const std::string& input) {
    std::vector<std::string> words;
    std::istringstream stream(input);
    std::string word;
    
    while (stream >> word) {
        words.push_back(word);
    }
    
    return words;
}

Command Command::parse_command(const std::string& user_input) {
	std::vector<std::string> words = split_into_words(user_input);
	
	auto length = words.size();
	
	if (length == 0) {
		return {CommandType::Empty, {}};
	}
	
	std::string command_word = words[0];
	
	if (command_word == "shift") {
		if (length > 1) {
			return {CommandType::UnknownCommand, {}};
		}
	
		return {CommandType::Shift, {}};
	}
	
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
			} else if (words[2] == "ccontr") {
				return {CommandType::RuleApplication, {Rule::Ccontr}};
			} else if (words[2] == "classical") {
				return {CommandType::RuleApplication, {Rule::Classical}};
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
	} else if (command_word == "exit" || command_word == "quit") {
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
