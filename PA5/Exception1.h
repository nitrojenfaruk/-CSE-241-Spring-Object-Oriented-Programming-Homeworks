#ifndef EXCEPTION1_H
#define EXCEPTION1_H
#include <iostream>
#include <vector>

using namespace std;

class Exception1
{
public:
	Exception1();
	Exception1(vector<string> v);
	vector<string>& get_exception_vec();
	~Exception1();
	static int get_error_num();

private:
	vector<string> exception_vec;

protected:
	static int error_num;
};

#endif