#ifndef _MATRIX2_HPP
#define _MATRIX2_HPP

#include <vector>

typedef std::pair<int, int> point;

class Matrix2 {
	std::vector<int> els;
	int size;
public:
	Matrix2() {};
	Matrix2(int _size) : els(_size*_size, 0), size(_size) {};
	void set(int x, int y, int val);
	void set(point, int val);
	int get(int x, int y);
	int get(point);
	void print(void);
};
#endif