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

template< typename BidirectionalIterator, typename Compare >
void quick_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp) {
	if (first != last) {
		BidirectionalIterator left = first;
		BidirectionalIterator right = last;
		BidirectionalIterator pivot = left++;
		while (left != right) {
			if (cmp(*left, *pivot)) {
				++left;
			}
			else {
				while ((left != --right) && cmp(*pivot, *right))
					;
				std::iter_swap(left, right);
				printArr(first, last);
			}
		}
		--left;
		std::iter_swap(first, left);
		quick_sort(first, left, cmp);
		quick_sort(right, last, cmp);
	}
}

std::vector<int> vec{1, 14, 5, 3, 45, 3, 12};

int main(int argc, char** argv){
	printArr(vec);
	quick_sort(vec.begin(), vec.end(), std::less<int>());
	printArr(vec);
	getc(stdin);
	return 0;
}