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
KomendaRampa::KomendaRampa (float tempStart, float tempStop, float speed) : 
	tempStart (tempStart), tempStop (tempStop), speed (speed) {}
KomendaIzotermiczne::KomendaIzotermiczne (float time) : wygrzewaj_ (time) {}

float KomendaSkoczDo::czasWykonania ()
{
	return 0.0;
}

void KomendaSkoczDo::operator() ()
{
	piec_->setTemp (skoczdo_);
}

float KomendaRampa::czasWykonania ()
{
	return ((tempStop - tempStart) > 0 ? (tempStop - tempStart)/speed : (tempStart - tempStop)/speed);
}

void KomendaRampa::operator() ()
{
	piec_->setTemp (tempStart);
	float tempActual = tempStart;
	if(speed > ((tempStop - tempStart) > 0 ? (tempStop - tempStart) : (tempStart - tempStop)))
		piec_->setTemp (tempStop);
	else if (tempStop > tempStart) {
		while (tempActual < tempStop) {
			sleep(1);
			tempActual+=speed;
			if(tempActual < tempStop)
				piec_->setTemp (tempActual);
		}
	}
	else if (tempStop < tempStart) {
		while (tempActual > tempStop) {
			sleep(1);
			tempActual-=speed;
			if(tempActual > tempStop)
				piec_->setTemp (tempActual);
		}
	}
	piec_->setTemp (tempStop);
}

float KomendaIzotermiczne::czasWykonania ()
{
	return wygrzewaj_;
}

void KomendaIzotermiczne::operator() ()
{
	sleep(wygrzewaj_);
}

const boost::regex KomendaSkoczDo::ID ("skocz\\s(\\d+(\\.\\d+)?)");
const boost::regex KomendaRampa::ID ("rampa\\s(\\d+(\\.\\d+)?)\\s(\\d+(\\.\\d+)?)\\s(\\d+(\\.\\d+)?)");
const boost::regex KomendaIzotermiczne::ID ("izotermiczne\\s(\\d+(\\.\\d+)?)");

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

Komenda *KomendaRampa::kreator (const std::string &kom)
{
	boost::match_results<std::string::const_iterator> co;
	std::string::const_iterator start = kom.begin (), koniec = kom.end ();
	if (regex_search(start, koniec, co, ID))
	{
		float tempStart = boost::lexical_cast <float> (std::string (co [1].first, co[1].second));
		float tempStop = boost::lexical_cast <float> (std::string (co [3].first, co[3].second));
		float speed = boost::lexical_cast <float> (std::string (co [5].first, co[5].second));
		std::cout<<tempStart<<"\t"<<tempStop<<"\t"<<speed<<std::endl;
		return new KomendaRampa (tempStart, tempStop, speed);
	}
	else
		return NULL;
}

Komenda *KomendaIzotermiczne::kreator (const std::string &kom)
{
	boost::match_results<std::string::const_iterator> co;
	std::string::const_iterator start = kom.begin (), koniec = kom.end ();
	if (regex_search(start, koniec, co, ID))
	{
		float time = boost::lexical_cast <float> (std::string (co [1].first, co[1].second));
		return new KomendaIzotermiczne (time);
	}
	else
		return NULL;
}

void FabrykaKomend::rejestruj (const boost::regex &id, kreator_komend kreat)
{
    komendy[id] = kreat;
}

Komenda *FabrykaKomend::utworz (const std::string &kom)
{
	typedef std::map <boost::regex, kreator_komend>::iterator it_type;
	for(it_type iterator = komendy.begin(); iterator != komendy.end(); iterator++) {
		boost::match_results<std::string::const_iterator> co;
		std::string::const_iterator start = kom.begin (), koniec = kom.end ();
		if (regex_search(start, koniec, co, iterator->first))
			return iterator->second(kom);
	}
	return NULL;
    // :-)
    // Szuka, czy istnieje takie wyrazenie regularne, ktore pasuje do kom
    // Jesli tak, wola kreator danej klasy
    // Jesli nie, zwraca NULL
}
