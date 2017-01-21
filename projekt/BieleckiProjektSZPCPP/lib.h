#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <fstream>
#include <vector>
#include <allegro.h>
#include <math.h>
#include <iostream>
#include <map>

struct Prosta {
	
	float a;
	float b;
	int x1;
	int x2;
	bool isLeaf;
	
};

struct Polozenie {
	
	Polozenie() {}
	Polozenie( int xx, int yy )
        :x(xx), y(yy)
    {}
	int x;
	int y;
	
};

struct Parametry {
	
	int N;
    int listkow;
    int leafSize;
    int korzeni;
    int korzenSize;
    bool automatic;
    int generations;
	float cks;
	float ckp;
	float cls;
	float clp; 
	
};

bool keyrel(int k);
void drawInfo(BITMAP * diagram, int toDraw, float value, int generationNr,
		float average, float max);
void init(BITMAP *diagram);
void deinit(BITMAP *diagram);

#endif
