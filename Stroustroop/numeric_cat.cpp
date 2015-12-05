#include <numeric>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

template <class T> class plusator {
public:
	T operator()(T& a, T& b) {
		return a + b;
	}
};

template <class T> class summator {
	T sum;
public:
	summator(T val = T()) : sum(val) {};

	T operator()(T& a) {
		return sum += a;
	}

	T getVal() { return sum; }
};

void numericCat() {
	std::vector<int> v1({ 1, 2, 3, 4, 5 });
	int initial = 0;
	int resultA = std::accumulate(v1.begin(), v1.end(), initial, plusator<std::vector<int>::value_type>());
	summator<int> r = std::for_each(v1.begin(), v1.end(), summator<int>(initial));
	std::cout << "Result A: " << resultA << std::endl;
	std::cout << "Result Fe: " << r.getVal() << std::endl;

	return;
}