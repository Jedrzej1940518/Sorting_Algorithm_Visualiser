#pragma once

#include <map>
#include <string>
#include <vector>
#include <list>

#include <regex>

#include <iostream>


#include "regex_Fun.h"
#include "infinite_queue.h"

#define ISSTREAM cin

using namespace std;

map<string, int> v;	//this hold ALL our variables 

rf r{};//this is for matching regexes with funcitons

list<string> code;	//this hold ALL our raw code
inf_que prepped_code;	//this is an already preperred code with random access iterator

int gotoctr = 0;

/////////////////////////////////////////////////////////////////////
/////////////////////// EVALUATE FUNCTIONS ///////////////////////

int evaluate_exp(string& a);	//takes string and returns int ie a = 5 * 2 + 1 returns 11
int calc(string& a);	//checks if an element in expressions is a member of map or just constant => i will return v[i], 5 will return 5
string ev_arr(string& a);	//takes a string and if it detects its an array will evaluate its index, ie array[2 * 3] returns array[5]

/////////////////////////////////////////////////////////////////////
/////////////////////// STRING FUNCTIONS///////////////////////

void between_s(string& a, string& b, string& p, char s);	//p = I,J => a=I, b=J // assigns if two strings are between a coma
inline void divide_by_iter(string::iterator i, string& a, string& b, string& s); //divide string s to string a and b with iterator being the divido
string in_par(string& s); //returns string between () ex  s=(a) returns a
string remove_ws(string& s);	//returns string s without whitespaces
string::iterator find_skip_ar(string& s, char z);		//returns iterator to the char z in string s, as long as z is not between brackets => z == + => ar[i+2]-4-1-1+2 returns last plus sign 

/////////////////////////////////////////////////////////////////////
/////////////////////// CODE FUNCTIONS ///////////////////////

void prepare_code();
void match_lines(rf::fc fr, rf::fc nd);
void replace_lines(list<string>::iterator& Up, list <string>::iterator& Down, rf::fc arg);
void replace_whiles(list<string>::iterator& Up, list <string>::iterator& Down);
void replace_ifs(list<string>::iterator& Up, list <string>::iterator& Down);

/////////////////////////////////////////////////////////////////////
/////////////////////// INTERPRET FUNCTIONS ///////////////////////

void interpret();

void assign(string& s);
void swp(string& s);
void nif(string& s);
void go(string& s);

/////////////////////////////////////////////////////////////
/////////////////////// COMPARE FUNCTIONS ///////////////////////

bool comp_combine(string& s);
bool comp_all(string& s);
string comp_sign(string& a);	//returns compare sign in given string ie 5 > 1 will return >

/////////////////////////////////////////////////////////////




