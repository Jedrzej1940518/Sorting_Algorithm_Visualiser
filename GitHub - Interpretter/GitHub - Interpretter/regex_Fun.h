#pragma once

#include <regex>

using namespace std;

regex ASSIGNMENT("[^=!]={1}[^=]");		

regex LOOP_WHILE("^(?!end)(while)");
regex END_WHILE("(endwhile)");

regex IF_STATEMENT("^(?!end)(if)");
regex END_IF("(endif)");

regex IS_ARRY("\\[");
regex ARRY("([A-Za-z0-9]+)\\[([A-Za-z\\+\\-*\\/0-9\\s]+)\\]");	//group 1 is arry name, group 2 is arry index inside the brackets - abc[1+i] -> abc, i+1

regex SWAP("swap");

regex GOTO("goto([0-9]+)");
regex NIF("NOTif");

regex END("endprogram");
																//
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

	int operator()(const string& s) {

		smatch mtch;
		for (int i = 0; i < NOF; ++i) {
			regex_search(s, mtch, func[i]);
			if (mtch.size())
				return i;
		}

		return -1;
	}
	bool isThere(fc n,const string& s) {
		
		if (s.size() == 0)
			return 0;

		smatch mtch;
		regex_search(s, mtch, func[n]);

		return mtch.size();
	}
	auto match(fc n, const string& s) {
		smatch mtch;
		regex_search(s, mtch, func[n]);
		return mtch;
	}

private:

	regex func[NOF];

};

rf::rf() {

	func[assig] = ASSIGNMENT;
	
	func[lwhile] = LOOP_WHILE;
	func[ewhile] = END_WHILE;
	
	func[ifstat] = IF_STATEMENT;
	func[eif] = END_IF;

	func[swp] = SWAP;
	
	func[isarry] = IS_ARRY;
	func[arry] = ARRY;

	func[go] = GOTO;
	func[nif] = NIF;
	func[end] = END;
}