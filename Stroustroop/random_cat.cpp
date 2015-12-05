#include <stdint.h>

#include "great_header.h"

#include <cmath>
#include <cassert>

#include <vector>
#include <string>
#include <map>

#include <iostream>
#include <iomanip>


class Randint //generator with uniform distribution 
{
	int32_t randx;
public:
	Randint(int32_t s = 0) { randx = s; }
	void seed(int32_t s) { randx = s; }
	static int32_t abs(int32_t x) { return x & 0x7fffffff; }
	static double max() { return 2147483648.0; }
	int32_t draw() { return randx = randx * 1103515245 + 12345;}
	double fdraw() { return abs(draw()) / max(); } //[0,1]
	virtual int32_t operator()() { FTRACE; return abs(draw()); }
};


class Urand : public Randint //uniform
{
	int32_t n;
public: 
	Urand(int32_t nn) { n = nn; }
	int32_t operator() () { long r = n*fdraw(); return r == n ? n - 1 : r; }
};

class Erand : public Randint { //exponential(dont sure it's working good)
	int32_t mean;
public:
	Erand(int32_t m) : mean(m) {};
	int32_t operator() () { return -mean * log((max() - draw()) / max() + .5); }
};


void generateN(std::vector<int32_t>& result, size_t n,  Randint& generator) {
	result.reserve(n);

	for (size_t i = 0; i < n; ++i ) {
		result.push_back(generator());
	}

	assert(result.size() == n);
	
	return;
}

void randomCat() {
	FTRACE;
	std::vector<int32_t> uniformVec;
	std::vector<int32_t> expVec;
	int32_t n = 100;

	generateN(uniformVec, n, Urand(10));
	generateN(expVec, n, Erand(10));

	std::vector<int32_t>::const_iterator ui = uniformVec.begin();
	std::vector<int32_t>::const_iterator ei = expVec.begin();

	for (; ui <uniformVec.end() && ei < expVec.end(); ++ui, ++ei) {
		std::cout << std::setw(4) << *ui << " " << std::setw(4) << *ei << std::endl;
	}

	return;
}

void randomTest() {
	FTRACE;
	Urand draw(10);
	std::map<int, int> bucket;
	for (int i = 0; i < 1000000; i++) bucket[draw()]++;
	for (int i = 0; i < 10; i++) std::cout << bucket[i] << '\n';
	return;
}
