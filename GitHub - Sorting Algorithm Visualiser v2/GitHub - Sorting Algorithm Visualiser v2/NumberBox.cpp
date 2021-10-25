
#pragma once

#include "NumberBox.h"

#pragma warning (disable: 4996)

NumberBox::NumberBox(int x, int y, int Side, int Value, Fl_Color Col) : Fl_Box(x, y, Side, Side), side{ Side }, val{ Value }, outline{ Col } {

	char* k = new char[MX_LEN];
	ch = k;

	sprintf(k, "%d", Value);

	label(k);

	box(FL_FLAT_BOX);
	labelsize(side / 2);

	r = 255 - Value * 10;
	b = r;
	g = 255;

}

NumberBox::~NumberBox() {

	delete[]ch;

}

vector<NumberBox*> NumberBox::NboxLn(int x, int y, int width, vector<int>& p) {

	vector<NumberBox*> vec;
	

	int s = width/p.size(); 
	int pos = x;


	for (int i = 0; i < p.size(); ++i) {
		
		NumberBox* n = new NumberBox(pos, y, s, p[i],FL_BLACK);
		pos += s;
		vec.push_back(n);
	}

	return vec;

}

void NumberBox::draw() {


	fl_rectf(x(), y(), side, side, r, g, b);
	fl_color(FL_BLACK);
	fl_font(FL_HELVETICA, side / 2);
	fl_draw(label(), x(), y(),side,side,FL_ALIGN_INSIDE);
	fl_rect(x(), y(), side, side, outline);
	fl_rect(x()+1, y()+1, side, side, outline);


}

int NumberBox::s() {
	return side;
}

void NumberBox::ol(Fl_Color f) {

	outline = f;

}