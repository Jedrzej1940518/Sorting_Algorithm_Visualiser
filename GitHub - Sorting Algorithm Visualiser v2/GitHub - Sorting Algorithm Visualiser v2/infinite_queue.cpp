#pragma once

#include "infinite_queue.h"


/// <summary>
/// Works like a carousel. You take an element -> the pointer points to the next one now. If it reaches the end, it goes back to the beginning
/// </summary>

int inf_que::size() { return q.size(); }


void inf_que::push(string& s) {
	int n = ptr - q.begin();
	q.push_back(s);
	ptr = q.begin() + n;
}

string& inf_que::take() {
	string& s = *ptr;
	++ptr;
	if (ptr == q.end())
		ptr = q.begin();
	return s;
}

inf_que::inf_que() {
	ptr = q.begin();
}

bool inf_que::empty() {
	return !q.size();
}

void inf_que::clear() {
	q.clear();
}