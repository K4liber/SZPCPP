#include "kwiatek.h"

Kwiatek::Kwiatek( Listek l[], int size ) {
	for ( int ii=0;ii<size;ii++ )
		listki.push_back(l[ii]);
	for ( int ii=0;ii<listki.size();ii++ ) {
		Listek lisc = listki[ii];
	}
}

Kwiatek::Kwiatek( std::vector<Listek> l,  std::vector<Polozenie> k,
					Parametry params ) {
						
	for ( int ii=0;ii<l.size();ii++ )
		listki.push_back(l[ii]);
	for ( int ii=0;ii<k.size();ii++ )
		korzenie.push_back(k[ii]);
		
	korzenSize = params.korzenSize;
	leafSize = params.leafSize;
	liczValue();
	this->params = params;
}

std::vector<Listek> Kwiatek::getListki() {
	return listki;
}

void Kwiatek::setKorzenie(std::vector<Polozenie> k) {
	for ( int ii=0;ii<k.size();ii++ )
		korzenie.push_back(k[ii]);
}

std::vector<Polozenie> Kwiatek::getKorzenie() {
	return korzenie;
}

void Kwiatek::setKorzenSize(int kS) {
	korzenSize = kS;
}

int Kwiatek::getKorzenSize() {
	return korzenSize;
}

void Kwiatek::liczProste() {
	for ( int ii=0;ii<listki.size();ii++ ) {
		std::vector<Polozenie> pol = listki[ii].getKsztalt();
		Polozenie sr = listki[ii].getPolozenie();
		Prosta pr1, pr2, pr3;
		pr1.isLeaf = true;
		pr2.isLeaf = true;
		pr3.isLeaf = false;
		if ( (float)(pol[1].x-pol[0].x) != 0 )
			pr1.a = (float)(pol[1].y-pol[0].y)/(float)(pol[1].x-pol[0].x);
		else 
			pr1.a = 999999.99;
		pr1.b = (float)sr.y - pr1.a*(float)sr.x;
		pr1.x1 = sr.x - pol[0].x;
		pr1.x2 = sr.x;
		if ( (float)(pol[2].x-pol[1].x) != 0 )
			pr2.a = (float)(pol[2].y-pol[1].y)/(float)(pol[2].x-pol[1].x);
		else 
			pr2.a = 999999.99;
		pr2.b = (float)sr.y - pr2.a*(float)sr.x;
		pr2.x1 = sr.x - pol[0].x;
		pr2.x2 = sr.x;
		//std::cout<<"y = "<<pr1.a<<"x + "<<pr1.b<<" ; "<<pr1.x1<<" < x < "<<pr1.x2<<std::endl;
		
		if ( (float)sr.x != 0 )
			pr3.a = (float)sr.y/(float)sr.x;
		else
			pr3.a = 999999.99;
		pr3.b = 0;
		if ( sr.x > 0 ) {
			pr3.x1 = 0;
			pr3.x2 = sr.x;
		} else {
			pr3.x2 = 0;
			pr3.x1 = sr.x;
		}
		
		proste.push_back(pr1);
		proste.push_back(pr2);
		proste.push_back(pr3);
	}
}

void Kwiatek::liczValue() {
	liczProste();
	value = 0;
	for ( float xx=-1000;xx+=10;xx<1001 ) {
		for ( float xx2=-200;xx2+=20;xx2<201 ) {
			std::vector<float> odleglosci;
			Prosta promyk;
			float yy = sqrt(1000000 - pow(xx,2));
			float yy2 = 0;
			if ( xx != xx2 )
				promyk.a = yy/xx;
			else 
				promyk.a = 999999.99;
				
			promyk.b = yy-promyk.a*xx;
			if ( xx > xx2 ) {
				promyk.x1 = xx2;
				promyk.x2 = xx;
			} else {
				promyk.x1 = xx;
				promyk.x2 = xx2;
			}
			
			for ( int ii=0;ii<proste.size();ii++ ) {
				odleglosci.push_back(liczOdleglosc( proste[ii], promyk ));
			}
			float min = 9999999;
			int index = 0;
			for ( int ii=0;ii<odleglosci.size();ii++ ) {
				if ( odleglosci[ii] < min ) {
					min = odleglosci[ii];
					index = ii;
				}
			}
			if ( proste[index].isLeaf && min!=9999999 ) {
				value+=params.clp;
			}
		}
	}
	
	std::map <std::string,float> pixs;
	for ( int ii=0;ii<korzenie.size();ii++ ) {
		value-= params.cks*((float)pow(korzenie[ii].x,2) + (float)pow(korzenie[ii].y,2));
		for ( int jj=-korzenSize;jj<korzenSize;jj++ ) {
			for ( int zz=-korzenSize;zz<korzenSize;zz++ ) {
				if ( pow(jj,2) + pow(zz,2) < pow(korzenSize,2) ) {
					Polozenie pol;
					pol.x = korzenie[ii].x + jj;
					pol.y = korzenie[ii].y + zz;
					std::string sd;
					char stemp[9] = "";
					snprintf(stemp, 9, "%d %d", pol.x, pol.y);
					sd = stemp;
					pixs[sd] = 1.0/(float)sqrt(pow(korzenie[ii].x+10,2) + pow(korzenie[ii].y+10,2));
				}
			}
		}
	}
	for ( auto iterator = pixs.begin(); iterator != pixs.end(); iterator++) {
		value+=params.ckp;
	}
	
	for ( int ii=0;ii<listki.size();ii++ ) {
		Polozenie pol = listki[ii].getPolozenie();
		value-= params.cls*((float)pow(pol.x,2) + (float)pow(pol.y,2));
	}
	
}

float liczOdleglosc( Prosta prosta, Prosta promyk ) {
	Polozenie pol;
	if ( promyk.x1 !=0 ) 
		pol.x = promyk.x1;
	else 
		pol.x = promyk.x2;
	pol.y = promyk.a*pol.x + promyk.b;
	float x = ( promyk.b - prosta.b ) / ( prosta.a - promyk.a );
	float y = promyk.a*x+promyk.b;
	if ( x > promyk.x1 && x < promyk.x2) 
		return sqrt(pow(x - pol.x,2) + pow(y - pol.y,2));
	else 
		return 9999999;
}

float Kwiatek::getValue() {
	return value;
}

std::vector<Polozenie> losujKorzenie( int ilosc, int korzenSize ) {
	std::vector<Polozenie> korzenie;
	int suma;
	int maxLong = korzenSize*ilosc*8;
	for ( int ii=0;ii<ilosc;ii++ ) {
		
		Polozenie pol;
		pol.x = (float)(rand())/(float)RAND_MAX*50-25;
		pol.y = (float)(rand())/(float)RAND_MAX*50 + korzenSize;
		suma+=sqrt(pow(pol.x,2) + pow(pol.y,2));
		korzenie.push_back(pol);
	}
	float norm = (float)maxLong/(float)suma;
	for ( int ii=0;ii<ilosc;ii++ ) {
		Polozenie pol;
		korzenie[ii].x = korzenie[ii].x*norm;
		korzenie[ii].y = korzenie[ii].y*norm;
	}
	return korzenie;
}

int findMax( std::vector<Kwiatek> kwiatki ) {
	float value = 0;
	int toReturn;
	for ( int ii=0;ii<kwiatki.size();ii++ ) {
		if ( kwiatki[ii].getValue() > value ) {
			toReturn = ii;
			value = kwiatki[ii].getValue();
		}
	}
	return toReturn;
}
