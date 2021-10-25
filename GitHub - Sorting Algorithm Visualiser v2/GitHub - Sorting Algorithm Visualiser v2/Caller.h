#pragma once

#include  "NumberBox.h"
#include <FL/Fl_Double_Window.H>

/// 
///	Used for calling next steps of animation
/// 

struct Caller {

	vector<NumberBox*>* nb;
	Fl_Double_Window* w;
	SoC* sc;

	Caller(vector<NumberBox*>* p, Fl_Double_Window* win, SoC* s);

	Caller();

	void operator()();

};

extern void AnimateSeq(vector<NumberBox*>* nb, Fl_Double_Window* w, SoC* sc);