#pragma once


#include "ConstNumbers.h"
#include "Callbacks.h"
#include "Labels.h"

#include <FL/Fl.H>
#include <FL/Fl_Menu_Window.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>

#include <FL/Fl_Input.H>

int main() {


	Fl_Menu_Window men (WIN_W / 2, WIN_H / 2, MNU_W,MNU_H, "Menu");

	Fl_Choice ar_len(MNU_W / 2, 0, CH_W, CH_H, "Array ");
	ar_len.add(rn10, "", NULL);
	ar_len.add(rn20, "", NULL);
	ar_len.add(rnUI,"", NULL);

	Fl_Choice srt_algo(MNU_W / 2, CH_H, CH_W, CH_H, "Sorting Algorithm");
	srt_algo.add(QS, "", NULL);
	srt_algo.add(IS, "", NULL);
	srt_algo.add(UA, "", NULL);


	Fl_Button strt(MNU_W * 0.7, MNU_H * 0.9, BTN_W, BTN_H, "Confirm");
	strt.callback(create_win, (void*)(men.array()));

	men.show();

	return Fl::run();

}