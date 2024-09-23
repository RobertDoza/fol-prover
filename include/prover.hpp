#pragma once

#include "formula.hpp"
#include "goal.hpp"

class Prover {
	public:
		Prover(const std::shared_ptr<Formula>& f)
			:_formula_to_prove(f), _goal_keeper(f)
		{}
		
		void start();
	private:
		void interact_with_user();
	private:
		std::shared_ptr<Formula> _formula_to_prove;
		GoalKeeper _goal_keeper;
};

