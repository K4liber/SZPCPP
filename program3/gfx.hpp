#ifndef _gfx_hpp_
#define _gfx_hpp_

#include <ncurses.h>
#include <string>
#include <unistd.h>

extern const int SCREEN_H;
extern const int SCREEN_W;

void ncurses_init ();
void ncurses_deinit ();
void rysuj_ramke (int x, int y, int w, int h);
void wypisz_tekst_srodek (int x, int y, const std::string &txt);

#endif
