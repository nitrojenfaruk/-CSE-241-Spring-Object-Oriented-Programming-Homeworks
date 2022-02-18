#include <iostream>
#include <cstdlib>
#include <string>
#include "Exception3.h"

using namespace std;

Exception3::Exception3(){}
Exception3::Exception3(string exc_l) : exception_line(exc_l) {}
string Exception3::get_exception_line(){return exception_line;}
Exception3::~Exception3(){}