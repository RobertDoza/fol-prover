#include <iostream>
#include <memory>

#include "formula.hpp"
#include "prover.hpp"

extern std::shared_ptr<Formula> parse_formula(const std::string& filename);

int main(int argc, char** argv) {
	try {
		std::shared_ptr<Formula> f;
		
		if (argc != 2) {
			throw std::invalid_argument(std::string("Usage: ") + argv[0] + " <filename>");
		}
		
		f = parse_formula(argv[1]);
		
		Prover p(f);
		p.start();
	} catch (const std::exception& e) {
		std::cerr << "Error:" << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
	
	return 0;
}

