#include "billing.hpp"

int main () {
	Billing bil (std::cin);
	std::cout << "*** STATYSTYKA DZIENNA ***" << std::endl;
	bil.statystykaDzienna (std::cout);
	std::cout << "\n*** STATYSTYKA KRAJOWA ***" << std::endl;
	bil.statystykaKrajowa (std::cout);
	return 0;
}
