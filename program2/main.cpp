#include "rozklad.hpp"
#include "dane_stat.hpp"
#include <boost/shared_ptr.hpp>
#include <dirent.h>
#include <stdio.h>

void listujPliki( const char * nazwa_sciezki, std::vector <boost::shared_ptr <DaneStat> > *dane) {
    struct dirent * plik;
    DIR * sciezka;
    if (( sciezka = opendir( nazwa_sciezki ) ) ) {
        while (( plik = readdir( sciezka ) ) ){
			std::string fileName = plik->d_name;
			if ( fileName.find("dat") != std::string::npos) {
				boost::shared_ptr<DaneStat> ptr( new DaneStatProxy(fileName));
				dane->push_back(ptr);
			}
		}
        closedir( sciezka );
    }
}

int main(int argc, char * argv[]) {
	// Wskaźniki do obiektów przechowujących dane
	std::vector <boost::shared_ptr <DaneStat> > dane;
	const char * nazwa_sciezki = "files";
	
	if (argc > 1) {
		const char * nazwa_sciezki_arg = argv[1];
		listujPliki(nazwa_sciezki_arg, &dane);
	} else {
		const char * nazwa_sciezki = "files";
		listujPliki(nazwa_sciezki, &dane);
	}

	// Rejestrujemy wtyczki
	FabrykaRozkladow::rejestruj (&RozkladGaussa::kreator, 
		std::string("Rozklad Gaussa"));
	FabrykaRozkladow::rejestruj (&RozkladLorentza::kreator, 
		std::string("Rozklad Lorentza"));
	FabrykaRozkladow::rejestruj (&RozkladPoissona::kreator, 
		std::string("Rozklad Poissona"));
	
	//MENU
	int close = 0;
	while (!close) {
		int wybor_pliku = 1;
		int wybor_r = 1;
		std::cout<<"Wybierz numer pliku z danymi i zatwierdz."<<std::endl;
		for ( int ii=0;ii<dane.size();ii++ ) 
			std::cout<<dane[ii].get()->nazwa()<<" ("<<ii+1<<")"<<std::endl;
		std::cin>>wybor_pliku;
		std::cout<<"Wybierz numer rozkladu i zatwierdz."<<std::endl;
		for ( int ii=1;ii<=FabrykaRozkladow::ilosc();ii++ ) 
			std::cout<<FabrykaRozkladow::nazwa(ii)<<" ("<<ii<<")"<<std::endl;
		std::cin>>wybor_r;
		// Tworzy miziadelko do obliczania statystyk
		std::shared_ptr <Rozklad> rozkl (FabrykaRozkladow::utworz (wybor_r, 
			dane[wybor_pliku-1].get()->wczytajDane ()));
		ParametryRozkladu params = rozkl.get()->oblicz();
		std::cout<<FabrykaRozkladow::nazwa(wybor_r)<<" - parametry: "<<std::endl;
		for ( auto iterator = params.begin(); iterator != params.end(); iterator++) {
			std::cout<<iterator->first<<":\t"<<iterator->second<<std::endl;
		}
		std::cout<<"Wpisz 0 jesli chcesz kontynuowac, 1 zeby wyjsc:"<<std::endl;
		std::cin>>close;
	}
	
	return 0;
}
