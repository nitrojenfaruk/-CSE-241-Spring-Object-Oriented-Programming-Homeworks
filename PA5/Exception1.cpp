#include <iostream>
#include <cstdlib>
#include <string>
#include "Exception1.h"

using namespace std;

Exception1::Exception1(){}
Exception1::Exception1(vector<string> v) : exception_vec(v) { error_num++; }
vector<string>& Exception1::get_exception_vec(){return exception_vec;}
Exception1::~Exception1(){}
int Exception1::get_error_num(){return error_num;}

int Exception1::error_num = 0;