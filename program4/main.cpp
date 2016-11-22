#include "mnozenie_macierzy.hpp"

#include <boost/shared_ptr.hpp>
#include <dirent.h>
#include <sys/time.h>    
#include <fstream>
#include <iostream>

double interwal( timespec start, timespec koniec ) {
	return koniec.tv_sec - start.tv_sec;
}

int main(int argc, char *arg []) {
	if (argc != 5)		// Sprawdzenie ilosci argumentow
	{
		std::cout << "Program wymaga podania 3 nazw plikow z programem jako parametry oraz liczbe watkow!" << std::endl;
		return 1;
	}
	
	int p = atoi(arg [4]);
	
	std::ifstream macierz1_plik (arg [1]);
	std::ifstream macierz2_plik (arg [2]);
	std::ifstream wynik_plik (arg [3]);
	const clockid_t ZegarID = CLOCK_REALTIME;
	timespec start, koniec; // Struktury przechowujące czas
	std::cout << "Mnozenie macierzy..." <<std::endl;
	std::cout.flush ();
	clock_gettime (ZegarID, &start); // Zapisuje czas początku mnożenia
	// Mnoży macierze a i b (liczba oznacza liczbę równoległych wątków)
	Macierz a(macierz1_plik);
	Macierz b(macierz2_plik);
	Macierz wynikPoprawny(wynik_plik);
	mnozenie_macierzy (a, b, wynikPoprawny, p);
	clock_gettime (ZegarID, &koniec); // Zapisuje czas końca mnożenia
	std::cout << " zajelo " << interwal (start, koniec) << " s" << std::endl;
	macierz1_plik.close();
	macierz2_plik.close();
	wynik_plik.close();
	return 0;
}
