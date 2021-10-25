#pragma once

#include <vector>
#include <string>

using namespace std;

/// <summary>
/// Works like carousel. You take an element -> the pointer points to the next one now. If it reaches end, it goes back to beggining
/// </summary>

struct inf_que{

	int size() { return q.size(); }

	vector<string>::iterator ptr;
	vector<string> q;

	void push(string& s) {
		int n = ptr - q.begin();
		q.push_back(s);
		ptr = q.begin() + n;		
	}
	
	string& take() {
		string& s = *ptr;
		++ptr;
		if (ptr == q.end())
			ptr = q.begin();
		return s;
	}

	inf_que() {
		ptr = q.begin();
	}

	bool empty() {
		return !q.size();
	}
};