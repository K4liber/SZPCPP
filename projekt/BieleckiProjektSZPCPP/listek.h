#ifndef LISTEK_H
#define LISTEK_H

#include "lib.h"

class Listek {
	
	public: 
		Listek(Polozenie p, std::vector<Polozenie> k);
		Listek();
		void setPolozenie(Polozenie pol);
		Polozenie getPolozenie();
		int getSize();
		std::vector<Polozenie> getKsztalt();
	private:
		Polozenie polozenie;
		std::vector<Polozenie> ksztalt;
		
};

std::vector<Listek> losujListki( int listkow, int leafSize );

#endif
