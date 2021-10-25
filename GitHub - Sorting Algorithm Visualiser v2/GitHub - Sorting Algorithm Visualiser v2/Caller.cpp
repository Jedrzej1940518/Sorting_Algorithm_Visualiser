
#include "Caller.h"



Caller::Caller(vector<NumberBox*>* p, Fl_Double_Window* win, SoC* s) : nb{ p }, w{ win }, sc{ s }{}

Caller::Caller() {}

void Caller::operator()() {
	AnimateSeq(nb, w, sc);
}