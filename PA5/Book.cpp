#include <iostream>
#include <cstdlib>
#include <string>
#include "Catalog.h"
#include "Book.h"

using namespace std;

Book::Book(){}
Book::~Book(){}
vector<string>& Book::get_title(){return title;}
vector<string>& Book::get_year(){return year;}
void Book::set_title(const string& t){title.push_back(t);}
void Book::set_year(const string& y){year.push_back(y);}
vector<string>& Book::get_authors(){return authors;}
vector<string>& Book::get_tags(){return tags;}
void Book::set_authors(const string& a){authors.push_back(a);}
void Book::set_tags(const string& t){tags.push_back(t);}
int Book::get_field_number(){return field_number;}