#ifndef SEFA_CICEK_1801042657_H
#define SEFA_CICEK_1801042657_H
#include <iostream>

using namespace std;

class Gate
{
public:
	Gate();
	~Gate();
	string get_name()const;
	void set_name(const string& n); 
	virtual string get_input1()const;
	virtual string get_input2()const;
	virtual string get_input3()const;
	virtual string get_input4()const;
	virtual void set_input1(const string& n); 
	virtual void set_input2(const string& n); 
	virtual void set_input3(const string& n); 
	virtual void set_input4(const string& n); 
	virtual int eval(); 
	virtual void set_out(int o);
	int get_out();
	void set_point1(Gate* p1){inp1 = p1;} 
	void set_point2(Gate* p2){inp2 = p2;} 
	Gate* get_point1(){return inp1;} 
	Gate* get_point2(){return inp2;} 
	void set_flag(int so){flag = so;} 
	int get_flag(){return flag;} 
protected:
	int out;
	int flag = 0;
	string name; 
	string input1;
	string input2;
	string input3;
	string input4;
	Gate* inp1;
	Gate* inp2;
};


class Output : public Gate
{
public:
	Output();  
	~Output();
	virtual int eval();
	virtual string get_input1()const;   
	virtual void set_input1(const string& n);  

private:
	string input1;
};


class And : public Gate
{
public:
	And(); 
	~And();
	virtual int eval();
	virtual string get_input1()const;  
	virtual string get_input2()const;  
	virtual void set_input1(const string& n);
	virtual void set_input2(const string& n);

private:
	string input1;
	string input2;
};



class Or : public Gate
{
public:
	Or();
	~Or();
	virtual int eval();
	virtual string get_input1()const;  
	virtual string get_input2()const;  
	virtual void set_input1(const string& n); 
	virtual void set_input2(const string& n); 

private:
	string input1;
	string input2;
};


class Not : public Gate
{
public:
	Not();
	~Not();
	virtual int eval();
	virtual string get_input1()const;  
	virtual string get_input2()const;  
	virtual void set_input1(const string& n);  

private:
	string input1;
};


class FlipFlop : public Gate
{
public:
	FlipFlop();
	~FlipFlop();
	virtual int eval();
	virtual string get_input1()const;  
	virtual string get_input2()const;  
	virtual void set_input1(const string& n); 
private:
	string input1;
	static int former_out;
};



class Decoder : public Gate
{
public:
	Decoder();  
	~Decoder();
	virtual int eval();
	virtual string get_input1()const;  
	virtual string get_input2()const;  
	virtual void set_input1(const string& n);  
	virtual void set_input2(const string& n);  
private:
	string input1;
	string input2;
};

#endif