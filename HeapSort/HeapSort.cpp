#include <vector>

template<typename I, typename C>
void checkRootNode(I vec, size_t root, size_t size, C comp){
	size_t left = root * 2;
	size_t right = root * 2+1;
	if (left < size && comp(*root, *(vec+left))){
		std::iter_swap(root, vec+left);
		checkRootNode(vec, left, size, comp);
	}
	if (right < size && comp(*root, *(vec+right))){
		std::iter_swap(root, vec + right);
		checkRootNode(vec, right, size, comp);
	}
}


template<typename I, typename C>
void build_heap(I vec, size_t size, C comp){
	for (size_t i = size / 2; i > 0; --i)
		checkRootNode(vec, i, size, comp);
}

template<typename I, typename C>
void heap_sort(I vec, size_t size){

}

template<typename T, typename C>
void heap_sort(T t, C comp){

}

std::vector<int> vec;

#define N 7

int main(int argc, char** argv){

	while (true){
		vec.clear();
		for (int i = 0; i < N; i++)
			vec.push_back(rand() % 100);
		heap_sort(vec);
		getc(stdin);
	}

	return true;
}