#ifndef _dane_stat_hpp_
#define _dane_stat_hpp_
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class DaneStat
{
	public:
		// klasa bazowa
		DaneStat (const std::string &nazwa);
		// zwraca referencje na przechowywane dane
		virtual const std::vector <float> &dane () const = 0;
		virtual ~DaneStat () {};
		virtual const std::string &nazwa () const;
		virtual std::vector <float> & wczytajDane();
		// zwraca nazwe pliku
	protected:
		std::string nazwa_; // nazwa pliku
};

// proxy - wczytuje prawdziwy obiekt przy pierwszym użyciu
class DaneStatProxy : public DaneStat
{
	private:
		DaneStat *dane_;
	public:
		DaneStatProxy (const std::string &nazwa);
		virtual const std::vector <float> &dane () const;
		std::vector <float> &wczytajDane();
};

// "prawdziwy" obiekt przechowujacy dane
class DaneStatReal : public DaneStat
{
	private:
		std::vector <float> vectorData;
	public:
		DaneStatReal (const std::string &nazwa);
		virtual const std::vector <float> &dane () const;
		std::vector <float> & wczytajDane();
};

#endif
