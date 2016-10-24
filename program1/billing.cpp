#include "billing.hpp"
#include "histogram.hpp"
#include <map>
#include <iostream>
#include <cstring>
#include <vector>
#include <functional>

std::string Polaczenie::kod () const {
	std::string kod = nr;
	kod.resize(2);
	return kod;
}

Billing::Billing (std::istream &is) 
{
	char call[100];
	//Wczytywanie danych ze standardowego wejscia do blng_
	while (is.getline(call,100)) {
		std::vector<char*> callData;
		Polaczenie polaczenie;
		char* chars_array = strtok(call, "\t");
		while (chars_array)
		{
			callData.push_back(chars_array);
			chars_array = strtok(NULL, "\t");
		}
		polaczenie.dzien = atoi(callData[0]);
		polaczenie.nr = callData[1];
		polaczenie.czas = atof(callData[2]);
		blng_.push_back(polaczenie);
	}
}

void Billing::statystykaDzienna (std::ostream &os) const 
{
	std::vector <unsigned> stat (32, 0); // przechowuje liczbę połączeń każdego dnia
	// Przelatuje całą tablicę blng_ i uzuzpełnia tablicę stat
	int numberOfCalls = 0;
	for (int ii=0; ii<blng_.size(); ii++) {
		stat[blng_[ii].dzien]++;
		numberOfCalls++;
	}
	// Formatuje i wyświetla wyniki na os
	std::cout.precision(2);
	std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	for (int ii=1; ii<stat.size(); ii++) {
		
		std::cout<<ii<<":\t"<<stat[ii]<<"\t"<<"("
			<<100*(float)stat[ii]/numberOfCalls<<"%):\t";
		for (int jj=0;jj<stat[ii]/10;jj++)
			std::cout<<"*";
		std::cout<<std::endl;
	}
	
	std::cout<<std::endl<<"Wykonanych polaczen:\t"<<numberOfCalls<<std::endl;
}

void Billing::statystykaKrajowa (std::ostream &os) const 
{
	std::map <std::string, Histogram> stat; // osobna statystyka dla każdego kodu
	// Przelatuje całą tablicę blng_ i wrzuca czasy rozmów do
	// odpowiednich histogramów w stat
	for ( auto &x : blng_) {
		stat[x.kod()].dodaj(x.czas);
	}
	// Formatuje i wyświetla wyniki na os
	std::cout<<"Kraj\tN\tSred.\tOdch.\tMin\tMax"<<std::endl;
	for ( auto iterator = stat.begin(); iterator != stat.end(); iterator++) {
		std::cout<<iterator->first<<":\t"<<iterator->second.rozmiar()<<"\t"
			<<iterator->second.srednia()<<"\t"<<iterator->second.odchylenie()
			<<"\t"<<iterator->second.min()<<"\t"
			<<iterator->second.max()<<std::endl;
	} 
	std::cout<<std::endl;
}

