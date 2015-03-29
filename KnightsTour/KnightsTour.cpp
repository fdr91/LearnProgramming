#include <iostream>
#include <exception>
#include <vector>
#include "Matrix2.hpp"

int n = 5;
int nsq = 25;
point beginPoint;
Matrix2 m;

#define IN_BOUNDS(p) p.first>=0 && p.first<n &&\
	p.second >= 0 && p.second<n

void parseArgs(int argc, char** argv){
	n = atoi(argv[1]);
	beginPoint = point(atoi(argv[2]), atoi(argv[3]));
}

void usageAndExit(){
	std::cout << "KnightsTour.exe <field_size> <x0> <y0>\n\t \
				 		field_size-size of field\n\t(x0,y0) - start position" << std::endl;
	exit(-1);
}

std::vector<point> knightMoves{
	{ 2, 1 }, { 1, 2 }, { -1, 2 },  { -2, 1 }, 
	{ -2, -1 }, {-1, -2}, { 1, -2 }, {2, -1}
};

bool tryMove(int i, point index){
	for (auto k : knightMoves){
		point newPoint(index.first + k.first, 
			index.second + k.second);
		if (IN_BOUNDS(newPoint) && !m.get(newPoint)) {
			m.set(newPoint, i);
			if (i < nsq) {
				if (!tryMove(i + 1, newPoint))
					m.set(newPoint, 0);
				else
					return true;
			}
			else
				return true;
		}
	}
	return false;
}

int main(int argc, char** argv){
	if (argc != 4)
		usageAndExit();
	printf("Start KnightTour\n");
	try {
		parseArgs(argc, argv);
		m = Matrix2(n);
		m.set(beginPoint, 1);
		if (tryMove(2, beginPoint))
		{	
			printf("Found solution...\n");
			m.print();
		}
		else {
			printf("No solution...\n");
		}
	}
	catch (const std::exception &e) {
		std::cout << e.what() <<std::endl;
	}
	catch (...) {
		std::cout << "Undefined exception" << std::endl;
	}
	printf("Press any key to exit...\n");
	getc(stdin);
	return 0;
}