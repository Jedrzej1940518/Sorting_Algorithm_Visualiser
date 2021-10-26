#pragma once

#include <string>
#include <regex>

using namespace std;

constexpr int NOF = 11;		//number of regexes/functions

struct rf {
	

	rf();

	enum fc {

		go,
		nif,
		assig,
		swp,
		end,

		lwhile,
		ewhile,

		ifstat,
		eif,

		arry,
		isarry,

	};

	int operator()(const string& s);			//matches string s with the right rf::fc

	bool isThere(fc n, const string& s);	//shows if fc n is in string&s

	smatch match(fc n, const string& s);

private:

	regex func[NOF];

};

