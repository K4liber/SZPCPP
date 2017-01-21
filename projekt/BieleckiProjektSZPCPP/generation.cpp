#include "generation.h"

Generation::Generation( std::vector<Kwiatek> k , Parametry p) {
	for ( int ii=0;ii<k.size();ii++ ) {
		kwiatki.push_back(k[ii]);
	}
	generationNumber = 0;
	params = p;
}

std::vector<Kwiatek> Generation::getKwiatki() {
	return kwiatki;
}

void Generation::nextGeneration() {
	generationNumber++;
	kwiatki = mutacje(kwiatki, params);
	kwiatki = krzyzowanie(kwiatki, params);
}

float Generation::getMaxValue() {
	std::vector<float> values;
	for ( int ii=0;ii<kwiatki.size();ii++ )
		values.push_back(kwiatki[ii].getValue());
	return *std::max_element(values.begin(),values.end());
}

float Generation::getAverageValue() {
	float average;
	for ( int ii=0;ii<kwiatki.size();ii++ ) {
		average+=kwiatki[ii].getValue();
	}
	return average/(float)kwiatki.size();
}

int Generation::getGenerationNumber() {
	return generationNumber;
}

std::vector<Kwiatek> krzyzowanie( std::vector<Kwiatek> kwiatki, 
	Parametry p) {
	std::vector<Kwiatek> poKrzyzowaniu;
	int toNextGen = p.N/2;
	int zMax = p.N/3;
	for ( int jj=0;jj<toNextGen;jj++ ) {
		for ( int zz=jj+1;zz<toNextGen;zz++ ) {
			if (zz - jj+1 > zMax -1 ) {
				zMax-=2;
				break;
			}
			poKrzyzowaniu.push_back(krzyzuj(kwiatki[jj], kwiatki[zz], p));
			if ( poKrzyzowaniu.size()==p.N ) {
				return poKrzyzowaniu;
			}
		}
	}
	return kwiatki;
}

bool mniejsze( Polozenie pol1, Polozenie pol2 ) 
{
    return pol1.y < pol2.y; 
}

