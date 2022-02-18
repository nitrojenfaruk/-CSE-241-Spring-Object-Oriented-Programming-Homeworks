#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class pixel
{
	private:
		int red;
		int green;
		int blue;

	public:
		/* Constructor */
		pixel(){}

		/* Accessor and Mutator functions*/
		int get_red()const{ return red; }
		int get_green()const{ return green; }
		int get_blue()const{ return blue; }
		
		void set_red(int r){ red = r; }
		void set_green(int g){ green = g;}
		void set_blue(int b){ blue = b; }

};


class ppmImage
{
	private:

		string file_name;
		string format;	  
		int d1, d2;		// Dimension  
		const int limit_val = 255;   
		vector<vector<pixel> > vec;   // Pixel's Data

	public:

		/* Constructors */
		ppmImage(string file){ file_name = file; }
		ppmImage(int x, int y);
		ppmImage(){}

		/* Accessor and Mutator functions*/
		int get_dimension1()const { return d1; }
		int get_dimension2()const { return d2; }
		int get_limit_val()const { return limit_val; }
		string get_format()const { return format; }
		vector<vector<pixel> >& get_vector(){ return vec; }
		vector<vector<pixel> > const& get_vector()const{ return vec; }

		void set_format(string f){ format = f; } 
		void set_dimension1(int x){ d1 = x; }
		void set_dimension2(int y){ d2 = y; }

		/* Member functions */
		void save_image();
		void read_image();
		void print_dimension();
		int pixel_info(int coor_1, int coor_2, char color);
		void change_pixel_value(int coor_1, int coor_2, int choice);
	
};


/* Parameterized constructor */
/* A constructor which creates an object according to the given dimensions.
The image data represents a blank (white) image. */

ppmImage::ppmImage(int x, int y){ 

	d1 = x;
	d2 = y;

	/* Vector resizing */
	vec.resize(d1);
		for(int k = 0; k < vec.size(); ++k)
			vec[k].resize(d2);

	for (int i = 0; i < d1; ++i)
	{
		for (int j = 0; j < d2; ++j)
		{
			/* 255 255 255 -> white color */
			vec[i][j].set_red(255);
			vec[i][j].set_green(255);
			vec[i][j].set_blue(255);
		}
	}

}


/* Saves ppm image to a file. */
void ppmImage::save_image(){

	ofstream file;
	file.open(file_name);

	if(file.is_open()){
		
		/* Writing format, dimension and limit value to file. */
		file << format << endl << d1 << " "
		<< d2 <<  endl << limit_val << endl;
		
		for (int i = 0; i < d1; ++i)
		{
			for (int j = 0; j < d2; ++j)
			{	
				/* Writing pixel's info to file. */
				file << vec[i][j].get_red() << " ";
				file << vec[i][j].get_green() << " ";
				file << vec[i][j].get_blue() << "   ";
			}
			file << endl;
		}

		file.close();
	}

	else
		cerr << "File could not be opened!" << endl;

}

/* Reads ppm image from a file. */
void ppmImage::read_image()
{
	int value;

	ifstream file;
	file.open(file_name);

	if (file.is_open()){
		
		/* Reading format, dimension and limit value from file. */
		file >> format;
		file >> d1 >> d2;
		file >> value;

		for (int i = 0; i < d1; ++i)
		{
			for (int j = 0; j < d2; ++j)
			{
				/* Reading pixel's info from file. */
				file >> value;
				vec[i][j].set_red(value);
				file >> value;
				vec[i][j].set_green(value);
				file >> value;
				vec[i][j].set_blue(value);
			}
		}

		file.close();
  	}

	else
		cerr << "File could not be opened!" << endl;

}


/* Prints dimensions of the ppm image. */
inline void ppmImage::print_dimension(){

	cout << d1 << " " << d2 << endl;

}


/* Returns individual pixel information. */
int ppmImage::pixel_info(int coor_1, int coor_2, char color){ 
	
	switch(color){

		case 'r' :
			return vec[coor_1][coor_2].get_red();

		case 'g':
			return vec[coor_1][coor_2].get_green();

		case 'b':
			return vec[coor_1][coor_2].get_blue();

		default:
			break;

	}

	return 0;
}


