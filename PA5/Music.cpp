#include <iostream>
#include <cstdlib>
#include <string>
#include "Catalog.h"
#include "Music.h"

using namespace std;

Music::Music(){}
Music::~Music(){}
vector<string>& Music::get_title(){return title;}
vector<string>& Music::get_year(){return year;}
void Music::set_title(const string& t){title.push_back(t);}
void Music::set_year(const string& y){year.push_back(y);}
vector<string>& Music::get_artists(){return artists;}
vector<string>& Music::get_genre(){return genre;}
void Music::set_artists(const string& a){artists.push_back(a);}
void Music::set_genre(const string& g){genre.push_back(g);}
int Music::get_field_number(){return field_number;}
