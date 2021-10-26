#pragma once

#pragma warning (disable:4996)

#include <map>
#include <list>

#include <regex>

#include <iostream>

#include "Interpretter.h"
#include "regex_Fun.h"
#include "infinite_queue.h"

rf r{};//this is for matching regexes with funcitons
map<string, int> v;	//this hold ALL our variables 

int gotoctr = 0;

/////////////////////////////////////////////////////////////////////
/////////////////////// EVALUATE FUNCTIONS ///////////////////////

int evaluate_exp(string& a);	//takes string and returns int ie a = 5 * 2 + 1 returns 11
int calc(string& a);	//checks if an element in expressions is a member of map or just constant => i will return v[i], 5 will return 5
string ev_arr(string& a);	//takes a string and if it detects its an array will evaluate its index, ie array[2 * 3] returns array[5]

/////////////////////////////////////////////////////////////////////
/////////////////////// STRING FUNCTIONS///////////////////////

void between_s(string& a, string& b, string& p, const char* sep);	//p = I,J => a=I, b=J // assigns if two strings are between a coma
inline void divide_by_iter(string::iterator i, string& a, string& b, string& s); //divide string s to string a and b with iterator being the divido
string in_par(string& s); //returns string between () ex  s=(a) returns a
string remove_ws(string& s);	//returns string s without whitespaces
string::iterator find_skip_ar(string& s, char z);		//returns iterator to the char z in string s, as long as z is not between brackets => z == + => ar[i+2]-4-1-1+2 returns last plus sign 

/////////////////////////////////////////////////////////////////////
/////////////////////// CODE FUNCTIONS ///////////////////////

inf_que* prepare_code(list<string>& raw_code);		//taking a raw code and outputting prepared code
void match_lines(rf::rf::fc fr, rf::rf::fc nd, list<string>& raw_code);		//finding corresponding fr and nd lines and replacing them (with below functions)
void replace_lines(list<string>::iterator& Up, list <string>::iterator& Down, rf::fc arg, list<string>& raw_code);
void replace_whiles(list<string>::iterator& Up, list <string>::iterator& Down, list<string>& raw_code);		//takes whiles and outputes if nots and GOTOES
void replace_ifs(list<string>::iterator& Up, list <string>::iterator& Down, list<string>& raw_code); //takes ifs and outputes if nots and GOTOES

/////////////////////////////////////////////////////////////////////
/////////////////////// INTERPRET FUNCTIONS ///////////////////////

void interpret(inf_que& prepped_code, SoC& sc);		//executing our code

void assign(string& s);		//assignemtn and initialization
void swp(string& s, SoC& sc);	//swap
void nif(string& s, SoC& sc, inf_que& prepped_code);		//not if
void go(string& s, inf_que& prepped_code);		//go to

/////////////////////////////////////////////////////////////
/////////////////////// COMPARE FUNCTIONS ///////////////////////

bool comp_combine(string& s, SoC& sc);		//complex comparsions -> example: a>b && a<b
bool comp_all(string& s, SoC& sc);			//comp expressions ie: a+b>a+c
string comp_sign(string& a);	//returns compare operation a in given string ie 5 >= 1 will return >=

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

