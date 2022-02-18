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
		int& get_red(){ return red;}        

		int get_green()const{ return green; }
		int& get_green(){ return green;} 

		int get_blue()const{ return blue; }
		int& get_blue(){ return blue;}
		
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
		int limit_val = 255;   
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
		void set_file_name(string f){ file_name = f; }  
		void set_dimension1(int x){ d1 = x; }
		void set_dimension2(int y){ d2 = y; }

		/* Member functions */
		void save_image();
		void read_image();
		void print_dimension();
		int pixel_info(int coor_1, int coor_2, int color);
		void change_pixel_value(int coor_1, int coor_2, int choice);
		
		/* -------------------------------------------------------- */
		/* -------------------------------------------------------- */

		/* Member function */
		int& operator()(int& row, int& column, int color_channel);    

		/* Friend Functions */
		friend ppmImage operator+(const ppmImage& img1, const ppmImage& img2);
		friend ppmImage operator-(const ppmImage& img1, const ppmImage& img2);
		friend ostream& operator<<(ostream& out, ppmImage& img);

};


/* Friend Functions */
/* Adds two ppmImage objects. They have to be the same size 
   otherwise it returns an empty ppmImage object. */
ppmImage operator+(const ppmImage& img1, const ppmImage& img2){

	int value;
	ppmImage obj;

	/* Empty object */
	obj.d1 = 0;
	obj.d2 = 0;
	obj.format = img1.format;

	/* Objects have same size.. */
	if(img1.d1 == img2.d1 && img1.d2 == img2.d2){

		/* Dimension data transfer */
		obj.d1 = img1.d1;
		obj.d2 = img1.d2;

		/* Vector resizing according to dimension. */
		obj.vec.resize(obj.d1);
		for(int k = 0; k < obj.vec.size(); ++k)
			obj.vec[k].resize(obj.d2);

		/* Addition Part */
		/* If a sum is greater than limit value(255), the sum will be fixed to limit value. */
		for (int i = 0; i < img1.d1; ++i)
		{
			for (int j = 0; j < img1.d2; ++j)
			{	
				/* Adding them pixel-by-pixel */
				value = img1.vec[i][j].get_red() + img2.vec[i][j].get_red();
				if(value > img1.limit_val)
					value = img1.limit_val;
				obj.vec[i][j].set_red(value);	

				value = img1.vec[i][j].get_green() + img2.vec[i][j].get_green();
				if(value > img1.limit_val)
					value = img1.limit_val;
				obj.vec[i][j].set_green(value);

				value = img1.vec[i][j].get_blue() + img2.vec[i][j].get_blue();
				if(value > img1.limit_val)
					value = img1.limit_val;
				obj.vec[i][j].set_blue(value);
			}
		}

	}

	return obj;
}


/* Subtracts one ppmImage objects from the other. They have to be 
   the same size otherwise it returns an empty ppmImage object. */
ppmImage operator-(const ppmImage& img1, const ppmImage& img2){

	int value, lower_bound = 0;
	ppmImage obj;

	/* Empty object */
	obj.d1 = 0;
	obj.d2 = 0;
	obj.format = img1.format; 

	/* Objects have same size.. */
	if(img1.d1 == img2.d1 && img1.d2 == img2.d2){

		/* Dimension data transfer */
		obj.d1 = img1.d1;
		obj.d2 = img1.d2;

		/* Vector resizing according to dimension. */
		obj.vec.resize(obj.d1);
		for(int k = 0; k < obj.vec.size(); ++k)
			obj.vec[k].resize(obj.d2);

		/* Subtraction Part */
		/* If a result is less than lower_bound(0), the result will be fixed to lower_bound. */
		for (int i = 0; i < img1.d1; ++i)
		{
			for (int j = 0; j < img2.d2; ++j)
			{	
				/* Subtracting them pixel-by-pixel */
				value = img1.vec[i][j].get_red() - img2.vec[i][j].get_red();	
				if(value < lower_bound)
					value = lower_bound;
				obj.vec[i][j].set_red(value);

				value = img1.vec[i][j].get_green() - img2.vec[i][j].get_green();
				if(value < lower_bound)
					value = lower_bound;
				obj.vec[i][j].set_green(value);

				value = img1.vec[i][j].get_blue() - img2.vec[i][j].get_blue();
				if(value < lower_bound)
					value = lower_bound;
				obj.vec[i][j].set_blue(value);
			}
		}

	}

	return obj;
}

/* Prints image details and image data to stdout. */
ostream& operator<<(ostream& out, ppmImage& img){

	out << img.format << endl << img.d1 << " "
		<< img.d2 <<  endl << img.limit_val << endl;

	for (int i = 0; i < img.d1; ++i)
	{
		for (int j = 0; j < img.d2; ++j)
		{	
			/* Writing pixel's info to stdout. */
			out << img.vec[i][j].get_red() << " ";   
			out << img.vec[i][j].get_green() << " ";
			out << img.vec[i][j].get_blue() << "   ";
		}
		out << endl;
	}

	return out;
}


