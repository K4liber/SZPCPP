#ifndef _kontrolka_temperatury_hpp_
#define _kontrolka_temperatury_hpp_

#include "piec.hpp"

class Piec;

class KontrolkaTemperatury	// abstrakcyjna klasa bazowa
{
	public:
		KontrolkaTemperatury (int x, int y, int w, int h, Piec *p);
		virtual ~KontrolkaTemperatury () {}
		virtual void odswiez () = 0;

	protected:
		int x_;
		int y_;
		int w_;
		int h_;
		Piec *p_;
};

class KolorowaKontrolkaTemperatury : public KontrolkaTemperatury
{
	public:
		KolorowaKontrolkaTemperatury (int x, int y, int w, int h,  Piec *p, int color_pair);
		virtual ~KolorowaKontrolkaTemperatury () {};
		virtual void odswiez ();	// odczytuje wynik z zaobserwowanego pieca i wyswietla
		
	private:
		int color_pair_;
};
#endif