#ifndef CATALOG_H
#define CATALOG_H
#include <iostream>
#include <vector>

using namespace std;

class Catalog 
{
public:
	Catalog();
	~Catalog();
	virtual vector<string>& get_title() = 0;
	virtual vector<string>& get_year() = 0;
	virtual void set_title(const string&) = 0;
	virtual void set_year(const string&) = 0;
	virtual int get_field_number() = 0;

private:
	vector<string> title;
	vector<string> year; 
};

#endif