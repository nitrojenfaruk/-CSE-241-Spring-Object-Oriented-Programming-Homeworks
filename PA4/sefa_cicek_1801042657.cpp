#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include "sefa_cicek_1801042657.h"

using namespace std;


void func(string txt1, string txt2,string txt3);

int main(int argc, char const *argv[])
{
	const string CIRCUIT_TXT = "circuit.txt";
	const string INPUT_TXT = "input.txt";
	const string OUTPUT_TXT = "output.txt";

	func("circuit.txt","input.txt","output.txt");   

	return 0;
}

Gate::Gate(){}
Gate::~Gate(){}
string Gate::get_name()const{return name;}
void Gate::set_name(const string& n){name = n;} 
void Gate::set_input1(const string& n){input1 = n;}  
void Gate::set_input2(const string& n){input2 = n;}   
void Gate::set_input3(const string& n){input2 = n;}   
void Gate::set_input4(const string& n){input2 = n;} 
string Gate::get_input1()const{return " ";}  
string Gate::get_input2()const{return " ";}   
string Gate::get_input3()const{return " ";}   
string Gate::get_input4()const{return " ";}     
int Gate::eval(){return out;}
void Gate::set_out(int o){out = o;}
int Gate::get_out(){return out;}

Output::Output(){}  
Output::~Output(){}
int Output::eval(){int temp; temp = inp1->eval(); this->out=temp; return temp;}   ///?????
string Output::get_input1()const{return input1;} 
void Output::set_input1(const string& n){input1 = n;} 

And::And(){}  
And::~And(){}
int And::eval(){return inp1->eval() && inp2->eval();}
string And::get_input1()const{return input1;} 
string And::get_input2()const{return input2;}  
void And::set_input1(const string& n){input1 = n;}  
void And::set_input2(const string& n){input2 = n;}  

Or::Or(){}  
Or::~Or(){}
int Or::eval(){return inp1->eval() || inp2->eval();}
string Or::get_input1()const{return input1;} 
string Or::get_input2()const{return input2;}  
void Or::set_input1(const string& n){input1 = n;}  
void Or::set_input2(const string& n){input2 = n;} 

Not::Not(){}
Not::~Not(){}
int Not::eval(){return !inp1->eval();}
string Not::get_input2()const{return input1;}  
string Not::get_input1()const{return input1;} 
void Not::set_input1(const string& n){input1 = n;}  

FlipFlop::FlipFlop(){}
FlipFlop::~FlipFlop(){}
int FlipFlop::eval(){	
						int temp=inp1->eval();
						int x;
						if(temp == 1)
						{
							if(FlipFlop::former_out == 0) 
								x=!temp;
							else if(FlipFlop::former_out == 0)
								x= temp;
						}
						if(temp == 0)
						{
							if(FlipFlop::former_out == 0) 
								x= temp;
							else if(FlipFlop::former_out == 0)
								x= !temp;
						}
						return x;
					}
string FlipFlop::get_input1()const{return input1;}  
string FlipFlop::get_input2()const{return input1;}  
void FlipFlop::set_input1(const string& n){input1 = n;}
int FlipFlop::former_out = 0;


Decoder::Decoder(){}  
Decoder::~Decoder(){}
int Decoder::eval(){return 1;}
string Decoder::get_input1()const{return input1;} 
string Decoder::get_input2()const{return input2;}  
void Decoder::set_input1(const string& n){input1 = n;}  
void Decoder::set_input2(const string& n){input2 = n;}  




void func(string txt1, string txt2, string txt3){

	ifstream cp, ip;
	ofstream op;

	cp.open(txt1);
	ip.open(txt2);
	op.open(txt3);

	string str, line, temp;
	int i=0, inp_count=0, line_count=0, check=1, size, input;

	/* Calculation of array size */
	while (getline(cp, line)) {
        if(check){    // It enters here only 1 time because of check=0 assignment after first entry.
        	stringstream str_strm(line);
        	while (str_strm >> temp){
    			inp_count++;	// inp_count calculates input numbers.
 			}
			check=0;
		}
		line_count++;   // line_count calculates line numbers.
    }

	size = (inp_count-1) + (line_count-1);

	Gate **arr = new Gate*[size]; 
	for (int k = 0; k < size; ++k)
		arr[k] = new Gate; 

	cp.close();
	cp.open(txt1);

	while(!cp.eof()){
     	
     	cp >> str;
		/* Information Assignment Parts */
		if(str == "INPUT"){
		
			while(i<inp_count-1){
				Gate* inputObj;
				inputObj = new Gate; 
				arr[i] = inputObj;
				cp >> str;
				inputObj->set_name(str);	 // Input names assignment 
				i++;
			}
		}

		if(str == "OUTPUT"){
			Gate* outputObj;
			outputObj = new Gate; 
			arr[i] = outputObj;
			arr[i]->set_flag(2);
			/* Output names assignment */
			cp >> str;
			outputObj->set_name(str);  
			i++;
		}
		
		
		if(str == "AND"){
			And* andObj;
			andObj = new And; 
			arr[i] = andObj;
			/* Name assignment */
			cp >> str;
			andObj->set_name(str);  
			/* input1 and input2 assignment */ 
			cp >> str;
			andObj->set_input1(str);
			cp >> str;
			andObj->set_input2(str);
			i++;
		}

		if(str == "OR"){
			Or* orObj;
			orObj = new Or; 
			arr[i] = orObj;
			/* Name assignment */
			cp >> str;
			orObj->set_name(str);  
			/* input1 and input2 assignment */ 
			cp >> str;
			orObj->set_input1(str);
			cp >> str;
			orObj->set_input2(str);
			i++;
		}

		if(str == "NOT"){
			Not* notObj;
			notObj = new Not; 
			arr[i] = notObj;
			/* Name assignment */
			cp >> str;
			notObj->set_name(str);  
			/* input1 assignment */ 
			cp >> str;
			notObj->set_input1(str);
			i++;
		}


		if(str == "FLIPFLOP"){
			FlipFlop* flipflopObj;
			flipflopObj = new FlipFlop; 
			arr[i] = flipflopObj;
			/* Name assignment */
			cp >> str;
			flipflopObj->set_name(str);  
			/* input1 assignment */
			cp >> str;
			flipflopObj->set_input1(str); 
			i++;
		}
		
	
        /* Gate Connection Part */
		for(int k=0; k != size; k++){ 

			/* If input1 or input2 is found, inp1 and inp2(gate pointers) holds the adress of that locations.*/
			for(int m=0; m != size; m++){
				if(arr[m]->get_name() == arr[k]->get_input1()){    
					arr[k]->set_point1(arr[m]);   // Adress transfer
				}

				if(arr[m]->get_name() == arr[k]->get_input2()){    // Same process for input2
					arr[k]->set_point2(arr[m]);	
				}
			}

		}

	}


	for(int l=0; l!=size; l++){
           
		if(arr[l]->get_flag()==2){   // If it is equal to 0, that gate was 'not passed' that's why it is the last gate.
          	/* Reading input.txt and assigning numbers to arr[i].out */
			while(!ip.eof()){            
				ip >> input;       
                arr[0]->set_out(input);
                for(i=1; i<inp_count-1; i++){   
                	ip >> input;
	                arr[i]->set_out(input);
                }
                op << arr[l]->eval() << endl;    // Evaluation of last gate. 
			}

		}
	}

	cp.close();
	ip.close();
	op.close();
}


