#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Exception1.h"   
#include "Exception2.h"   
#include "Exception3.h"   
#include "Catalog.h"   
#include "Movie.h"   
#include "Book.h"   
#include "Music.h"   

using namespace std;

ofstream& operator<< (ofstream& out, const vector<string>& vec);
bool col1_sort(const vector<string>& vec1, const vector<string>& vec2);
bool col2_sort(const vector<string>& vec1, const vector<string>& vec2);
bool col3_sort(const vector<string>& vec1, const vector<string>& vec2);
bool col4_sort(const vector<string>& vec1, const vector<string>& vec2);
bool col5_sort(const vector<string>& vec1, const vector<string>& vec2);


int main(int argc, char const *argv[])
{

	const string DATA_TXT = "data.txt";
	const string COMMANDS_TXT = "commands.txt";
	const string OUTPUT_TXT = "output.txt";
	const char quoatation_mark = '\"';

	int book = 0, movie = 0, music = 0;
	string line, catalog_type, word;

	ifstream dp, cp;
	ofstream op;

	dp.open(DATA_TXT);
	cp.open(COMMANDS_TXT);
	op.open(OUTPUT_TXT);

	/* Reading the catalog type */
	dp >> catalog_type;
	op << "Catalog Read: " << catalog_type << endl;    

	/* Specifying the catalog type */
	if(catalog_type == "movie")
		movie = 1;

	else if(catalog_type == "book")
		book = 1;

	else if(catalog_type == "music")
		music = 1;

	Movie movie_obj;
	Book book_obj;
	Music music_obj;

	getline(dp, line);   // dummy line


	/* 'line_count' counts the line number */
	/* 'count' was used to know which field to enter  */
	int line_count = 0;
	int count = 0;

	vector<vector<string>> vec;

	while (getline(dp, line)){

	int x = 0;   
	int check = 0;

	/* Blank line control */
	while(isspace(line[x])){
		x++;
		if(line.length() == x)
			check = 1;		// Line is blank!
	}


	if(!check){		// If line is not blank, assignment process begins. Otherwise, it moves to the next line.

		vec.push_back(vector<string>());  

		for (int i = 0; i < line.length(); ++i){
		
			if(line[i] == quoatation_mark){		// line[i] == '"'

				for (int j = i + 1; j < line.length(); ++j)
				{	

					if(line[j] == quoatation_mark){		// line[j] == '"'
						
						word = line.substr(i+1, j-i-1);		// Subtracting quotation marks from line and assigning to word (string).
						i = j + 1;		// Shifting the first cursor to the behind of second cursor.(cursors(i an j) holds the quotation marks' index)

						/******************************************************/
						/*              DATA TRANSFER PART	              	  */
						/******************************************************/

						switch(count){    // count determines which field the word enter.
						/* movie, book and music are integer. They was assigned by specific value(1 or 0) according to catalog type. 
						/* The word is assigned to the private vector(title vector, director vector etc...) according to the name of the field.
						/* And then, the 2 dimensional vector is filled by that private data */
							case 0:

								if(movie){
									movie_obj.set_title(word);
									vec[line_count].push_back(movie_obj.get_title().back()); 
								}
								else if(book){
									book_obj.set_title(word);
									vec[line_count].push_back(book_obj.get_title().back());
								}
								else if(music){
									music_obj.set_title(word);
									vec[line_count].push_back(music_obj.get_title().back());
								}
								break;

							case 1:

								if(movie){
									movie_obj.set_director(word);
									vec[line_count].push_back(movie_obj.get_director().back());
								}
								else if(book){
									book_obj.set_authors(word);
									vec[line_count].push_back(book_obj.get_authors().back());
								}
								else if(music){
									music_obj.set_artists(word);
									vec[line_count].push_back(music_obj.get_artists().back());
								}
								break;

							case 2:	

								if(movie){
									movie_obj.set_year(word);
									vec[line_count].push_back(movie_obj.get_year().back());
								}
								else if(book){
									book_obj.set_year(word);
									vec[line_count].push_back(book_obj.get_year().back());
								}
							
								else if(music){
									music_obj.set_year(word);
									vec[line_count].push_back(music_obj.get_year().back());
								}
								break;

							case 3:

								if(movie){
									movie_obj.set_genre(word);
									vec[line_count].push_back(movie_obj.get_genre().back());
								}
								else if(book){
									book_obj.set_tags(word);
									vec[line_count].push_back(book_obj.get_tags().back());
								}
								else if(music){
									music_obj.set_genre(word);
									vec[line_count].push_back(music_obj.get_genre().back());
								}
								break;

							case 4:	

								if(movie){
									movie_obj.set_starring(word);
									vec[line_count].push_back(movie_obj.get_starring().back());
								}
								break;

							default:
								break;

						}
						count++;	// The count increases as field was assigned
						break;
					} 

				}		
			}
		}
		count = 0;		// line end
		line_count++;	
	}
	}


	/******************************************************/
	/*           EXCEPTION 1 - DUPLICATE ENTRY	          */
	/******************************************************/

	vector<int> missed_rows;	// missed_rows vector will hold lines index which have missing field.
	
	/* Nested loop is used for comparing two data */
	for (int i = 0; i < line_count-1 ; ++i)		
	{	
		for (int j = i+1; j < line_count ; ++j)
		{			
			try{
				/* If the titles are same and the row does 'not' have the missing field, it enters here. */
				if((vec[i][0] == vec[j][0]) && (vec[i].size() == movie_obj.get_field_number()) && (vec[j].size() == movie_obj.get_field_number())){  //movie
					missed_rows.push_back(j);	
					i++;
					throw Exception1(vec[j]);	// Throwing the exception.
				}
		
				else if((book || music) && (vec[i][0] == vec[j][0]) && (vec[i].size() == book_obj.get_field_number())
				 		&& (vec[j].size() == book_obj.get_field_number())){     // book or music (they have same field number)
					missed_rows.push_back(j);
					i++;
					throw Exception1(vec[j]);	// Throwing the exception.
				}
			} 
			catch(Exception1 obj){
				op << "Exception: duplicate entry" << endl;    // Printing the exception.
				op << obj.get_exception_vec() << endl;    // Printing the exception.
			}
		}
	}

	/******************************************************/
	/*           EXCEPTION 2 - MISSING FIELD	          */
	/******************************************************/

	
		for (int i = 0; i < line_count; ++i)
		{	
			try{
			/* If size of vector is not equal to real field number, it has missing field. */
			if(movie && (vec[i].size() != movie_obj.get_field_number())){	// movie
				missed_rows.push_back(i);
				throw Exception2(vec[i]);	// Throwing the exception.
			}
			
			else if((book || music) && (vec[i].size() != book_obj.get_field_number())){   // book or music (they have same field number)
				missed_rows.push_back(i);
				throw Exception2(vec[i]);	// Throwing the exception.
			}	
			}
			catch(Exception2 obj2){
		op << "Exception: missing field" << endl;    // Printing the exception.
		op << obj2.get_exception_vec() << endl; 	// Printing the exception.
	}
		}
	

	/* Calculating and printing the unique entry number.. */
	int unique_entry_num = line_count - Exception1::get_error_num();
	op << unique_entry_num << " unique entries" << endl;  // unique entry num


	sort(missed_rows.begin(), missed_rows.end(), greater<int>());
	/* The row which has the missing field is deleted from the 2D vector.*/
	for(int i = 0; i < missed_rows.size(); ++i){
    	vec.erase(vec.begin() + missed_rows[i]);
    	line_count--;
	}
	/* Now, 2D vector has only unique rows. */



	/******************************************************/
	//              SEARCH AND SORT PART	              //
	/******************************************************/

	string command_line;
	string command, searched_word, searched_field;
	int column = 0;

	while(getline(cp,command_line)){

		int leading_spaces = 0;
		int trailing_spaces = 0;

		stringstream str_strm(command_line);
		str_strm >> command;

 		try{ 
 			/* -------------------------------------*/
 			/* ---------- SEARCH PART ------------- */
 			/* -------------------------------------*/
			if(command == "search"){

				str_strm >> command;	

				/* If command has trailing_spaces. */
				if(command[command.length()-1] != quoatation_mark){
					char garbage;
					while(garbage != '\"'){
						str_strm.get(garbage);
						command.push_back(garbage);
					}
				}
				
				/* If command has leading_spaces. */
				else if(command.length()==1 && command[0] == quoatation_mark){
					char garbage;
					while(garbage != '\"'){
						str_strm.get(garbage);
						command.push_back(garbage);
					}
				}

				/* Finding the leading spaces number to erase spaces. */
				for (int i = 1; command[i] == ' '; ++i)
					leading_spaces++;

				/* Finding the trailing spaces number to erase spaces. */
				int k = 0;
				for (k = command.length()-2; command[k] == ' '; --k)
					trailing_spaces++;
				
				command.erase(k+1, trailing_spaces);    // remove trailing spaces
				command.erase(1, leading_spaces);    // remove leading spaces
					
					/* If the 2nd command is in correct form, it enters here. */
					if(command[0] == quoatation_mark && command[command.length()-1] == quoatation_mark){

						// Removing quotation marks from command and assigning to the string(searched_word).
						searched_word = command.substr(1,command.length()-2);	

						/* 3rd command */
						str_strm >> command;

						if(command == "in"){
						
							/* 4th command */
							str_strm >> command;

							/* If the 4th command is in correct form, it enters here. */
							if(command[0] == quoatation_mark && command[command.length()-1] == quoatation_mark){

								// Removing quotation marks from command and assigning to the string(searched_field).
								searched_field = command.substr(1,command.length()-2);

								/* column is assigned by number according to the field name. */
								if(searched_field == "title")
									column = 0;
								else if(searched_field == "director" && movie)
									column = 1;
								else if(searched_field == "authors" && book)
									column = 1;
								else if( searched_field == "artists" && music)
									column = 1;
								else if(searched_field == "year")
									column = 2;
								else if(searched_field == "genre" && (movie || music))
									column = 3;
								else if(searched_field == "tags" && book)
									column = 3;
								else if(searched_field == "starring" && movie)
									column = 4;
								else
									throw Exception3(command_line);		// Throwing the exception
								
								/* Printing the command line and search result.*/
								op << command_line << endl;
								for (int i = 0; i < line_count; ++i)
								{	
									auto found = vec[i][column].find(searched_word);    
									if(found != string::npos){    // Word is found !
										op << vec[i] << endl;
									}
								}
							}

						}   
						else   // 3rd command is wrond.
							throw Exception3(command_line);
					}
			}  

			/* -------------------------------------*/
 			/* ---------- SORT PART --------------- */
 			/* -------------------------------------*/
			else if(command == "sort"){

				/* 2nd command */
				str_strm >> command;
				
				// Removing quotation marks from command and assigning to the string(searched_field).
				searched_field = command.substr(1,command.length()-2);

				/* Vector is sorted according to the field name. */
				if(searched_field == "title")
					sort(vec.begin(), vec.end(), col1_sort);

				else if(searched_field == "director" && movie)
					sort(vec.begin(), vec.end(), col2_sort);

				else if(searched_field == "authors" && book)
					sort(vec.begin(), vec.end(), col2_sort);

				else if(searched_field == "artists" && music)
					sort(vec.begin(), vec.end(), col2_sort);

				else if(searched_field == "year")
					sort(vec.begin(), vec.end(), col3_sort);

				else if(searched_field == "genre" && (movie || music))
					sort(vec.begin(), vec.end(), col4_sort);

				else if(searched_field == "tags" && book)
					sort(vec.begin(), vec.end(), col4_sort);

				else if(searched_field == "starring" && movie)
					sort(vec.begin(), vec.end(), col5_sort);

				else
					throw Exception3(command_line);		// Throwing the exception


				/* Printing the command line and sort result.*/
				op << command_line << endl;
				for (int i = 0; i < vec.size(); i++)
				{
					for (int j = 0; j < vec[i].size(); j++){
						if(i != vec.size()-1)
							op << "\"" << vec[i][j] << "\"" << " ";
						else
							op << "\"" << vec[i][j] << "\"";
					}
					if(i != vec.size()-1)
						op << endl;
				}
			}  

			else
				throw Exception3(command_line);		// Throwing the exception
		}
		
		/* Catching the exceptions */
		catch(Exception3 obj3){
			op << "Exception: command is wrong" << endl;    // Printing the exception.
			op << obj3.get_exception_line() << endl; 
		}
	}

	dp.close();
	cp.close();
	op.close();
	return 0;
}


/* Overload function for printing the vector. */
ofstream& operator<< (ofstream& out, const vector<string>& vec)
{
	for (int i = 0; i < vec.size(); ++i)
		out << "\"" << vec[i] << "\"" << " ";
	
	return out;
}

/* For comparing first column order */
bool col1_sort(const vector<string>& vec1, const vector<string>& vec2)
{ 
	return vec1[0] < vec2[0]; 
} 

/* For comparing second column order */
bool col2_sort(const vector<string>& vec1, const vector<string>& vec2)
{ 
	return vec1[1] < vec2[1]; 
} 

/* For comparing third column order */
bool col3_sort(const vector<string>& vec1, const vector<string>& vec2)
{ 
	return vec1[2] < vec2[2]; 
} 

/* For comparing fourth column order */
bool col4_sort(const vector<string>& vec1, const vector<string>& vec2)
{ 
	return vec1[3] < vec2[3]; 
} 

/* For comparing fifth column order */
bool col5_sort(const vector<string>& vec1, const vector<string>& vec2)
{ 
	return vec1[4] < vec2[4]; 
} 

