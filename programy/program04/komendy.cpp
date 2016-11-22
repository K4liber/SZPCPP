#include "komendy.hpp"
#include <cmath>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <ctime>

Piec* Komenda::piec_;

void Komenda::ustawPiec (Piec *p)
{
	piec_ = p;
}

KomendaSkoczDo::KomendaSkoczDo (float temp) : skoczdo_ (temp) {}

float KomendaSkoczDo::czasWykonania ()
{
	return 0.0;
}

void KomendaSkoczDo::operator() ()
{
	piec_->setTemp (skoczdo_);
}

const boost::regex KomendaSkoczDo::ID ("skocz\\s(\\d+(\\.\\d+)?)");

Komenda *KomendaSkoczDo::kreator (const std::string &kom)
{
	boost::match_results<std::string::const_iterator> co;
	std::string::const_iterator start = kom.begin (), koniec = kom.end ();
	if (regex_search(start, koniec, co, ID))
	{
		float temp = boost::lexical_cast <float> (std::string (co [1].first, co[1].second));
		return new KomendaSkoczDo (temp);
	}
	else
		return NULL;
}

void FabrykaKomend::rejestruj (const boost::regex &id, kreator_komend kreat)
{
    // :-)
}

Komenda *FabrykaKomend::utworz (const std::string &kom)
{
    // :-)
    // Szuka, czy istnieje takie wyrazenie regularne, ktore pasuje do kom
    // Jesli tak, wola kreator danej klasy
    // Jesli nie, zwraca NULL
}