#ifndef EXCEPTION3_H
#define EXCEPTION3_H
#include <iostream>
#include <vector>

using namespace std;

class Exception3
{
public:
	Exception3();
	Exception3(string exc_l);
	string get_exception_line();
	~Exception3();

private:
	string exception_line;
};

#endif