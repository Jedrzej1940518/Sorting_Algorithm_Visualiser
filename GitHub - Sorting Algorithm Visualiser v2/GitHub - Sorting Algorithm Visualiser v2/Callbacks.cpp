
#pragma once

#include "Callbacks.h"
#include "Moving.h"
#include "ConstNumbers.h"
#include "NumberBox.h"
#include "SortingAlgo.h"
#include "arryinpt.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Multiline_Input.H>

#include <random>
#include <string>
#include <iostream>

void Popup(Fl_Group* prev, const char* msg) {

	Fl_Group::current(NULL);

	Fl_Window popup(MNU_W * 1.5, MNU_H / 4, "PopUp");
	Fl_Box txt(0, 0, MNU_W * 1.5, MNU_H / 4, msg);
	Fl_Button ok(MNU_W * 1.5 - BTN_W - 10, MNU_H / 4 - BTN_H - 10, BTN_W, BTN_H, "Ok");
	popup.show();
	bool b = 0;
	ok.callback(BasicCb, &b);

	while (b == 0)
		Fl::wait();


}

void BasicCb(Fl_Widget* w, void* p) {

	bool* k = (bool*)p;

	*k = 1;
}

string txt_inp(Fl_Group* prev, const char* label) {

	Fl_Group::current(NULL);
	Fl_Window* win = new Fl_Window(0, 0, MNU_W, MNU_H, label);

	Fl_Multiline_Input* inpt = new Fl_Multiline_Input(MNU_W / 4, MNU_H / 4, MNU_W / 2, BTN_H * 3);

	bool k = 0;

	Fl_Button* acc = new Fl_Button(MNU_W - BTN_W - 10, MNU_H - BTN_H - 10, BTN_W, BTN_H, "Accept");
	acc->callback(BasicCb, &k);


	win->show();

	while (k == 0)
		Fl::wait();

	string p = inpt->value();

	Fl_Group::current(prev);
	delete win;

	return p;

}

void windowCB(Fl_Widget* widget, void*) {

	Fl_Double_Window* win = (Fl_Double_Window*)widget;

	win->hide();

	Fl::remove_timeout(CompCb);
	Fl::remove_timeout(SwpCb);

	STATIC_S = 0;

	if (CALLING.nb)
		for (auto& p : *CALLING.nb)
			delete p;

	delete CALLING.nb;
	delete CALLING.sc;
	delete win;

}

inline vector<int> rand_vec(int min, int max, int sz) {

	vector<int>vec;
	
	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<mt19937::result_type> dist(min, max);
	
	for (int i = 0; i < sz; ++i)
		vec.push_back(dist(rng));

	return vec;
}

void create_arr(const char*k, vector<int>& vc, Fl_Group* pr) {

	int sz = 0;

	if (strcmp(k, rn10) == 0)
		vc = rand_vec(1, 10, 10);
	else if (strcmp(k, rn20) == 0)
		vc = rand_vec(1, 20, 20);
	else if (strcmp(k, rnUI) == 0)
		arry_inp(vc, pr);

}

void sort_arr(const char* k, vector<int>& vc, SoC* sc, Fl_Group* pr) {


	if (strcmp(k, QS) == 0)
		QuickSort(vc, *sc, 0, vc.size() - 1);
	else if (strcmp(k, IS) == 0)
		InsertSort(vc, *sc);
	else if (strcmp(k, UA) == 0) {
	
		Popup(pr, "Consult Sorting Algorithm Interpreter documentation");
		string p = txt_inp(pr, "Input code");
		UserAlgorithm(vc, *sc, p);

	}
}

void visualise_seq(const char* k, vector<NumberBox*>* nb, SoC* sc, Fl_Double_Window* w) {

	AnimateSeq(nb, w, sc);

}

void create_win(Fl_Widget* gr, void* dt) {
	 
	Fl_Double_Window* win = new Fl_Double_Window(WIN_W, WIN_H, "Sorting Algorithm Visualiser");

	auto p = (Fl_Choice* const*)dt;
	//p[0] -> arr len p[1] -> srt algo

	const char* arry_inpt = p[0]->text();		
	
	vector<int> vc;		//vector that we will fill

	create_arr(arry_inpt, vc, win);

	vector<NumberBox*>* nb = new vector<NumberBox*>;

	*nb = NumberBox::NboxLn(MRG, WIN_H / 2, WIN_W - MRG * 2, vc);

	const char* sort_meth = p[1]->text();

	SoC* opr = new SoC;

	sort_arr(sort_meth, vc, opr, win);

	win->show();
	win->callback(windowCB);

	visualise_seq(sort_meth, nb, opr, win);
}
