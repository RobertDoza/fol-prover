#include "formula.hpp"
#include "atom.hpp"
#include "connective.hpp"
#include "quantifier.hpp"

bool are_equal(const std::shared_ptr<Formula>& f1, const std::shared_ptr<Formula>& f2) {
	FormulaType type = f1->type();

	if (type != f2->type()) {
		return false;
	}
	
	switch (type) {
		case FormulaType::True: {
			auto t1 = std::dynamic_pointer_cast<True>(f1);
			auto t2 = std::dynamic_pointer_cast<True>(f2);
			return *t1 == *t2;
		}
		case FormulaType::False: {
			auto x1 = std::dynamic_pointer_cast<False>(f1);
			auto x2 = std::dynamic_pointer_cast<False>(f2);
			return *x1 == *x2;
		}
		case FormulaType::SimpleAtom: {
			auto s1 = std::dynamic_pointer_cast<SimpleAtom>(f1);
			auto s2 = std::dynamic_pointer_cast<SimpleAtom>(f2);
			return *s1 == *s2;
		}
		case FormulaType::ComplexAtom: {
			auto c1 = std::dynamic_pointer_cast<ComplexAtom>(f1);
			auto c2 = std::dynamic_pointer_cast<ComplexAtom>(f2);
			return *c1 == *c2;
		}
		case FormulaType::Negation: {
			auto n1 = std::dynamic_pointer_cast<Negation>(f1);
			auto n2 = std::dynamic_pointer_cast<Negation>(f2);
			return *n1 == *n2;
		}
		case FormulaType::Conjunction: {
			auto c1 = std::dynamic_pointer_cast<Conjunction>(f1);
			auto c2 = std::dynamic_pointer_cast<Conjunction>(f2);
			return *c1 == *c2;
		}
		case FormulaType::Disjunction: {
			auto d1 = std::dynamic_pointer_cast<Disjunction>(f1);
			auto d2 = std::dynamic_pointer_cast<Disjunction>(f2);
			return *d1 == *d2;
		}
		case FormulaType::Implication: {
			auto i1 = std::dynamic_pointer_cast<Implication>(f1);
			auto i2 = std::dynamic_pointer_cast<Implication>(f2);
			return *i1 == *i2;
		}
		case FormulaType::Equivalence: {
			auto e1 = std::dynamic_pointer_cast<Equivalence>(f1);
			auto e2 = std::dynamic_pointer_cast<Equivalence>(f2);
			return *e1 == *e2;
		}
		case FormulaType::ForAll: {
			auto fa1 = std::dynamic_pointer_cast<ForAll>(f1);
			auto fa2 = std::dynamic_pointer_cast<ForAll>(f2);
			return *fa1 == *fa2;
		}
		case FormulaType::Exists: {
			auto ex1 = std::dynamic_pointer_cast<Exists>(f1);
			auto ex2 = std::dynamic_pointer_cast<Exists>(f2);
			return *ex1 == *ex2;
		}
	}

	return false;
}

std::ostream& operator<<(std::ostream& out, const Formula& formula) {
	out << formula.to_string();
	return out;
}

std::string Formula::generate_new_variable_name(const std::string& old_name, const std::set<std::string>& used_names) {
	std::string new_name;
	
	unsigned i = 1;
	while (true) {
		new_name = old_name + std::to_string(i);
		
		if (used_names.find(new_name) == used_names.end()) {
			break;
		}
		
		i++;
	}
	
	return new_name;
}

