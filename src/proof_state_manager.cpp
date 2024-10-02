#include "proof_state_manager.hpp"

std::string ProofStateManager::to_string() const {
	if (_goals.empty()) {
		return "No goals!";
	}

	std::stringstream s;
	
	auto size = _goals.size();
	
	s << "Goals to prove: " << size << "\n";
	
	for (size_t i = 0; i < size; i++) {
		s << (i + 1) << ". " << _goals[i].to_string();
		if (i < size - 1) {
			s << "\n";
		}
	}
	
	return s.str();
}

ManagerStatus ProofStateManager::apply_assumption() {
	if (_goals.empty()) {
		return ManagerStatus(ManagerStatusCode::EmptyGoalList);
	}

	RuleStatus status = _goals[0].apply_assumption();
	
	if (status == RuleStatus::Failure) {
		return ManagerStatus(ManagerStatusCode::Failure);
	}
	
	_goals.pop_front();
	
	return ManagerStatus(ManagerStatusCode::Success);
}

void ProofStateManager::apply_rule_not_i() {
	// TODO: handle empty goal list

	RuleStatus status = _goals[0].apply_rule_not_i();
	
	if (status == RuleStatus::Failure) {
		// TODO: handle failure
	}
}

void ProofStateManager::apply_erule_not_e() {
	// TODO: handle empty goal list

	RuleStatus status = _goals[0].apply_erule_not_e();
	
	if (status == RuleStatus::Failure) {
		// TODO: handle failure
	}
}

void ProofStateManager::apply_rule_conj_i() {
	ConjIResult result = _goals[0].apply_rule_conj_i();
	
	RuleStatus status = result.status;
	
	if (status == RuleStatus::Failure) {
		// TODO: handle failure
		return;
	}
	
	auto target_1 = result.new_target_1;
	auto target_2 = result.new_target_2;
	
	Goal new_goal_1 = _goals[0];
	Goal new_goal_2 = _goals[0];
	
	new_goal_1.set_target(target_1);
	new_goal_2.set_target(target_2);
	
	_goals.pop_front();
	
	_goals.push_front(new_goal_2);
	_goals.push_front(new_goal_1);
}

ManagerStatus ProofStateManager::apply_erule_conj_e() {
	if (_goals.empty()) {
		return ManagerStatus(ManagerStatusCode::EmptyGoalList);
	}

	RuleStatus status = _goals[0].apply_erule_conj_e();
	
	if (status == RuleStatus::Failure) {
		return ManagerStatus(ManagerStatusCode::Failure);
	}
	
	return ManagerStatus(ManagerStatusCode::Success);
}

void ProofStateManager::apply_rule_disj_i_1() {
	// TODO: handle empty goal list
	
	RuleStatus status = _goals[0].apply_rule_disj_i_1();
	
	if (status == RuleStatus::Failure) {
		// TODO: handle failure
	}
}

void ProofStateManager::apply_rule_disj_i_2() {
	// TODO: handle empty goal list
	
	RuleStatus status = _goals[0].apply_rule_disj_i_2();
	
	if (status == RuleStatus::Failure) {
		// TODO: handle failure
	}
}

void ProofStateManager::apply_erule_disj_e() {
	// TODO: handle empty goal list
	
	DisjEResult result = _goals[0].apply_erule_disj_e();
	
	RuleStatus status = result.status;
	
	if (status == RuleStatus::Failure) {
		// TODO: handle failure
		return;
	}
	
	auto disj_left = result.new_assumption_1;
	auto disj_right = result.new_assumption_2;
	
	Goal new_goal_1 = _goals[0];
	Goal new_goal_2 = _goals[0];
	
	new_goal_1.add_assumption(disj_left);
	new_goal_2.add_assumption(disj_right);
	
	_goals.pop_front();
	
	_goals.push_front(new_goal_2);
	_goals.push_front(new_goal_1);
}

ManagerStatus ProofStateManager::apply_rule_imp_i() {
	if (_goals.empty()) {
		return ManagerStatus(ManagerStatusCode::EmptyGoalList);
	}

	RuleStatus status = _goals[0].apply_rule_imp_i();
	
	if (status == RuleStatus::Failure) {
		return ManagerStatus(ManagerStatusCode::Failure);
	}
	
	return ManagerStatus(ManagerStatusCode::Success);
}

