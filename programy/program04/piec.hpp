#ifndef _piec_hpp_
#define _piec_hpp_

#include "kontrolka_temperatury.hpp"
#include <vector>

class KontrolkaTemperatury;

class Piec	// abstrakcyjna klasa bazowa
{
	public:
		explicit Piec (float temperatura);	// przypisuje temperature poczatkowa pieca
		virtual ~Piec () {}
		void dodajObserwatora (KontrolkaTemperatury* obs);	// dodaje obserwatora do listy
		virtual void setTemp (float temperatura) = 0;	// ustawia temperature pieca
		virtual float getTemp () const = 0;	// zwraca temperature pieca
	protected:
		void powiadom ();	// powiadamia wszystkich obserwatorow o zmianie stanu
		float temperatura_;	// przechowuje temperature pieca
		std::vector <KontrolkaTemperatury*> obserwatorzy_;	// wektor obserwatorow pieca
};

class PiecDoswiadczalny : public Piec
{
	public:
		explicit PiecDoswiadczalny (float temperatura);	// przypisuje temperature poczatkowa pieca
		virtual ~PiecDoswiadczalny () {}
		virtual void setTemp (float temperatura);	// ustawia temperature pieca
		virtual float getTemp () const;	// zwraca temperature pieca
};


#endif