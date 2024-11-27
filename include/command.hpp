#pragma once

#include <optional>
#include <string>

enum class Rule {
	Assumption,
	NotI,
	NotE,
	ConjI,
	ConjE,
	DisjI1,
	DisjI2,
	DisjE,
	ImpI,
	ImpE,
	IffI,
	IffE,
	AllI,
	AllE,
	ExI,
	ExE,
	Ccontr,
	Classical
};

enum class CommandType {
	Empty,
	ListRequest,
	HelpRequest,
	ExitRequest,
	RuleApplication,
	Done,
	Shift,
	UnknownCommand
};

struct Command {
	CommandType type;
	std::optional<Rule> rule_to_apply;

    static Command parse_command(const std::string&);
};