ManagerStatus ProofStateManager::apply_erule_imp_e() {
	if (_goals.empty()) {
		return ManagerStatus(ManagerStatusCode::EmptyGoalList);
	}
	
	ImpEResult result = _goals[0].apply_erule_imp_e();
	
	RuleStatus status = result.status;
	
	if (status == RuleStatus::Failure) {
		return ManagerStatus(ManagerStatusCode::Failure);
	}
	
	auto left_subformula = result.left_subformula;
	auto right_subformula = result.right_subformula;
	
	Goal new_goal_1 = _goals[0];
	Goal new_goal_2 = _goals[0];
	
	new_goal_1.set_target(left_subformula);
	
	new_goal_2.add_assumption(right_subformula);
	
	_goals.pop_front();
	
	_goals.push_front(new_goal_2);
	_goals.push_front(new_goal_1);
	
	return ManagerStatus(ManagerStatusCode::Success);
}

ManagerStatus ProofStateManager::apply_rule_iff_i() {
	if (_goals.empty()) {
		return ManagerStatus(ManagerStatusCode::EmptyGoalList);
	}
	
	IffIResult result = _goals[0].apply_rule_iff_i();
	
	RuleStatus status = result.status;
	
	if (status == RuleStatus::Failure) {
		return ManagerStatus(ManagerStatusCode::Failure);
	}
	
	auto left_subformula = result.left_subformula;
	auto right_subformula = result.right_subformula;
	
	Goal new_goal_1 = _goals[0];
	Goal new_goal_2 = _goals[0];
	
	new_goal_1.add_assumption(left_subformula);
	new_goal_1.set_target(right_subformula);
	
	new_goal_2.add_assumption(right_subformula);
	new_goal_2.set_target(left_subformula);
	
	_goals.pop_front();
	
	_goals.push_front(new_goal_2);
	_goals.push_front(new_goal_1);
	
	return ManagerStatus(ManagerStatusCode::Success);
}

ManagerStatus ProofStateManager::apply_erule_iff_e() {
	if (_goals.empty()) {
		return ManagerStatus(ManagerStatusCode::EmptyGoalList);
	}
	
	RuleStatus status = _goals[0].apply_erule_iff_e();
	
	if (status == RuleStatus::Failure) {
		return ManagerStatus(ManagerStatusCode::Failure);
	}
	
	return ManagerStatus(ManagerStatusCode::Success);
}

ManagerStatus ProofStateManager::apply_rule_all_i() {
	if (_goals.empty()) {
		return ManagerStatus(ManagerStatusCode::EmptyGoalList);
	}
	
	RuleStatus status = _goals[0].apply_rule_all_i();
	
	if (status == RuleStatus::Failure) {
		return ManagerStatus(ManagerStatusCode::Failure);
	}
	
	return ManagerStatus(ManagerStatusCode::Success);
}

ManagerStatus ProofStateManager::apply_erule_all_e(const std::shared_ptr<Term>& replacement_term) {
	if (_goals.empty()) {
		return ManagerStatus(ManagerStatusCode::EmptyGoalList);
	}
	
	RuleStatus status = _goals[0].apply_erule_all_e(replacement_term);
	
	if (status == RuleStatus::Failure) {
		return ManagerStatus(ManagerStatusCode::Failure);
	}
	
	return ManagerStatus(ManagerStatusCode::Success);
}

ManagerStatus ProofStateManager::apply_rule_ex_i(const std::shared_ptr<Term>& replacement_term) {
	if (_goals.empty()) {
		return ManagerStatus(ManagerStatusCode::EmptyGoalList);
	}
	
	RuleStatus status = _goals[0].apply_rule_ex_i(replacement_term);
	
	if (status == RuleStatus::Failure) {
		return ManagerStatus(ManagerStatusCode::Failure);
	}
	
	return ManagerStatus(ManagerStatusCode::Success);
}

ManagerStatus ProofStateManager::apply_erule_ex_e() {
	if (_goals.empty()) {
		return ManagerStatus(ManagerStatusCode::EmptyGoalList);
	}
	
	RuleStatus status = _goals[0].apply_erule_ex_e();
	
	if (status == RuleStatus::Failure) {
		return ManagerStatus(ManagerStatusCode::Failure);
	}
	
	return ManagerStatus(ManagerStatusCode::Success);
}

bool ProofStateManager::goals_solved() const {
	return _goals.empty();
}

