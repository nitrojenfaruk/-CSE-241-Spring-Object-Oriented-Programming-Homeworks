#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <vector>
#include "Catalog.h"

using namespace std;

class Book : public Catalog
{
public:
	Book();
	~Book();
	vector<string>& get_title();
	vector<string>& get_authors();
	vector<string>& get_year();
	vector<string>& get_tags();
	void set_title(const string&);
	void set_authors(const string&);
	void set_year(const string&);
	void set_tags(const string&);
	int get_field_number();
	
private:
	const int field_number = 4;
	vector<string> title;
	vector<string> authors;
	vector<string> year; 
	vector<string> tags;
};

#endif