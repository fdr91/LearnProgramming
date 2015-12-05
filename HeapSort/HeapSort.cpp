#include <vector>
#include <iostream>
#include <functional>   // std::greater

template<typename T>
void printArr(T a){
	for (auto e : a)
		std::cout << e << "\t";
	std::cout << "\n";
}
std::vector<int> glob;
#define N 7

template<typename T, typename C>
void heapify(T a, size_t i, size_t size, C c){
	size_t left = 2 * i + 1;
	size_t right = left + 1;
	size_t el = i;
	if (left < size && c(*(a + i), *(a + left)))
		el = left;
	if (right < size && c(*(a + el), *(a + right)))
		el = right;
	if (el!=i){
		std::iter_swap((a + el), (a + i));
		heapify(a, el, size, c);
	}
}

template<typename T, typename C>
void buildHeap(T a, size_t size, C c){
	size_t i = size / 2;
	do{
		heapify(a, i, size, c);
	} while (i-- != 0);
}



template<typename T, typename C>
void heap_sort(T a, size_t size, C c){
	buildHeap(a, size, c);
	size_t length=size;
	while (--length){
		std::iter_swap(a, a + length);
		heapify(a, 0, length,c);
	}
}


int main(int argc, char** argv){

	while (true){
		glob.clear();
		for (int i = 0; i < N; i++)
			glob.push_back(rand() % 100);
		printArr(glob);
		heap_sort(glob.begin(), N, std::greater<int>());
		printArr(glob);
		getc(stdin);
	}

	return true;
}