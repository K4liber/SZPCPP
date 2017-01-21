#include "stats.h"

Stats::Stats( Generation genPoczatkowa ) {
	params = genPoczatkowa.getParams();
	generations.push_back( genPoczatkowa );
}

std::vector<float> Stats::getAverages() {
	std::vector<float> averages;
	for ( int ii=0;ii<generations.size();ii++ ) {
		averages.push_back(generations[ii].getAverageValue());
	}
	return averages;
}

std::vector<Generation> Stats::getGenerations() {
	return generations;
}

std::vector<float> Stats::getMaxs() {
	std::vector<float> maxes;
	for ( int ii=0;ii<generations.size();ii++ ) {
		maxes.push_back(generations[ii].getMaxValue());
	}
	return maxes;
}

void Stats::nextGeneration() {
	Generation gen(generations[generations.size()-1]);
	gen.nextGeneration();
	generations.push_back(gen);
}

std::vector<Kwiatek> Stats::getKwiatki(int ii) {
	return generations[ii].getKwiatki();
}

Generation Stats::getGeneration(int ii) {
	return generations[ii];
}

Parametry Stats::getParams() {
	return params;
}

void rysujKwiatek(Stats stats, int generationNr,int toDraw) {
	Parametry params = stats.getParams();
	Kwiatek kwiatek = stats.getKwiatki(generationNr)[toDraw];
	int startX = 250;
	int startY = 300;
	int stalkSize = 30;
	int size = 500;
	std::vector<Listek> listki = kwiatek.getListki();
	std::vector<Polozenie> korzenie = kwiatek.getKorzenie();
	BITMAP * diagram = NULL;
	diagram = create_bitmap( size, size );
	clear_to_color( diagram, makecol( 200, 200, 255 ) );
	for ( int ii=0;ii<listki.size();ii++ ) {
		Listek listek = listki[ii];
		Polozenie pol = listek.getPolozenie();
		line(diagram, startX, startY, startX-pol.x, startY-pol.y, 
			makecol( 0, 150, 0 ) );
		std::vector<Polozenie> ksztalt = listek.getKsztalt();
		for( int ii=1;ii<ksztalt.size();ii++ ) {
			Polozenie polPix1 = ksztalt[ii];
			Polozenie polPix2 = ksztalt[ii-1];
			line(diagram, startX-pol.x-polPix2.x, startY-pol.y-polPix2.y, 
				startX-pol.x-polPix1.x, startY-pol.y-polPix1.y, 
				makecol( 150, 0, 0 ) );
		}
	}
	rectfill( diagram, 0, startY + stalkSize, size, size,
		 makecol( 90, 40, 40 ));
	for ( int ii=0;ii<korzenie.size();ii++ ) {
		line( diagram, startX, startY+stalkSize, startX+korzenie[ii].x, 
			startY+stalkSize+korzenie[ii].y+params.korzenSize, makecol( 0, 0, 0 ) );
		circle( diagram, startX+korzenie[ii].x, startY+stalkSize+korzenie[ii].y+params.korzenSize, 
				kwiatek.getKorzenSize(), makecol( 0, 0, 0 ) );
	}
	line( diagram, startX, startY, startX, startY+stalkSize, 
		makecol( 0, 150, 0 ) );
	
	Generation gen = stats.getGeneration(generationNr);
	float average = gen.getAverageValue();
	float max = gen.getMaxValue();
	drawInfo(diagram, toDraw, kwiatek.getValue(), generationNr,
		average, max);
	blit( diagram, screen, 0, 0, 0, 0, diagram->w, diagram->h );

}

void saveStats( Stats stats ) {
	std::fstream maxFile;
	maxFile.open( "max.data",std::fstream::out);
	std::fstream averageFile;
	averageFile.open( "average.data",std::fstream::out);
	for ( int ii=0;ii<stats.getGenerations().size();ii++ ) {
		maxFile << ii <<"\t" << stats.getGeneration(ii).getMaxValue() << std::endl;
		averageFile << ii <<"\t" << stats.getGeneration(ii).getAverageValue() << std::endl;
	}
	maxFile.close();
	averageFile.close();
	std::cout<<"Pomyslnie zapisano!"<<std::endl;
}
