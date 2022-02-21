#ifndef MUSIC_H
#define MUSIC_H
#include <iostream>
#include <vector>
#include "Catalog.h"

using namespace std;

class Music : public Catalog
{
public:
	Music();
	~Music();
	vector<string>& get_title();
	vector<string>& get_artists();
	vector<string>& get_year();
	vector<string>& get_genre();
	void set_title(const string&);
	void set_artists(const string&);
	void set_year(const string&);
	void set_genre(const string&);
	int get_field_number();
	
private:
	const int field_number = 4;
	vector<string> title;
	vector<string> artists;
	vector<string> year; 
	vector<string> genre;
};

#endif