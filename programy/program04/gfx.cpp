#include "gfx.hpp"

const int SCREEN_H = 20;
const int SCREEN_W = 40;

void ncurses_init ()
{
	initscr();
	cbreak ();
	noecho ();
	start_color();	
}

void ncurses_deinit ()
{
	endwin();
}

void rysuj_ramke (int x, int y, int w, int h)
{
	for (int i = x; i < x+w; ++i)
	{
		mvprintw (y, i, "*");
		mvprintw (y+h, i, "*");
	}
	for (int j = y; j < y+h; ++j)
	{
		mvprintw (j, x, "*");
		mvprintw (j, x+w, "*");
	}
}

void wypisz_tekst_srodek (int x, int y, const std::string &txt)
{
	mvprintw (y, x - txt.size () / 2, txt.c_str ());
}