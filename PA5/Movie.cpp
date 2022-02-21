#include <iostream>
#include <cstdlib>
#include <string>
#include "Catalog.h"
#include "Movie.h"

using namespace std;

Movie::Movie(){}
Movie::~Movie(){}
vector<string>& Movie::get_title(){return title;}
vector<string>& Movie::get_director(){return director;}
vector<string>& Movie::get_year(){return year;}
vector<string>& Movie::get_genre(){return genre;}
vector<string>& Movie::get_starring(){return starring;}
void Movie::set_title(const string& t){title.push_back(t);}
void Movie::set_director(const string& d){director.push_back(d);}
void Movie::set_year(const string& y){year.push_back(y);}
void Movie::set_genre(const string& g){genre.push_back(g);}
void Movie::set_starring(const string& s){starring.push_back(s);}
int Movie::get_field_number(){return field_number;}