// Function-call operator. This operator returns a reference to the pixel value. 
/* First parameter -> row number.
   Second parameter -> column number. 
   Third parameter -> color channel */
int& ppmImage::operator()(int& row, int& column, int color_channel){


	switch(color_channel){
				
		case 1:   // RED
			return vec[row][column].get_red();	
				
		case 2:   // GREEN
			return vec[row][column].get_green();	

		case 3:	  // BLUE
			return vec[row][column].get_blue();	

		default:
			break;
			
	}

	return vec[0][0].get_red();	   // Dummy return value, it will never returned.

}


/* Standalone functions */
/* Reads images from two file. Adds them and saves the resulting image to the third file. */
int test_addition(const string filename_image1, const string filename_image2, const string filename_image3){

	ifstream file1, file2;
	ofstream file3;

	file1.open(filename_image1);	
	file2.open(filename_image2);
	file3.open(filename_image3);

	if(file1.is_open() && file2.is_open() && file3.is_open()){

		/* Creating objects based on file names */
		ppmImage obj1(filename_image1);
		ppmImage obj2(filename_image2);
		ppmImage obj3;
		
		/* Reads ppm images from files. */
		obj1.read_image();
		obj2.read_image();

		vector<vector<pixel>>& rgb_vec = obj3.get_vector();  // new object vector

		/* Vector resizing */
		rgb_vec.resize(obj1.get_dimension1());
		for(int i = 0; i < rgb_vec.size(); ++i)
			rgb_vec[i].resize(obj1.get_dimension2());

		/* ADDITION */
		obj3 = obj1 + obj2;

		/* Saves the ppm image to filename_image3. */
		obj3.set_file_name(filename_image3);
		obj3.save_image();
		
		return 1;
	}

	return 0;
}


/* Reads images from two file. Subtracts them and saves the resulting image to third file. */
int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3){

	ifstream file1, file2;
	ofstream file3;

	file1.open(filename_image1);	
	file2.open(filename_image2);
	file3.open(filename_image3);

	if(file1.is_open() && file2.is_open() && file3.is_open()){

		/* Creating objects based on file names */
		ppmImage obj1(filename_image1);
		ppmImage obj2(filename_image2);
		ppmImage obj3;
		
		/* Reads ppm images from files. */
		obj1.read_image();
		obj2.read_image();

		vector<vector<pixel>>& rgb_vec = obj3.get_vector();  // new object vector

		/* Vector resizing */
		rgb_vec.resize(obj1.get_dimension1());
		for(int i = 0; i < rgb_vec.size(); ++i)
			rgb_vec[i].resize(obj1.get_dimension2());

		/* SUBTRACTION */
		obj3 = obj1 - obj2;

		/* Saves the ppm image to filename_image3 */
		obj3.set_file_name(filename_image3);
		obj3.save_image();
		
		return 1;
	}

	return 0;
}


/* Reads images from filename_image1 and prints it to stdout. */
int test_print(const string filename_image1){

	ifstream file;
	file.open(filename_image1);	

	if(file.is_open()){

		ppmImage obj(filename_image1);
		obj.read_image();	// Reading ppm image from file.

		/* Printing Part */ 
		cout << obj;

		return 1;  // Successful printing.
	}

	return 0;
}




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

		vec.resize(d1);
		for(int k = 0; k < vec.size(); ++k)
			vec[k].resize(d2);


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
int ppmImage::pixel_info(int coor_1, int coor_2, int color){ 
	
	switch(color){

		case 1:
			return vec[coor_1][coor_2].get_red();

		case 2:
			return vec[coor_1][coor_2].get_green();

		case 3:
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

		file >> value;   // limit value -> member varible

		/* Vector resizing */
		rgb_vec.resize(destination_object.get_dimension1());
		for(int i = 0; i < rgb_vec.size(); ++i)
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


/* Re-implemented swap_channels function with function-call operator.*/
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
					temp = image_object_to_be_modified(i,j,1);
					image_object_to_be_modified(i,j,1) = image_object_to_be_modified(i,j,2);
					image_object_to_be_modified(i,j,2) = temp;
					break;

				case 2:	// RED AND BLUE	
					temp2 = image_object_to_be_modified(i,j,1);
					image_object_to_be_modified(i,j,1) = image_object_to_be_modified(i,j,3);
					image_object_to_be_modified(i,j,3) = temp2;
					break;

				case 3:	// GREEN AND BLUE
					temp3 = image_object_to_be_modified(i,j,2);
					image_object_to_be_modified(i,j,2) = image_object_to_be_modified(i,j,3);
					image_object_to_be_modified(i,j,3) = temp3;
					break;

				default:
					return 1;

			}
		}
	}

	return 0;
}


