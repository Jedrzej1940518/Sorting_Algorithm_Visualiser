#pragma once

#include <vector>
#include <string>

using namespace std;

/// <summary>
/// Works like carousel. You take an element -> the pointer points to the next one now. If it reaches end, it goes back to beggining
/// Handles our code in the interpretter

struct inf_que {

	int size();

	vector<string>::iterator ptr;
	vector<string> q;

	void push(string& s);

	string& take();

	inf_que();
	void clear();
	bool empty();
};