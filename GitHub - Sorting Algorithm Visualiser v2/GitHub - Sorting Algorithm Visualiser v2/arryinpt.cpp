
#include "arryinpt.h";
#include "ConstNumbers.h"

#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Button.H>

#include <iostream>


void string_to_vec(string& p, vector<int>& vc) {

	auto i = p.begin();

	string k = "";

	while (i != p.end() && *i != ';') {

		if (*i >= 48 && *i <= 57)	//adding nubmers
			k += *i;
		else if (*i == ',') {		//',' seperetes numbers

			if (k == "") {
				++i;
				continue;
			}
			vc.push_back(stoi(k));
			k = "";
		}

		++i;
	}

	if(k!="")
	vc.push_back(stoi(k));
}

void arry_inp(vector<int>& vc, Fl_Group* prev) {

	Popup(prev, "Input coma seperated values ending with ';'\nExample: 1,2,3,4;");

	string k = txt_inp(prev, "Input Array");
	string_to_vec(k, vc);

	if (vc.size() > 40 || vc.size() < 3) {
		cerr << "ERROR! ARRAY SIZE >40";
		exit(1);
	}

	for (auto& p : vc)
		if (p > 99) {
			cerr << "ERROR! INPUT NUMBER >99";
			exit(1);
		}
}