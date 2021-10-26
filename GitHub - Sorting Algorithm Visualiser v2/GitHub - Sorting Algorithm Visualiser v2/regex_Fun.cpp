#pragma once

#include "regex_Fun.h"

int rf::operator()(const string& s) {

	smatch mtch;
	for (int i = 0; i < NOF; ++i) {
		regex_search(s, mtch, func[i]);
		if (mtch.size())
			return i;
	}

	return -1;
}

bool rf::isThere(fc n, const string& s) {

	if (s.size() == 0)
		return 0;

	smatch mtch;
	regex_search(s, mtch, func[n]);

	return mtch.size();
}

smatch rf::match(fc n, const string& s) {
	smatch mtch;
	regex_search(s, mtch, func[n]);
	return mtch;
}

rf::rf() {

	func[assig] = "[^=!]={1}[^=]";

	func[lwhile] = "^(?!end)(while)";
	func[ewhile] = "(endwhile)";

	func[ifstat] = "^(?!end)(if)";
	func[eif] = "(endif)";

	func[swp] = "swap";

	func[isarry] = "\\[";
	func[arry] = "([A-Za-z0-9]+)\\[([A-Za-z\\+\\-*\\/0-9\\s]+)\\]";		//ar[1+3*4] -> smatch[1] => ar, smatch[2] => 1+3*4

	func[go] = "goto([0-9]+)";
	func[nif] = "NOTif";
	func[end] = "endprogram";
}