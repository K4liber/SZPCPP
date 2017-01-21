#ifndef GENERATION_H
#define GENERATION_H

#include "kwiatek.h"
#include <algorithm>
#include <math.h>

class Generation {
	
	public:
		Generation( std::vector<Kwiatek> kwiatki, Parametry p );
		std::vector<Kwiatek> getKwiatki();
		void nextGeneration();
		float getMaxValue();
		float getAverageValue();
		int getGenerationNumber();
		Parametry getParams();
		
	private:
		int generationNumber;
		std::vector<Kwiatek> kwiatki;
		Parametry params;
		
};

std::vector<Kwiatek> krzyzowanie( std::vector<Kwiatek> kwiatki, 
	Parametry p);
std::vector<Kwiatek> mutacje( std::vector<Kwiatek> kwiatki ,
	Parametry p);
Kwiatek krzyzuj( Kwiatek k1, Kwiatek k2, Parametry params );

#endif