/* Re-implemented single_color function with function-call operator.*/
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

	/* Object's data transfer */
	ppmImage new_source = source;
	vector<vector<pixel>>const& rgb_vec_source = source.get_vector();  


	for (int i = 0; i < newObj.get_dimension1(); ++i)
	{
		for (int j = 0; j < newObj.get_dimension2(); ++j)
		{

			switch(color_choice){
				
				case 1:  // RED channel is preserved.
					newObj(i,j,1)=new_source(i,j,1);
					newObj(i,j,2)=0;
					newObj(i,j,3)=0;
					break;

				case 2:  // GREEN channel is preserved.
					newObj(i,j,1)=0;
					newObj(i,j,2)=new_source(i,j,2);
					newObj(i,j,3)=0;
					break;

				case 3:  // BLUE channel is preserved.
					newObj(i,j,1)=0;
					newObj(i,j,2)=0;
					newObj(i,j,3)=new_source(i,j,3);
					break;

				default:
					break;

			}
		}
	}

	return newObj;
}


/* Checks the existance of the optional argument/file */
bool check_file_existence(const string& file_name){

	fstream file;
	file.open(file_name);

	if(file.is_open())
		return true;

	return false;
}


/* Checks the existance of the optional arguments/files */
bool check_file_existence(const string& file_name, const string& file_name2){

	fstream file, file2;
	file.open(file_name);
	file2.open(file_name2);

	if(file.is_open() && file2.is_open())
		return true;

	return false;
}


int main(int argc, char const *argv[])
{

	int choice, dim1, dim2;
	string ppm_file_name1, ppm_file_name2;
	bool no_error = false;

	if(argc == 3 || argc == 4 || argc == 5){
		choice = stoi(argv[1]);	  
		ppm_file_name1 = argv[2];
		ppm_file_name2 = argv[3];	
		no_error = true;
	}
	else{
		cerr << "Wrong call!" << endl;
		no_error = false;
	}


	if(no_error){

		ppmImage obj;
		string ppm_file_name3;
		
		switch(choice){

			case 1:   // Reads images from two file. Adds them and saves the resulting image to third file.
				if(argc == 5){
					ppm_file_name3 = argv[4];
					if(!check_file_existence(ppm_file_name2, ppm_file_name3)){
						cerr << "File/files not found!" << endl;
						break; 
					}
					test_addition(ppm_file_name1, ppm_file_name2, ppm_file_name3);
				}
				else
					cerr << "Number of files is wrong!" << endl;
				break;

			case 2:   // Reads images from two file. Subtracts them and saves the resulting image to third file.
				if(argc == 5){
					ppm_file_name3 = argv[4];
					if(!check_file_existence(ppm_file_name2, ppm_file_name3)){
						cerr << "File/files not found!" << endl;
						break; 
					}
					test_subtraction(ppm_file_name1, ppm_file_name2, ppm_file_name3);
				}
				else
					cerr << "Number of files is wrong!" << endl;
				break;

			case 3:	  // Swaps red and blue channels.
				read_ppm(ppm_file_name1, obj);	
				swap_channels(obj, 2);
				if(!check_file_existence(ppm_file_name2)){
					cerr << "File/files not found!" << endl;
					break; 
				}
				write_ppm(ppm_file_name2, obj);
				break;
			
			case 4:   // Swaps green and blue channels.
				read_ppm(ppm_file_name1, obj);	
				swap_channels(obj, 3);
				if(!check_file_existence(ppm_file_name2)){
					cerr << "File/files not found!" << endl;
					break; 
				}
				write_ppm(ppm_file_name2, obj);
				break;

			case 5:   // Creates a new object which only contains red channel data of the file read.
				read_ppm(ppm_file_name1, obj);	
				if(!check_file_existence(ppm_file_name2)){
					cerr << "File/files not found!" << endl;
					break; 
				}	
				write_ppm(ppm_file_name2, single_color(obj, 1));
				break;

			case 6:   // Creates a new object which only contains green channel data of the file read.
				read_ppm(ppm_file_name1, obj);		
				if(!check_file_existence(ppm_file_name2)){
					cerr << "File/files not found!" << endl;
					break; 
				}
				write_ppm(ppm_file_name2, single_color(obj, 2));
				break;

			case 7:	  // Creates a new object which only contains blue channel data of the file read.
				read_ppm(ppm_file_name1, obj);
				if(!check_file_existence(ppm_file_name2)){
					cerr << "File/files not found!" << endl;
					break; 
				}
				write_ppm(ppm_file_name2, single_color(obj, 3));
				break;

			default:
				cout << "Wrong call!" << endl;
				break; 
			
		}

	}

	return 0;
}