/* Changes individual pixel values. */
void ppmImage::change_pixel_value(int coor_1, int coor_2, int choice){

	int temp, temp2, temp3;

	switch(choice){
				
		case 1: // RED AND GREEN
			temp = vec[coor_1][coor_2].get_red();
			vec[coor_1][coor_2].set_red(vec[coor_1][coor_2].get_green());
			vec[coor_1][coor_2].set_green(temp);
			break;
	
		case 2:	// RED AND BLUE
			temp2 = vec[coor_1][coor_2].get_red();
			vec[coor_1][coor_2].set_red(vec[coor_1][coor_2].get_blue());
			vec[coor_1][coor_2].set_blue(temp2);
			break;

		case 3:  // GREEN AND BLUE
			temp3 = vec[coor_1][coor_2].get_green();
			vec[coor_1][coor_2].set_green(vec[coor_1][coor_2].get_blue());
			vec[coor_1][coor_2].set_blue(temp3);
			break;

		default:
			break;

	}
		
}



/* STANDALONE FUNCTIONS */

/* Reads ppm data from file named as source_ppm_file_name, stores data in destination_object. */
int read_ppm(const string source_ppm_file_name, ppmImage& destination_object){

	int value, dim_1, dim_2; 
	string str;

	vector<vector<pixel>>& rgb_vec = destination_object.get_vector();

	ifstream file;
	file.open(source_ppm_file_name);


	if(file.is_open()){

		/* Reading format, dimension and limit value from file. */
		file >> str;
		destination_object.set_format(str);
		
		file >> dim_1;
		destination_object.set_dimension1(dim_1);

		file >> dim_2;
		destination_object.set_dimension2(dim_2);

		file >> value;   // limit value -> const member varible

		/* Vector resizing */
		rgb_vec.resize(destination_object.get_dimension1());
		for(int i = 0; i< rgb_vec.size(); ++i)
			rgb_vec[i].resize(destination_object.get_dimension2());

		
		/* Reading pixel's infoformation from file. */
		/* If value is greater than 255, it is fixed to 255. */
		for (int i = 0; i < destination_object.get_dimension1(); ++i)
		{
			for (int j = 0; j < destination_object.get_dimension2(); ++j)
			{
				file >> value;
				if(value > destination_object.get_limit_val())
					value = 255;
				rgb_vec[i][j].set_red(value);

				file >> value;
				if(value > destination_object.get_limit_val())
					value = 255;
				rgb_vec[i][j].set_green(value);

				file >> value;
				if(value > destination_object.get_limit_val())
					value = 255;
				rgb_vec[i][j].set_blue(value);

			}
		}

		file.close();
		return 1;
	}

	return 0;	
}


/* Writes ppm data from source_object to the file named destination_ppm_file_name.*/
int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object){    

	ofstream file;
	file.open(destination_ppm_file_name);

	vector<vector<pixel>>const& rgb_vec = source_object.get_vector();

	if(file.is_open()){
		
		/* Writing format, dimension and limit value to file. */
		file << source_object.get_format() << endl << source_object.get_dimension1() << " "
		<< source_object.get_dimension2() <<  endl << source_object.get_limit_val() << endl;
		
		/* Writing pixel's information to file. */
		for (int i = 0; i < source_object.get_dimension1(); ++i)
		{
			for (int j = 0; j < source_object.get_dimension2(); ++j)
			{
				file << rgb_vec[i][j].get_red() << " ";
				file << rgb_vec[i][j].get_green() << " ";
				file << rgb_vec[i][j].get_blue() << "   ";
			}
			file << endl;
		}

		file.close();
		return 1;
	}

	return 0;
}


/* Swaps the color values of every pixel in a given ppm image.*/
int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice){

	int temp, temp2, temp3;
	vector<vector<pixel>>& rgb_vec = image_object_to_be_modified.get_vector();

	for (int i = 0; i < image_object_to_be_modified.get_dimension1(); ++i)
	{
		for (int j = 0; j < image_object_to_be_modified.get_dimension2(); ++j)
		{
			switch(swap_choice){
				
				case 1:  // RED AND GREEN
					temp = rgb_vec[i][j].get_red();
					rgb_vec[i][j].set_red(rgb_vec[i][j].get_green());
					rgb_vec[i][j].set_green(temp);
					break;

				case 2:	// RED AND BLUE
					temp2 = rgb_vec[i][j].get_red();
					rgb_vec[i][j].set_red(rgb_vec[i][j].get_blue());
					rgb_vec[i][j].set_blue(temp2);
					break;

				case 3:	// GREEN AND BLUE
					temp3 = rgb_vec[i][j].get_green();
					rgb_vec[i][j].set_green(rgb_vec[i][j].get_blue());
					rgb_vec[i][j].set_blue(temp3);
					break;

				default:
					return 1;

			}
		}
	}

	return 0;

}


