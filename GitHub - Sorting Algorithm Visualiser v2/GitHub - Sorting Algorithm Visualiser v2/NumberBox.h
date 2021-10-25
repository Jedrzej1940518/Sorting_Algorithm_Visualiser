#pragma once

#include "ConstNumbers.h"

#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>

#include <vector>

using namespace std;

class NumberBox: public Fl_Box {

public:

	void draw();

	NumberBox(int x, int y, int Side, int Value, Fl_Color Col);
	~NumberBox();

	static vector<NumberBox*> NboxLn(int x, int y, int width, vector<int>& p);

	int s();
	void ol(Fl_Color f);

private:


	int side;
	int val;
	Fl_Color outline;
	
	int r;
	int g;
	int b;

	char* ch;
	
};
