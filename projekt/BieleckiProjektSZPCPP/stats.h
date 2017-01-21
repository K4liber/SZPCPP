#ifndef STATS_H
#define STATS_H

#include "generation.h"

class Stats {
	
	public:
	    
	    Stats( Generation genPoczatkowa );
		std::vector<float> getAverages();
		std::vector<Generation> getGenerations();
		std::vector<float> getMaxs();
		void nextGeneration();
		std::vector<Kwiatek> getKwiatki(int ii);
		Generation getGeneration(int ii);
		Parametry getParams();
		
	private:
		Parametry params;
		std::vector<Generation> generations;
		
};

void rysujKwiatek( Stats stats, int generationNr,int toDraw);
void saveStats( Stats stats );

#endif
