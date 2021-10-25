
#include "SortingAlgo.h"
#include "infinite_queue.h"
#include "Callbacks.h"

#include <map>
#include <list>
#include <string>

void Swap(vector<int>& vc, int i, int j, SoC&sc) {

	int h = vc[i];
	vc[i] = vc[j];
	vc[j] = h;

	sc.push_back({ { i,j }, 0 });
}

int part(vector<int>& vc, SoC& sc, int low, int high) {

	int pivot = vc[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; ++j) {

		sc.push_back({ {j, high},1 });
		if (vc[j] <= pivot) {
			
			++i;
			Swap(vc, i, j, sc);
		}
	}

	Swap(vc, i + 1, high, sc);
	return i + 1;

}

void QuickSort(vector<int>& vc, SoC& sc, int low, int high) {


	if (low < high) {

		int pi = part(vc, sc, low, high);

		QuickSort(vc, sc, low, pi - 1);
		QuickSort(vc, sc, pi + 1, high);

	}

}

void InsertSort(vector<int>& vc, SoC& sc) {

	int i, key, j;
	int keyDx;
	for (i = 1; i < vc.size(); ++i) {

		key = vc[i];
		keyDx = i;
		j = i - 1;
		while (j >= 0 && vc[j] > key) {

			sc.push_back({ {j, keyDx},1 });
			Swap(vc, j + 1, j, sc);

			--keyDx;
			--j;
		}


	}


}

void UserAlgorithm(vector<int>& vc, SoC& sc, string& code) {

	useralgorithm(vc, sc, code);

}