Kwiatek krzyzuj( Kwiatek k1, Kwiatek k2, Parametry params ) {
	bool segreguj = 1;
	bool normuj = 0;
	std::vector<Listek> listki;
	int maxLong = params.leafSize*k1.getListki().size()*8;
	int maxLongK = params.korzenSize*params.korzeni*8;
	//krzyzujemy listki
	if ( segreguj ) {
		std::vector <Polozenie> katy1;
		std::vector <Polozenie> katy2;
		std::vector <Listek> listki1 = k1.getListki();
		std::vector <Listek> listki2 = k2.getListki();
		std::vector <Listek> posortowane1;
		std::vector <Listek> posortowane2;
		for ( int ii=0;ii<listki1.size();ii++ ) {
			Polozenie kat1,kat2;
			kat1.x = ii;
			kat2.x = ii;
			if ( listki1[ii].getPolozenie().y != 0)
				kat1.y = atan((float)listki1[ii].getPolozenie().x/(float)listki1[ii].getPolozenie().y);
			else 
				kat1.y = atan((float)listki1[ii].getPolozenie().x/0.00001);
			if ( listki2[ii].getPolozenie().y != 0)
				kat2.y = atan((float)listki2[ii].getPolozenie().x/(float)listki2[ii].getPolozenie().y);
			else 
				kat2.y = atan((float)listki2[ii].getPolozenie().x/0.00001);
			katy1.push_back(kat1);
			katy2.push_back(kat2);
		}
		sort( katy1.begin(), katy1.end(), mniejsze );
		sort( katy2.begin(), katy2.end(), mniejsze );
		for ( int ii=0;ii<katy1.size();ii++ ) {
			posortowane1.push_back(listki1[katy1[ii].x]);
			posortowane2.push_back(listki2[katy2[ii].x]);
		}
		for ( int ii=0;ii<k1.getListki().size();ii++ ) {
			if ( 0.5 <  (float)(rand())/(float)RAND_MAX )
				listki.push_back(posortowane1[ii]);
			else
				listki.push_back(posortowane2[ii]);
		}
	} else {
		for ( int ii=0;ii<k1.getListki().size();ii++ ) {
			if ( 0.5 <  (float)(rand())/(float)RAND_MAX )
				listki.push_back(k1.getListki()[ii]);
			else
				listki.push_back(k2.getListki()[ii]);
		}
	}
	
	int sum = 0;
	for ( int jj=0;jj<listki.size();jj++ ) {
		sum+=listki[jj].getSize();
	}
	float norm = ( float )maxLong/( float )sum;
	for (int ii=0;ii<listki.size();ii++ ) {
		Polozenie pol = listki[ii].getPolozenie();
		if ( normuj ) {
			pol.x = pol.x*norm;
			pol.y = pol.y*norm;
		}
		if ( pol.x > 150 )
			pol.x = 20;
		if ( pol.y > 150 )
			pol.y = 20;
		if ( pol.x < -150 )
			pol.x = -20;
		if ( pol.y < -150 )
			pol.y = -20;
		listki[ii].setPolozenie(pol);
	}
	//krzyzujemy korzenie
	std::vector<Polozenie> korzenie;
	int sumK = 0;
	if ( segreguj ) {
		std::vector <Polozenie> katy1;
		std::vector <Polozenie> katy2;
		std::vector <Polozenie> korzenie1 = k1.getKorzenie();
		std::vector <Polozenie> korzenie2 = k2.getKorzenie();
		std::vector <Polozenie> posortowane1;
		std::vector <Polozenie> posortowane2;
		for ( int ii=0;ii<korzenie1.size();ii++ ) {
			Polozenie kat1,kat2;
			kat1.x = ii;
			kat2.x = ii;
			if ( korzenie1[ii].y != 0)
				kat1.y = atan((float)korzenie1[ii].x/(float)korzenie1[ii].y);
			else 
				kat1.y = atan((float)korzenie1[ii].x/0.00001);
			if ( korzenie2[ii].y != 0)
				kat2.y = atan((float)korzenie2[ii].x/(float)korzenie2[ii].y);
			else 
				kat2.y = atan((float)korzenie2[ii].x/0.00001);
			katy1.push_back(kat1);
			katy2.push_back(kat2);
		}
		sort( katy1.begin(), katy1.end(), mniejsze );
		sort( katy2.begin(), katy2.end(), mniejsze );
		for ( int ii=0;ii<katy1.size();ii++ ) {
			posortowane1.push_back(korzenie1[katy1[ii].x]);
			posortowane2.push_back(korzenie2[katy2[ii].x]);
		}
		for ( int ii=0;ii<k1.getKorzenie().size();ii++ ) {
			if ( 0.5 <  (float)(rand())/(float)RAND_MAX )
				korzenie.push_back(posortowane1[ii]);
			else
				korzenie.push_back(posortowane2[ii]);
		}
	} else {
		for ( int ii=0;ii<k1.getKorzenie().size();ii++ ) {
			if ( 0.5 <  (float)(rand())/(float)RAND_MAX )
				korzenie.push_back(k1.getKorzenie()[ii]);
			else
				korzenie.push_back(k2.getKorzenie()[ii]);
		}
	}
	for ( int jj=0;jj<korzenie.size();jj++ ) {
		int korzenSize = 
			sqrt( pow(korzenie[jj].x, 2) + pow(korzenie[jj].y ,2) );
		sumK+=korzenSize;
	}
	float normK = ( float )maxLongK/( float )sumK;
	for (int ii=0;ii<korzenie.size();ii++ ) {
		if ( normuj ) {
			korzenie[ii].x = korzenie[ii].x*normK;
			korzenie[ii].y = korzenie[ii].y*normK;
		}
		if ( korzenie[ii].y > 70 )
			korzenie[ii].y = 20;
		if ( korzenie[ii].x > 70 )
			korzenie[ii].x = 20;
		if ( korzenie[ii].y < -70 )
			korzenie[ii].y = -20;
		if ( korzenie[ii].x < -70 )
			korzenie[ii].x = -20;
	}
	Kwiatek skrzyzowany( listki, korzenie, params );
	return skrzyzowany;
}

