#include "gfx.hpp"
#include "komendy.hpp"
#include <fstream>
#include <iostream>

int main (int argc, char *arg [])
{
	if (argc != 2)		// Sprawdzenie ilosci argumentow
	{
		std::cerr << "Program wymaga podania nazw pliku z programem jako pierwszego parametru!" << std::endl;
		return 1;
	}
	std::ifstream plik_z_programem (arg [1]);

	// Rejestrowanie komend w fabryce
	FabrykaKomend fk;
	fk.rejestruj (KomendaSkoczDo::ID, &KomendaSkoczDo::kreator);
	fk.rejestruj (KomendaRampa::ID, &KomendaRampa::kreator);
	fk.rejestruj (KomendaIzotermiczne::ID, &KomendaIzotermiczne::kreator);

	// Wczytanie programu
	Komendy program;
	std::string linia;
	unsigned nr_linii = 0;
	unsigned liczba_bledow = 0;
	while (std::getline (plik_z_programem, linia))
	{
		++nr_linii;
		if (linia [0] == '#') continue;	// ignoruje linijki zaczynajace sie od krzyzyka (komentarze)
		Komenda *k = NULL;
		k = fk.utworz (linia);
		if (k)
			program.push_back (k);
		else
		{
			std::cerr << "Blad skladni w linii " << nr_linii << std::endl;
			++liczba_bledow;
		}
	}
	plik_z_programem.close ();
	if (liczba_bledow)	// konczy, gdy jest jakakolwiek bledna linijka
	{
		std::cerr << "Wystapily bledy w skladni programu: kontynuowanie jest niemozliwe!" << std::endl;
		return 1;
	}
	else
		std::cerr << "Program wczytany prawidlowo." << std::cerr;

	// Inicjuje ncurses i rysuje ekran
	ncurses_init ();
	rysuj_ramke (0, 0, SCREEN_W, SCREEN_H);
	init_pair (1, COLOR_RED, COLOR_BLACK);
	init_pair (2, COLOR_GREEN, COLOR_BLACK);
	attron (COLOR_PAIR(1) | A_BOLD);
	wypisz_tekst_srodek (SCREEN_W / 2, 0, " KONTROLER TEMPERATURY ");
	attroff (COLOR_PAIR(1) | A_BOLD);

	// Tworzy piec i kontrolke temperatury
	PiecDoswiadczalny piecyk (25.0);
	Komenda::ustawPiec (&piecyk);
	KolorowaKontrolkaTemperatury termometr (5, 5, 10, 5,  &piecyk, 2);
	piecyk.dodajObserwatora (&termometr);

	mvprintw (SCREEN_H - 4, 5, "Komenda:");

	// Oblicza i wyswietla calkowity czas trwania programu
	float czas = 0;
	for (Komendy::const_iterator it = program.begin(); it != program.end(); ++it)
		czas += (*it)->czasWykonania ();

	mvprintw (SCREEN_H - 2, 5, "Czas trwania programu: %.2f s", czas);
	refresh ();

	// Wykonuje kolejne komendy
	for (unsigned i = 0; i < program.size(); ++i)
	{
		mvprintw (SCREEN_H - 4, 15, "%u / %u", i+1, program.size ());
		refresh ();
		(*program [i]) ();
	}
		
	ncurses_deinit ();	// deinicjacja ncurses

	// Czyscy pamiec
	for (Komendy::iterator it = program.begin(); it != program.end(); ++it)
		delete *it;
	
	return 0;
}