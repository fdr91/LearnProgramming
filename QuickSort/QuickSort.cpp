#include <windows.h>
#include <functional>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>

#include <cassert>

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


template < class I, class C>
void qs(I begin, I end, C comp) {
	if (begin == end)
		return;
	I left = begin;
	I right = end;
	I pivot = left++;
	while (left != right) {
		if (comp(*left, *pivot)) {
			left++;
		}
		else {
			while (left != --right && comp(*left, *right));
			std::iter_swap(left, right);
		}
	}
	left--;
	std::iter_swap(left, begin);
	qs(begin, left, comp);
	qs(right, end, comp);

	return;
}

template<class I, class C>
bool compare(I b1, I e1, I b2, I e2, C comp){
	if (b1 == e1)
		return b2 == e2;
	else if (b2 == e2)
		return e1 == b1;
	while (b1 != e1 && b2 != e2) {
		if (comp(*b1, *b2) || comp(*b2++, *b1++))
			return false;
	}
	return b1 == e1 && b2 == e2;
}

std::vector<int> vec1;
std::vector<int> vec2;

#define N 8

int main(int argc, char** argv){
	int i = N * 10;
	while (i--){
		vec1.clear();
		vec2.clear();
		for (int i = 0; i < N; i++){
			int r = rand() % 100;
			vec1.push_back(r);
			vec2.push_back(r);
		}
		printArr(vec1);
		quick_sort(vec1.begin(), vec1.end(), std::less<int>());
		qs(vec2.begin(), vec2.end(), std::less<int>());

		printArr(vec1);
		printArr(vec2);
		assert(compare(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::less<int>()));
		//getc(stdin);
	}
	return 0;
}



