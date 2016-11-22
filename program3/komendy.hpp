#ifndef _komendy_hpp_
#define _komendy_hpp_
#include <boost/regex.hpp>

#include "piec.hpp"

class Komenda
{
	public:
		virtual void operator() () = 0;	// wywoluje komende
		virtual float czasWykonania () = 0;	// zwraca (oszacowany) czas wykonania komendy
		static void ustawPiec (Piec *p);	// ustawia statyczny wskaznik piec_
	protected:
		static Piec *piec_;	// wskazuje na piec, ktorym sterowac beda wszystkie komendy
};

typedef std::vector <Komenda*> Komendy;	// wektor przechowujacy komendy (wskazniki)

class KomendaSkoczDo : public Komenda	// skacze natychmiast do zadanej temperatury
{
	public:
		KomendaSkoczDo (float temp);
		virtual void operator() () ;
		virtual float czasWykonania ();
		static const boost::regex ID;
		static Komenda *kreator (const std::string &kom);
	private:
		float skoczdo_;
};

class KomendaIzotermiczne : public Komenda	// utrzymuje temperature przez okreslona liczbe sekund
{
    public:
		KomendaIzotermiczne (float time);
		virtual void operator() () ;
		virtual float czasWykonania ();
		static const boost::regex ID;
		static Komenda *kreator (const std::string &kom);
	private:
		float wygrzewaj_;
};

class KomendaRampa : public Komenda	// jednostajnie zwieksza (lub zmniejsza) temperature od tp do tk z okreslona szybkoscia
{
    public:
		KomendaRampa (float tempStart, float tempStop, float speed);
		virtual void operator() () ;
		virtual float czasWykonania ();
		static const boost::regex ID;
		static Komenda *kreator (const std::string &kom);
	private:
		float tempStart;
		float tempStop;
		float speed;
};

typedef Komenda* (*kreator_komend) (const std::string &kom);

class FabrykaKomend	// tworzy komendy za pomoca dopasowania wyrazenia regularnego
{
	public:
		void rejestruj (const boost::regex &id, kreator_komend kreat);
		Komenda *utworz (const std::string &kom);
	private:
		std::map <boost::regex, kreator_komend> komendy;
};

#endif