int main() {


	string s = "";
	
	while (s != "end program") {
		getline(ISSTREAM, s);
		code.push_back(s);
	}

	prepare_code();

	interpret();

	cout << "\nProgram ended. Variables are now equal to:\n";

	for (auto& p : v)
		cout << p.first << "= " << p.second << endl;


}

   
int evaluate_exp(string& ss) {

	string a;
	string b;

	if (find_skip_ar(ss, '+') != ss.end()) {
		auto p = find_skip_ar(ss, '+');
		divide_by_iter(p, a, b, ss);
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

	return calc(ss);
}
int calc(string& a) {

	if (isdigit(a[0]))
		return stoi(a);

	return v[ev_arr(a)];

}
string ev_arr(string& s) {

	auto mtch = r.match(rf::fc::arry, s);

	if (!mtch.size())
		return s;
	
	string ss = mtch[2].str(); //this is inside the index ie ar[2+4] creates 2+4
	
	string res= mtch[1].str()+'['+to_string(evaluate_exp(ss))+']';	//returns ar[evaluation(2+4)] => ar[6]

	return res;
}

void between_s(string& a, string& b, string& p, const char* sep) {

	int k = p.find(sep);

	a = p.substr(0, k);
	b = p.substr(k+strlen(sep), p.size()-k-strlen(sep));
}	   

/////CHECK/////CHECK

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
	while (p != s.end()&& *p != z) {
		
		while (cnt|| (*p =='[')) {
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

void prepare_code() {

	for (auto p = code.begin(); p!=code.end(); ++p)
		*p= remove_ws(*p);

	match_lines(rf::fc::lwhile, rf::fc::ewhile);
	match_lines(rf::fc::ifstat, rf::fc::eif);

	for (auto& p : code)
		prepped_code.push(p);

}

void match_lines(rf::fc fr, rf::fc nd) {
	int Up = 0;
	int Dwn = code.size();
	for (auto p = code.begin(); p != code.end(); ++p) {

		if (r.isThere(fr, *p)) {

			for (auto k = code.end(); k != p;) {
				
				--k;

				if (r.isThere(nd, *k)) {
					replace_lines(p, k, fr);
					Dwn = code.size();
					break;
				}
					Dwn--;
			}
		}

		Up++;
	}

}
void replace_lines(list<string>::iterator& Up, list <string>::iterator& Down, rf::fc arg) {

	if(arg== rf::fc::ifstat)
	replace_ifs(Up, Down);
	else
	replace_whiles(Up, Down);

}
void replace_whiles(list<string>::iterator& Up, list <string>::iterator& Down) {

	code.insert(Up, to_string(gotoctr));
	*Down = "goto" + to_string(gotoctr);
	
	string up = "NOTif(" + in_par(*Up) + ")";	//transforms while/if into ifs
	*Up = up;

	string gt = "goto" + to_string(gotoctr + 1);
	++Up;
	code.insert(Up, gt);

	++Down;
	code.insert(Down, to_string(gotoctr + 1));

	gotoctr += 2;

}
void replace_ifs(list<string>::iterator& Up, list <string>::iterator& Down) {

	string up = "NOTif(" + in_par(*Up) + ")";	//transforms while/if into ifs
	*Up = up;

	string gt = "goto" + to_string(gotoctr);
	++Up;
	code.insert(Up, gt);

	++Down;
	code.insert(Down, to_string(gotoctr));

	++gotoctr;
}

void interpret() {

	while (1) {

		string& s = prepped_code.take();

		int f = r(s);

		switch (f) {

		case rf::assig:
			assign(s);
			break;

		case rf::swp:
			swp(s);
			break;

		case rf::go:
			go(s);
			break;

		case rf::fc::nif:
			nif(s);
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

	l = ev_arr(l);
	int val = (evaluate_exp(r));

	v[l] = val;

}
void swp(string& s) {
	
	string p = in_par(s);

	string a;
	string b;

	between_s(a, b, p, ",");

	a = ev_arr(a);
	b = ev_arr(b);

	int h = v[a];
	v[a] = v[b];
	v[b] = h;
}

void nif(string& s) {

	string cmp = in_par(s);

	if (!comp_combine(cmp))
		return;
	else {
		//prepped_code.take();
		prepped_code.take();
	}

}
void go(string& s) {

	auto p = r.match(rf::fc::go, s);
	string flg = p[1];	//this is our go to flag

	while (prepped_code.take() != flg);
}

bool comp_combine(string& par)	//takes input from () so (1>2) should pass 1>2, (1>2 && 2>1) should send 1>2 && 2>1
{	
	string a;
	string b;

	if (par.find("&&") != string::npos) {

		between_s(a, b, par, "&&");
		return comp_combine(a) && comp_combine(b);

	}
	else if (par.find("||") != string::npos) {

		between_s(a, b, par, "||");
		return comp_combine(a) || comp_combine(b);

	}
	else

		return comp_all(par);
}
bool comp_all(string& par) {	//takes inpt from between () so while(1>2) should send here 1>2

	string z = comp_sign(par);
	
	string a; 
	string b; 

	between_s(a, b, par,z.c_str());	//asigns to a and b strings from string par between a char z

	switch (z[0]) {

	case '=':
		return evaluate_exp(a) == evaluate_exp(b);
	case '>':
		return evaluate_exp(a) > evaluate_exp(b);
	case '<':
		return evaluate_exp(a) < evaluate_exp(b);
	case '!':
		return evaluate_exp(a) != evaluate_exp(b);
	}

	return 0;
}
string comp_sign(string& a) {

	string z = "";

	if (a.find('>') != string::npos)
		z = ">";
	else if (a.find('<') != string::npos)
		z = "<";
	else if (a.find('!') != string::npos)
		z = "!=";
	else if (a.find('=') != string::npos)
		z = "==";

	return z;

}