/* Creates and returns a copy of a new ppmImage object which stores only one color at each pixel*/
ppmImage single_color(const ppmImage& source, int color_choice){  

	/* Format and dimension transfer */
	ppmImage newObj;
	newObj.set_format(source.get_format());
	newObj.set_dimension1(source.get_dimension1());
	newObj.set_dimension2(source.get_dimension2());

	vector<vector<pixel>>& rgb_vec = newObj.get_vector();  // new object vector

	/* Vector resizing */
	rgb_vec.resize(newObj.get_dimension1());
		for(int i = 0; i< rgb_vec.size(); ++i)
			rgb_vec[i].resize(newObj.get_dimension2());


	vector<vector<pixel>>const& rgb_vec_source = source.get_vector();  // source object vector


	for (int i = 0; i < newObj.get_dimension1(); ++i)
	{
		for (int j = 0; j < newObj.get_dimension2(); ++j)
		{

			switch(color_choice){
				
				case 1:  // RED channel is preserved.
					rgb_vec[i][j].set_red(rgb_vec_source[i][j].get_red());
					rgb_vec[i][j].set_green(0);
					rgb_vec[i][j].set_blue(0);
					break;

				case 2:  // GREEN channel is preserved.
					rgb_vec[i][j].set_red(0);
					rgb_vec[i][j].set_green(rgb_vec_source[i][j].get_green());
					rgb_vec[i][j].set_blue(0);
					break;

				case 3:  // BLUE channel is preserved.
					rgb_vec[i][j].set_red(0);
					rgb_vec[i][j].set_green(0);
					rgb_vec[i][j].set_blue(rgb_vec_source[i][j].get_blue());
					break;

				default:
					break;

			}
		}
	}

	return newObj;
}



int main(int argc, char const *argv[])
{

	int choice, dim1, dim2;
	string ppm_file_name;
	bool no_error = false;

	/*
	./test 7 image.ppm 
	choice = 7;
	ppm_file_name = image.ppm 
	*/
	if(argc == 3){
		choice = stoi(argv[1]);	  
		ppm_file_name += argv[2];	
		no_error = true;
	}
	else{
		cerr << "Wrong call!" << endl;
		no_error = false;
	}


	if(no_error){

		string o1, o2, o3, o4, o5, o6, o7;
		ppmImage obj, obj1, obj2, obj3;
		
		switch(choice){

			case 1:   // Reads ppm_file_name and write the same data without changing anything.
				read_ppm(ppm_file_name, obj);	
				o1 = "o1.ppm";	
				write_ppm(o1, obj);
				break;

			case 2:   // Swaps red and green channels.	
				read_ppm(ppm_file_name, obj);	
				swap_channels(obj, 1);
				o2 = "o2.ppm";
				write_ppm(o2, obj);
				break;

			case 3:	  // Swaps red and blue channels.
				read_ppm(ppm_file_name, obj);	
				swap_channels(obj, 2);
				o3 = "o3.ppm";
				write_ppm(o3, obj);
				break;
			
			case 4:   // Swaps green and blue channels.
				read_ppm(ppm_file_name, obj);	
				swap_channels(obj, 3);
				o4 = "o4.ppm";
				write_ppm(o4, obj);
				break;

			case 5:   // Creates a new object which only contains red channel data of the file read.
				read_ppm(ppm_file_name, obj);	
				o5 = "o5.ppm";
				write_ppm(o5, single_color(obj, 1));
				break;

			case 6:   // Creates a new object which only contains green channel data of the file read.
				read_ppm(ppm_file_name, obj);	
				o6 = "o6.ppm";		
				write_ppm(o6, single_color(obj, 2));
				break;

			case 7:	  // Creates a new object which only contains blue channel data of the file read.
				read_ppm(ppm_file_name, obj);
				o7 = "o7.ppm";	
				write_ppm(o7, single_color(obj, 3));
				break;

			default:
				cout << "Wrong call!" << endl;
				break; 
			
		}

	}

	return 0;
}
