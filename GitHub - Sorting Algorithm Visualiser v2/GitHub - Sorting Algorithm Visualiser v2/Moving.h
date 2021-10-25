#pragma once

#include "NumberBox.h"
#include "Caller.h"

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

extern Caller CALLING;

extern int STATIC_S;

typedef vector<pair<pair<int, int>, bool>> SoC; // swap or Comparsion-> bool = 0 -> swap, bool = 1, comp

void AnimateSeq(vector<NumberBox*>* nb, Fl_Double_Window* w, SoC* sc);

void SwpCb(void* v);
void CompCb(void* v);