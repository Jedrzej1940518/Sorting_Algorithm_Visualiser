#pragma once

#include "ConstNumbers.h"
#include "Interpretter.h"

#include <vector>
#include <string>
#include <utility>

using namespace std;


void QuickSort (vector<int>& vc, SoC& sc, int low, int high);

void InsertSort(vector<int>& vc, SoC& sc);

void UserAlgorithm(vector<int>& vc, SoC& sc, string& code);