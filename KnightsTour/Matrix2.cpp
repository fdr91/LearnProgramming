#include "Matrix2.hpp"

#include <exception>
#include <algorithm>

#include <stdio.h>

using namespace std;

#define INDEX_BOUNDS_CHECK(x,y, size) if(x<0 || y<0 || x >= size || y >= size)\
										throw exception("Matrix index outbound");

void Matrix2::set(int x, int y, int val){
	INDEX_BOUNDS_CHECK(x, y, size);
	els[x*size + y] = val;
}

void Matrix2::set(point p, int val){
	set(p.first, p.second, val);
}

int Matrix2::get(int x, int y){
	INDEX_BOUNDS_CHECK(x, y, size);
	return els[x*size + y];
}

int Matrix2::get(point p){
	return get(p.first, p.second);
}

void Matrix2::print(void){
	for (int i = 0; i < size*size; i++){
		if ((i+1)%size == 0)
			printf("%3d\n", els[i]);
		else
			printf("%3d\t",els[i]);
	}
}
