#ifndef EXCEPTION2_H
#define EXCEPTION2_H
#include <iostream>
#include <vector>
#include "Exception2.h"

using namespace std;

class Exception2 : public Exception1
{
public:
	Exception2();
	Exception2(vector<string> v);
	vector<string>& get_exception_vec();
	~Exception2();

private:
	vector<string> exception_vec;
};

#endif
