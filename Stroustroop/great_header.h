#include "stdafx.h"

#include <string>
#include <iostream>


class BeLogger {
	std::string f;
public:
	BeLogger(std::string fun = "") : f(fun) { std::cout << "Begin " << f << std::endl; }
	~BeLogger() {
		std::cout << "End " << f << std::endl;
	}
};

#define FTRACE BeLogger lgr(__FUNCTION__ );

void numericCat();
void randomCat();
void randomTest();