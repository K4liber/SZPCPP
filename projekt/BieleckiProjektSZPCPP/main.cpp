#include "stats.h"

Parametry params;
std::string paramsFileName = "int.txt";
std::fstream paramsFile;

void loadParameters() {
	params.N = 50;
	params.listkow = 20;
	params.leafSize = 10;
	params.korzeni = 10;
	params.korzenSize = 10;
	params.automatic = false;
	params.cks = 0.00001;
	params.ckp = 0.001;
	params.cls = 0.00001;
	params.clp = 0.0001;
	if ( paramsFile.good() ) {
		paramsFile >> params.N;
		paramsFile >> params.listkow;
		paramsFile >> params.leafSize;
		paramsFile >> params.korzeni;
		paramsFile >> params.korzenSize;
		int generations;
		paramsFile >> generations;
		if ( generations != 0 ) {
			params.automatic = true;
			params.generations = generations;
		} else {
			params.automatic = false;
		}
		paramsFile >> params.cks;
		paramsFile >> params.ckp;
		paramsFile >> params.cls;
		paramsFile >> params.clp;
	} else {
		std::cout<<"Błędny plik! Uruchomiono ze standardowymi parametrami."
			<<std::endl;
	}
}

int main(int argc, char * argv[]) {
	
	if( argc > 1) {
		paramsFile.open( argv[1],std::fstream::in);
		paramsFileName = argv[1];
		std::cout<<"Instrukcja obslugi:"<<std::endl<<
		"strzalki - przelaczanie pomiedzy osobnikami w populacji"<<std::endl<<
		"N - nastepna generacja"<<std::endl<<
		"P - symuluj kolejne 50 symulacji (wyswietla tylko najlepszego osobnika)"<<std::endl<<
		"S - zapisz dane do plikow"<<std::endl;
	} else {
		std::cout<<"Aby uruchomić program jako 1 argument podaj \n"<<
			"nazwe pliku z parametrami. Poprawny plik: \n" <<
			"[liczba osobników]\n" << "[liczba listków]\n" <<
			"[rozmiar listka]\n" << "[liczba korzeni]\n" <<
			"[rozmiar korzenia]\n" << "[liczba generacji]\n" <<
			"Jeśli chcesz ręcznie  przechodzić przez kolejne generacje," 
			<< " ustaw [liczba generacji] na 0."<<std::endl;
	}
	
	int toDraw = 0;
	int generationNr = 0;
    loadParameters();
    std::vector<Kwiatek> kwiatki;
    BITMAP * diagram = NULL;

	srand (time(NULL));
	init(diagram);
    
    for ( int ii=0;ii<params.N;ii++ ) {
		std::vector<Listek> listki 
			= losujListki( params.listkow, params.leafSize);
		std::vector<Polozenie> korzenie 
			= losujKorzenie( params.korzeni, params.korzenSize );
		Kwiatek kwiatek(listki, korzenie, params);
		kwiatki.push_back(kwiatek);
	}
	
	Generation generation(kwiatki, params);
	Stats stats(generation);
	
	toDraw = findMax(kwiatki);
    rysujKwiatek(stats, generationNr, toDraw);
    
    while ( !key[ KEY_ESC ] ) {
		
		if ( keyrel(KEY_LEFT) && toDraw > 0) 
			rysujKwiatek(stats, generationNr, --toDraw);
		
		if ( keyrel(KEY_RIGHT) && toDraw < params.N - 1 ) 
			rysujKwiatek(stats, generationNr, ++toDraw);
		
		if ( keyrel(KEY_M) ) {
			int max = findMax(stats.getKwiatki(generationNr));
			rysujKwiatek(stats, generationNr, max);
			
		}
		
		if ( keyrel(KEY_N) ) {
			if( generationNr+1>stats.getGenerations().size() );
				stats.nextGeneration();
			generationNr++;
			int max = findMax(stats.getKwiatki(generationNr));
			rysujKwiatek(stats, generationNr, max);
			
		}
		
		if ( keyrel(KEY_P) ) {
			for ( int ii=0;ii<50;ii++ ) {
				if ( generationNr+1>stats.getGenerations().size() );
					stats.nextGeneration();
				generationNr++;
				int max = findMax(stats.getKwiatki(generationNr));
				rysujKwiatek(stats, generationNr, max);
			}
			saveStats( stats );
		}
		
		if ( keyrel(KEY_S) ) {
			saveStats( stats );
		}

    }
	
	deinit(diagram);
	
    return 0;
}

END_OF_MAIN()
