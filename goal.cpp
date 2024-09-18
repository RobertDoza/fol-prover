#include "goal.hpp"

std::string Goal::to_string() const {
	std::stringstream s;
	
	s << "[";
	
	for (size_t i = 0; i < _assumptions.size(); i++) {
		s << *_assumptions[i];
		if (i < _assumptions.size() - 1) {
			s << ", ";
		}
	}
	
	s << "]";
	
	s << " ⊢  ";
	
	s << *_goal;
	
	return s.str();
}

