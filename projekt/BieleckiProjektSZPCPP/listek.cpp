#include "listek.h"

Listek::Listek(Polozenie p, std::vector<Polozenie> k) {
	polozenie = p;
	ksztalt = k;
}

Listek::Listek() { 
	
}

void Listek::setPolozenie( Polozenie pol ) {
	polozenie = pol;
}

Polozenie Listek::getPolozenie() {
	return polozenie;
}

std::vector<Polozenie> Listek::getKsztalt() {
	return ksztalt;
}

std::vector<Listek> losujListki( int listkow, int leafSize ) {
	int maxLong = leafSize*listkow*8;
	int sumLong = 0;
	int rozmiarListka = 1;
	std::vector<Listek> listki;
	for ( int ii=0;ii<listkow;ii++ ) {
		
		Polozenie pol;
		std::vector<Polozenie> ksztalt;
		
		std::vector<Polozenie> ksztaltPrawy;
		for ( int jj=0;jj<rozmiarListka;jj++ ) {
			pol.x = (float)(rand())/(float)RAND_MAX*10-5;
			pol.y = (float)(rand())/(float)RAND_MAX*10-5;
			int norm = leafSize/sqrt(pow(pol.x,2) + pow(pol.y,2));
			pol.x = norm * pol.x;
			pol.y = norm * pol.y;
			if ( jj > 0 ) {
				pol.x = pol.x - ksztaltPrawy[jj-1].x;
				pol.y = pol.y - ksztaltPrawy[jj-1].y;
			}
			ksztaltPrawy.push_back(pol);
		}
		
		std::vector<Polozenie> ksztaltLewy;
		for ( int jj=0;jj<rozmiarListka;jj++ ) {
			pol.x = (float)(rand())/(float)RAND_MAX*10-5;
			pol.y = (float)(rand())/(float)RAND_MAX*10-5;
			int norm = leafSize/sqrt(pow(pol.x,2) + pow(pol.y,2));
			pol.x = norm * pol.x;
			pol.y = norm * pol.y;
			if ( jj > 0 ) {
				pol.x = pol.x - ksztaltLewy[jj-1].x;
				pol.y = pol.y - ksztaltLewy[jj-1].y;
			}
			ksztaltLewy.push_back(pol);
		} 
		
		for ( int jj=0;jj<rozmiarListka;jj++ )
			ksztalt.push_back(ksztaltLewy[rozmiarListka-1-jj]);
		pol.x = 0;
		pol.y = 0;
		ksztalt.push_back(pol);
		for ( int jj=0;jj<rozmiarListka;jj++ )
			ksztalt.push_back(ksztaltPrawy[jj]);
			
		/* Stary listek
		for ( int jj=1;jj<ksztalt.size();jj++ )
			ksztalt[jj].y = ksztalt[jj].y + ksztalt[jj-1].y;
		//Wysrodkowanie listka
		int diff = ksztalt[0].y - ksztalt[(int)(rozmiarListka/2)+1].y;
		for ( int jj=0;jj<ksztalt.size();jj++ ) { 
			ksztalt[jj].y +=diff;
			ksztalt[jj].x -=(int)(rozmiarListka/2)+1;
		}
		*/
		pol.x = (float)(rand())/(float)RAND_MAX*100 - 50;
		pol.y = (float)(rand())/(float)RAND_MAX*100;
		sumLong += sqrt(pow(pol.x,2) + pow(pol.y,2));
		Listek lisc(pol, ksztalt);
		listki.push_back(lisc);
		
	}
	float norm = ( float )maxLong/( float )sumLong;
	for (int ii=0;ii<listkow;ii++ ) {
		Polozenie pol = listki[ii].getPolozenie();
		pol.x = pol.x*norm;
		pol.y = pol.y*norm;
		listki[ii].setPolozenie(pol);
	}
	return listki;
}

int Listek::getSize() {
	return sqrt( pow(polozenie.x,2) + pow(polozenie.y,2) );
}

