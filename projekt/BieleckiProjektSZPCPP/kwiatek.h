#ifndef KWIATEK_H
#define KWIATEK_H

#include "listek.h"

class Kwiatek {
	
	public:
		Kwiatek( Listek l[], int size );
		Kwiatek( std::vector<Listek> listki, 
				std::vector<Polozenie> korzenie, Parametry params );
		std::vector<Listek> getListki();
		void setProste( std::vector<Prosta> proste );
		std::vector<Prosta> getProste();
		void setKorzenie( std::vector<Polozenie> korzenie );
		std::vector<Polozenie> getKorzenie();
		void setKorzenSize( int kS );
		int getKorzenSize();
		void liczValue();
		void liczProste();
		float getValue();
		int getLeafSize();
	private:
		std::vector<Listek> listki;
		std::vector<Polozenie> korzenie;
		int korzenSize;
		std::vector<Prosta> proste;
		int leafSize;
		float value;
		Parametry params;
		
};

int findMax( std::vector<Kwiatek> kwiatki );

std::vector<Polozenie> losujKorzenie( int korzeni, int korzenSize);

float liczOdleglosc( Prosta p, Prosta d );

#endif
