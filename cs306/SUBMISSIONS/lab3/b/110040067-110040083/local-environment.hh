
/*********************************************************************************************

                                cfglp : A CFG Language Processor
                                --------------------------------

           About:

           Implemented   by  Tanu  Kanvar (tanu@cse.iitb.ac.in) and Uday
           Khedker    (http://www.cse.iitb.ac.in/~uday)  for the courses
           cs302+cs306: Language  Processors  (theory and  lab)  at  IIT
           Bombay.

           Release  date  Jan  15, 2013.  Copyrights  reserved  by  Uday
           Khedker. This  implemenation  has been made  available purely
           for academic purposes without any warranty of any kind.

           Documentation (functionality, manual, and design) and related
           tools are  available at http://www.cse.iitb.ac.in/~uday/cfglp


***********************************************************************************************/

#ifndef LOCAL_ENVIRONMENT_HH
#define LOCAL_ENVIRONMENT_HH

#include<string>
#include<map>

#define VAR_SPACE "         "

using namespace std;

typedef enum
{
	int_result,
	void_result, 
	float_result
} Result_Enum;

class Eval_Result;
class Local_Environment;

// one bad way is to make all the things float, i.e. don't consider int, because we will print using print_ast using recursion, and hence we do not need to print using the current value, but it is not a good way, hence will not use it

class Eval_Result 
{
protected:
	Result_Enum result_type;
	bool is_conditional;
public:
	virtual double get_value();
	virtual void set_value(double value);
	
	//added by me
	virtual void set_conditional(bool temp);
	virtual bool get_conditional();

	virtual bool is_variable_defined();
	virtual void set_variable_status(bool def);

	virtual void set_result_enum(Result_Enum res) = 0;
	virtual Result_Enum get_result_enum() = 0;
};

class Eval_Result_Value:public Eval_Result
{
public:
	virtual void set_value(double number) = 0;
	virtual double get_value() = 0;

	virtual bool is_variable_defined() = 0;
	virtual void set_variable_status(bool def) = 0;

	virtual void set_result_enum(Result_Enum res) = 0;
	virtual Result_Enum get_result_enum() = 0;
};

class Eval_Result_Value_Int:public Eval_Result_Value
{
	int value;
	bool defined;
public:
	Eval_Result_Value_Int();
	~Eval_Result_Value_Int();

	void set_value(double number);
	double get_value();

	void set_variable_status(bool def);
	bool is_variable_defined();

	void set_result_enum(Result_Enum res);
	Result_Enum get_result_enum();
	
	void set_conditional(bool temp);
	bool get_conditional();
};

class Eval_Result_Value_Float:public Eval_Result_Value
{
	double value;
	bool defined;
public:
	Eval_Result_Value_Float();
	~Eval_Result_Value_Float();

// these 2 are giving errors, because in eval_result_value, the argument type and return type are int whereas here we are using float
	void set_value(double number);
	double get_value();

	void set_variable_status(bool def);
	bool is_variable_defined();

	void set_result_enum(Result_Enum res);
	Result_Enum get_result_enum();
	
	void set_conditional(bool temp);
	bool get_conditional();
};



class Local_Environment
{
	map<string, Eval_Result_Value *> variable_table;

public:
	Local_Environment();
	~Local_Environment();

	void print(ostream & file_buffer);
	bool is_variable_defined(string name);
	Eval_Result_Value * get_variable_value(string name);
	void put_variable_value(Eval_Result_Value & value, string name);
	bool does_variable_exist(string name);
};

extern Local_Environment interpreter_global_table;

#endif
