#ifndef HEADER_H
#define HEADER_H
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



class Exception1
{
public:
	Exception1();
	Exception1(vector<string> v);
	vector<string>& get_exception_vec();
	~Exception1();
	static int get_error_num();

private:
	vector<string> exception_vec;

protected:
	static int error_num;
};



class Exception2 : public Exception1
{
public:
	Exception2();
	Exception2(vector<string> v);
	vector<string>& get_exception_vec();
	~Exception2();

private:
	vector<string> exception_vec;
};


class Exception3
{
public:
	Exception3();
	Exception3(string exc_l);
	string get_exception_line();
	~Exception3();

private:
	string exception_line;
};


#endif