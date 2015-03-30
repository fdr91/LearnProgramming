#include <windows.h>
#include <functional>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>

template<typename T>
void printArr(T a){
	for (auto e : a)
		std::cout << e << "\t";
	std::cout << "\n";
}

template<typename T>
void printArr(T first, T last){
	while (first!=last)
		std::cout << *(first++) << "\t";
	std::cout << "\n";
}
template<typename I, typename C>
void quick_sort(I begin, I end, C comp){
	if (begin == end) return;
	I left = begin;
	I right = end;
	I pivot = left++;
	while (left != right){
		if (comp(*left, *pivot)){
			left++;
		}
		else {
			while (left != --right && comp(*left, *right));
			std::iter_swap(left, right);
		}
	}
	left--;
	std::iter_swap(left, begin);
	quick_sort(begin, left, comp);
	quick_sort(right, end, comp);
}

std::vector<int> vec;

#define N 8

int main(int argc, char** argv){
	while (true){
		vec.clear();
		for (int i = 0; i < N; i++){
			vec.push_back(rand()%100);
		}
		printArr(vec);
		quick_sort(vec.begin(), vec.end(), std::less<int>());
		printArr(vec);
		getc(stdin);
	}
	return 0;
}