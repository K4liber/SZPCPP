#ifndef _billing_hpp_
#define _billing_hpp_
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

struct Polaczenie {
	unsigned dzien;
	std::string nr;
	float czas; // czas połączenia
	std::string kod () const; // zwraca dwucyfrowy kod międzynarodowy
};

std::istream &operator>> (std::istream &is, Polaczenie &p);

class Billing {
	public:
		explicit Billing (std::istream &is); // wczytuje połączenia z is
		void statystykaDzienna (std::ostream &os) const;
		void statystykaKrajowa (std::ostream &os) const;
	private:
		std::vector <Polaczenie> blng_; // tablica połączeń
};

#endif