std::vector<Kwiatek> mutacje( std::vector<Kwiatek> kwiatki ,
	Parametry p) {
	bool normuj = 0;
	int rozmiarListka = 1;
	float prawd = 0.002;
	int maxLong = p.leafSize*p.listkow*8;
	for ( int ii=0;ii<kwiatki.size();ii++ ) {
		//mutujemy listki
		std::vector<Listek> listki;
		std::vector<Polozenie> korzenie;
		int maxLong = p.leafSize*kwiatki[0].getListki().size()*8;
		for ( int jj=0;jj<kwiatki[ii].getListki().size();jj++ ) {
			//Mutujemy ksztalt listka
			std::vector<Polozenie> ksztalt;
			Polozenie pol;
			if ( (float)(rand())/(float)RAND_MAX < prawd ) {
				std::vector<Polozenie> ksztaltPrawy;
				for ( int jj=0;jj<rozmiarListka;jj++ ) {
					pol.x = (float)(rand())/(float)RAND_MAX*10-5;
					pol.y = (float)(rand())/(float)RAND_MAX*10-5;
					int norm = p.leafSize/sqrt(pow(pol.x,2) + pow(pol.y,2));
					if ( normuj ) {
						pol.x = norm * pol.x;
						pol.y = norm * pol.y;
					}
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
					int norm = p.leafSize/sqrt(pow(pol.x,2) + pow(pol.y,2));
					if ( normuj ) {
						pol.x = norm * pol.x;
						pol.y = norm * pol.y;
					}
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
				
			} else
				ksztalt = kwiatki[ii].getListki()[jj].getKsztalt();
			//Mutujemy polozenie
			if ( (float)(rand())/(float)RAND_MAX < prawd ) {
				pol.x = (float)(rand())/(float)RAND_MAX*100 - 50;
				pol.y = (float)(rand())/(float)RAND_MAX*100;
			} else 
				pol = kwiatki[ii].getListki()[jj].getPolozenie();
			Listek lisc(pol, ksztalt);
			listki.push_back(lisc);
		}
		//Normujemy listki
		int sum = 0;
		for ( int jj=0;jj<listki.size();jj++ ) {
			sum+=listki[jj].getSize();
		}
		float norm = ( float )maxLong/( float )sum;
		for (int ii=0;ii<listki.size();ii++ ) {
			Polozenie pol = listki[ii].getPolozenie();
			if ( normuj ) {
				pol.x = pol.x*norm;
				pol.y = pol.y*norm;
			}
			if ( pol.x > 150 )
				pol.x = 20;
			if ( pol.y > 150 )
				pol.y = 20;
			if ( pol.x < -150 )
				pol.x = -20;
			if ( pol.y < -150 )
				pol.y = -20;
			listki[ii].setPolozenie(pol);
		}
		//Mutujemy i normujemy korzenie
		int sumaK = 0;
		int maxLongK = p.korzenSize*p.korzeni*5;
		for ( int ii=0;ii<kwiatki[ii].getKorzenie().size();ii++ ) {
			Polozenie pol;
			if ( (float)(rand())/(float)RAND_MAX < prawd ) {
				pol.x = (float)(rand())/(float)RAND_MAX*50-25;
				pol.y = (float)(rand())/(float)RAND_MAX*50;
			} else
				pol = kwiatki[ii].getKorzenie()[ii];
			korzenie.push_back(pol);
			sumaK+=sqrt(pow(pol.x,2)+pow(pol.y,2));
		}
		float normK = (float)maxLongK/(float)sumaK;
		for ( int ii=0;ii<korzenie.size();ii++ ) {
			if ( normuj ) {
				korzenie[ii].x = korzenie[ii].x*normK;
				korzenie[ii].y = korzenie[ii].y*normK;
			}
			if ( korzenie[ii].y > 70 )
				korzenie[ii].y = 20;
			if ( korzenie[ii].x > 70 )
				korzenie[ii].x = 20;
			if ( korzenie[ii].y < -70 )
				korzenie[ii].y = -20;
			if ( korzenie[ii].x < -70 )
				korzenie[ii].x = -20;
		}
		kwiatki[ii] = Kwiatek(listki, korzenie, p);
	}
	return kwiatki;
}

Parametry Generation::getParams() {
	return params;
}