void useralgorithm(vector<int>& vc, SoC& sc, string& cd) {
	
	list<string> raw_code;

	char* buff = new char[20];

	sprintf(buff, "s = %d\n", vc.size());			//adding array size as s first
	
	string k = buff;

	raw_code.push_back(k);

	for (size_t i = 0; i < vc.size(); ++i) {	//adding array initializaiton 2nd
		sprintf(buff, "ar[%d] = %d\n",i,vc[i]);
		string k = buff;
		raw_code.push_back(k);
	}

	string h = "";

	for (auto p = cd.begin(); p != cd.end(); ++p) {
		
		if (*p == '\n') {	//seperating code line by line
			raw_code.push_back(h);
			h = "";
			continue;
		}
		else
		h += *p;

	}

	raw_code.push_back(h);

	inf_que* prepped_code = prepare_code(raw_code);

	interpret(*prepped_code, sc);

	delete[]buff;
	delete prepped_code;
	v.clear();
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

int evaluate_exp(string& ss) {	

	string a;
	string b;

	if (find_skip_ar(ss, '+') != ss.end()) {
		auto p = find_skip_ar(ss, '+');	//returns iterator for +
		divide_by_iter(p, a, b, ss);	//divides p{a + b} into {a} and {b}
		return evaluate_exp(a) + evaluate_exp(b);
	}
	else if (find_skip_ar(ss, '-') != ss.end()) {
		auto p = find_skip_ar(ss, '-');
		divide_by_iter(p, a, b, ss);
		return evaluate_exp(a) - evaluate_exp(b);
	}
	else if (find_skip_ar(ss, '*') != ss.end()) {
		auto p = find_skip_ar(ss, '*');
		divide_by_iter(p, a, b, ss);
		return evaluate_exp(a) * evaluate_exp(b);
	}
	else if (find_skip_ar(ss, '/') != ss.end()) {
		auto p = find_skip_ar(ss, '/');
		divide_by_iter(p, a, b, ss);
		return evaluate_exp(a) / evaluate_exp(b);
	}

	return calc(ss);	//calculates termns ie: "5" returns 5, a[2+1] returns the value inside a[3] 
}
int calc(string& a) {

	if (a == "")
		return 0;

	if (isdigit(a[0]))
		return stoi(a);

	return v[ev_arr(a)];

}
string ev_arr(string& s) {

	auto mtch = r.match(rf::fc::arry, s);

	if (!mtch.size())
		return s;

	string ss = mtch[2].str(); //this is inside the index ie ar[2+4] creates 2+4

	string res = mtch[1].str() + '[' + to_string(evaluate_exp(ss)) + ']';	//returns ar[evaluation(2+4)] => ar[6]

	return res;
}

void between_s(string& a, string& b, string& p, const char* sep) {

	int k = p.find(sep);

	a = p.substr(0, k);
	b = p.substr(k + strlen(sep), p.size() - k - strlen(sep));
}

inline void divide_by_iter(string::iterator i, string& a, string& b, string& s) {

	a = s.substr(0, i - s.begin());
	b = s.substr(i - s.begin() + 1, s.end() - i);

}
string in_par(string& s) {

	auto l = s.find('(');
	auto r = s.rfind(')');

	string cp = s.substr(l + 1, r - l - 1);

	return cp;
}
string remove_ws(string& s) {

	string ns = "";
	for (auto p = s.begin(); p != s.end(); ++p)
		if (!isspace(*p))
			ns += *p;

	return ns;
}
string::iterator find_skip_ar(string& s, char z) {

	auto p = s.begin();
	int cnt = 0;
	while (p != s.end() && *p != z) {

		while (cnt || (*p == '[')) {
			if (*p == '[')
				++cnt;

			++p;

			if (*p == ']')
				--cnt;
		}
		++p;
	}
	return p;
}

inf_que* prepare_code(list<string>& raw_code){	

	inf_que* prepped_code = new inf_que;

	for (auto p = raw_code.begin(); p != raw_code.end(); ++p)	//remove whitespaces from our code
		*p = remove_ws(*p);

	match_lines(rf::fc::lwhile, rf::fc::ewhile, raw_code);
	match_lines(rf::fc::ifstat, rf::fc::eif, raw_code);

	for (auto& p : raw_code)
		prepped_code->push(p);

	return prepped_code;
}

void match_lines(rf::fc fr, rf::fc nd, list<string>& raw_code) {

	int ctr = 0;
	for (auto p = raw_code.begin(); p != raw_code.end(); ++p) {	//this looks for the first instance of fc:: fr

		if (r.isThere(fr, *p)) {
			ctr++;

			for (auto k = p; 1;) {			//now we look for a matching fc:: nd

				++k;

				if (r.isThere(fr, *k))
					++ctr;

				else if (r.isThere(nd, *k))
					--ctr;

				if (ctr == 0) {
					replace_lines(p, k, fr, raw_code);
					break;
				}
			}
		}
	}
}

void replace_lines(list<string>::iterator& Up, list <string>::iterator& Down, rf::fc arg, list<string>& raw_code) {

	if (arg == rf::fc::ifstat)
		replace_ifs(Up, Down, raw_code);
	else
		replace_whiles(Up, Down, raw_code);

}
void replace_whiles(list<string>::iterator& Up, list <string>::iterator& Down, list<string>& raw_code) {

	raw_code.insert(Up, to_string(gotoctr));
	*Down = "goto" + to_string(gotoctr);

	string up = "NOTif(" + in_par(*Up) + ")";	//transforms while/if into NOTifs
	*Up = up;

	string gt = "goto" + to_string(gotoctr + 1);
	++Up;
	raw_code.insert(Up, gt);

	++Down;
	raw_code.insert(Down, to_string(gotoctr + 1));

	gotoctr += 2;

}
void replace_ifs(list<string>::iterator& Up, list <string>::iterator& Down, list<string>& raw_code) {

	string up = "NOTif(" + in_par(*Up) + ")";	//transforms while/if into NOTifs
	*Up = up;

	string gt = "goto" + to_string(gotoctr);
	++Up;
	raw_code.insert(Up, gt);

	++Down;
	raw_code.insert(Down, to_string(gotoctr));

	++gotoctr;
}

void interpret(inf_que& prepped_code, SoC& sc) {

	while (1) {

		string& s = prepped_code.take();

		int f = r(s);	//matching our instruction

		switch (f) {	

		case rf::assig:
			assign(s);
			break;

		case rf::swp:
			swp(s,sc);
			break;

		case rf::go:
			go(s,prepped_code);
			break;

		case rf::fc::nif:
			nif(s,sc,prepped_code);
			break;

		case rf::fc::end:
			return;
		}
	}

}

void assign(string& s) {

	string l;
	string r;

	between_s(l, r, s, "=");	//dziele a = k + b na a, k+b

	l = ev_arr(l);	//this calculates our variable name -> a[4+1] returns a[5]. i returns i
	int val = (evaluate_exp(r));

	v[l] = val;

}
void swp(string& s, SoC& sc) {

	string p = in_par(s);		//returns value in () so swap(a[1],a[2]) returns string a[1],a[2]

	string a;
	string b;

	between_s(a, b, p, ",");	//seperates string p into A and B -> ',' is our seperator

	a = ev_arr(a);
	b = ev_arr(b);

	int h = v[a];
	v[a] = v[b];
	v[b] = h;
	//below checks if we have 2 arrays in swap -> if we do, we put their indexes in SoC
	if (r.isThere(rf::fc::isarry, a) && r.isThere(rf::fc::isarry, b)) {

		smatch k = r.match(rf::fc::arry, a);
		string A = k[2];
		int i = stoi(A);

		smatch s = r.match(rf::fc::arry, b);
		string B = s[2];
		int j = stoi(B);

		sc.push_back({ {i,j }, 0 });

	}
}

void nif(string& s, SoC& sc, inf_que& prepped_code) {

	string cmp = in_par(s);

	if (!comp_combine(cmp,sc))
		return;
	else {
		//prepped_code.take();
		prepped_code.take();	//we skip a code line if NOTIF is false
	}

}
void go(string& s, inf_que& prepped_code) {

	auto p = r.match(rf::fc::go, s);
	string flg = p[1];	//this is our go to flag

	while (prepped_code.take() != flg);		//finding flag
}

bool comp_combine(string& par, SoC& sc)	//takes input from () so (1>2) should pass 1>2, (1>2 && 2>1) should send 1>2 && 2>1
{
	string a;
	string b;

	if (par.find("&&") != string::npos) {

		between_s(a, b, par, "&&");
		return comp_combine(a, sc) && comp_combine(b,sc);

	}
	else if (par.find("||") != string::npos) {

		between_s(a, b, par, "||");
		return comp_combine(a,sc) || comp_combine(b,sc);

	}
	else

		return comp_all(par, sc);
}
bool comp_all(string& par, SoC& sc) {	//takes inpt from between () so while(1>2) should send here 1>2

	string z = comp_sign(par);

	string a;
	string b;

	between_s(a, b, par, z.c_str());	//asigns to a and b strings from string par between a char z

	if (r.isThere(rf::fc::isarry, a) && r.isThere(rf::fc::isarry, b)) {

		smatch k = r.match(rf::fc::arry, a);
		string A = k[2];
		int i = evaluate_exp(A);

		smatch s = r.match(rf::fc::arry, b);
		string B = s[2];
		int j = evaluate_exp(B);

		sc.push_back({ {i,j }, 1 });

	}

	if (z == ">=")
		return evaluate_exp(a) >= evaluate_exp(b);
	else if (z == "<=")
		return evaluate_exp(a) <= evaluate_exp(b);
	else if (z == "==")
		return evaluate_exp(a) == evaluate_exp(b);
	else if (z == "!=")
		return evaluate_exp(a) != evaluate_exp(b);
	else if (z == ">")
		return evaluate_exp(a) > evaluate_exp(b);
	else if (z == "<")
		return evaluate_exp(a) < evaluate_exp(b);

	return 0;
}
string comp_sign(string& a) {

	string z = "";

	if (a.find(">=") != string::npos)
		z = ">=";
	else if (a.find("<=") != string::npos)
		z = "<=";
	else if (a.find('<') != string::npos)
		z = "<";
	else if (a.find('>') != string::npos)
		z = ">";
	else if (a.find('!') != string::npos)
		z = "!=";
	else if (a.find('=') != string::npos)
		z = "==";

	return z;

}