#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <vector>
#include "Catalog.h"

using namespace std;

class Movie : public Catalog
{
public:
	Movie();
	~Movie();
	vector<string>& get_title();
	vector<string>& get_director();
	vector<string>& get_year();
	vector<string>& get_genre();
	vector<string>& get_starring();
	void set_title(const string&);
	void set_director(const string&);
	void set_year(const string&);
	void set_genre(const string&);
	void set_starring(const string&);
	int get_field_number();

private:
	const int field_number = 5;
	vector<string> title;
	vector<string> director;
	vector<string> year; 
	vector<string> genre;
	vector<string> starring;
};

#endif