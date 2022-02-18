#include <iostream>
#include <cstdlib>
#include <string>
#include "Exception1.h"
#include "Exception2.h"

using namespace std;

Exception2::Exception2(){Exception1();}
Exception2::Exception2(vector<string> v) : exception_vec(v), Exception1() {error_num++; }
vector<string>& Exception2::get_exception_vec(){return exception_vec;}
Exception2::~Exception2(){}