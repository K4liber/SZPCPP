#include "kontrolka_temperatury.hpp"
#include "gfx.hpp"

KontrolkaTemperatury::KontrolkaTemperatury (int x, int y, int w, int h, Piec *p) :
	x_ (x), y_ (y), w_ (w), h_ (h), p_ (p)
{
	rysuj_ramke (x_, y_, w_, h_);
}

KolorowaKontrolkaTemperatury::KolorowaKontrolkaTemperatury (int x, int y, int w, int h,  Piec *p, int color_pair) :
	KontrolkaTemperatury (x, y, w, h, p), color_pair_ (color_pair)
{
	odswiez ();
}

void KolorowaKontrolkaTemperatury::odswiez ()
{
	attron (COLOR_PAIR(color_pair_));
	mvprintw (y_+2, x_+2, "%.2f", p_->getTemp ());
	attroff (COLOR_PAIR(color_pair_));
	refresh ();
}