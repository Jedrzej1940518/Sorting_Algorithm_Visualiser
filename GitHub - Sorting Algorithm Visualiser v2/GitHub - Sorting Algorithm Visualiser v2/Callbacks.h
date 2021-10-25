#pragma once




#include <FL/Fl.H>
#include <FL/Fl_Group.H>

#include <string>

using namespace std;

void create_win(Fl_Widget*, void*);

void BasicCb(Fl_Widget* w, void* p);

void Popup(Fl_Group* prev, const char* msg);

string txt_inp(Fl_Group* prev, const char* label);
