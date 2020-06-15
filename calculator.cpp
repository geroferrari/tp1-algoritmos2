#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <iostream>
#include <ctime>
#include <cmath>


#include "stack.h"
#include "cmdline.h"
#include "image.h"
#include "complex.h"
#include "pixel.h"
#include "calculator.h"


using namespace std;

void lower_case (string & s){
	for(unsigned int i =0 ; i < s.length(); i++){
	    if (isalpha(s[i])){
	        if(isupper(s[i])){
	            s[i]=s[i]+32;
	        }
	    }
	}
}

bool is_a_function(const string &tokens, string &function , int &i){
	if (tokens[i]=='i' && tokens[i+1]=='m'){
		function = "im";
		i++;
		return true;
	}
	else if(tokens[i] == 'r' && tokens[i+1] == 'e'){
		function = "re";
		i++;
		return true;
	}
	else if(tokens[i] == 'e'){
		if (tokens[i+1]=='x' && tokens[i+2]=='p'){
			function = "exp";
			i+=2;
			return true;
		}
		else if (tokens[i+1]=='^'){
			function = "exp";
			i++;
			return true;
		}
	}

	else if(tokens[i] == 'l'  && tokens[i+1]=='n'){
			function = "ln";
			i++;
			return true;
	}

	else if(tokens[i] == 'a'  && tokens[i+1]=='b' && tokens[i+2]=='s'){
			function = "abs";
			i+=2;
			return true;
	}

	else if(tokens[i] == 'p' && tokens[i+1]=='h' && tokens[i+2]=='a' && tokens[i+3]=='s' && tokens[i+4]=='e'){
			function = "phase";
			i+=4;
			return true;
	}

	else if(tokens[i] == 's'  && (tokens[i+1]=='i' || tokens[i+1]=='e') && tokens[i+2]=='n'){
			function = "sin";
			i+=2;
			return true;
	}

	else if(tokens[i] == 'c'  && tokens[i+1]=='o' && tokens[i+2]=='s'){
			function = "cos";
			i+=2;
			return true;
	}

	else if(tokens[i] == 't'  && tokens[i+1]=='a' && tokens[i+2]=='n'){
			function = "tan";
			i+=2;
			return true;
	}

	return false;
}

bool is_a_function(const string &tokens){
	if (tokens[0]=='i' && tokens[1]=='m'){
		return true;
	}
	else if(tokens[0] == 'r' && tokens[1] == 'e'){

		return true;
	}
	else if(tokens[0] == 'e'){
		if (tokens[1]=='x' && tokens[2]=='p'){
			return true;
		}
		else if (tokens[1]=='^'){

			return true;
		}
	}

	else if(tokens[0] == 'l'  && tokens[1]=='n'){
			return true;
	}

	else if(tokens[0] == 'a'  && tokens[1]=='b' && tokens[2]=='s'){
			return true;
	}

	else if(tokens[0] == 'p' && tokens[1]=='h' && tokens[2]=='a' && tokens[3]=='s' && tokens[4]=='e'){
			return true;
	}

	else if(tokens[0] == 's'  && (tokens[1]=='i' || tokens[1]=='e') && tokens[2]=='n'){
			return true;
	}

	else if(tokens[0] == 'c'  && tokens[1]=='o' && tokens[2]=='s'){
			return true;
	}

	else if(tokens[0] == 't'  && tokens[1]=='a' && tokens[2]=='n'){
			return true;
	}

	return false;
}



bool is_operator(const char & token,   int & precedence, string & operation){
	if(token=='+'){
		operation = "+";
		precedence = 2;
		return true;
	}
	else if(token=='-'){
		operation = "-";
		precedence = 2;
		return true;
	}
	else if(token=='*'){
		operation = "*";
		precedence = 3;
		return true;
	}
	else if(token=='/'){
		operation = "/";
		precedence = 3;
		return true;
	}
	else if(token=='^'){
		operation = "^";
		precedence = 4;
		return true;
	}
	else
		return false;
}

bool is_operator(const char & token,   int & precedence){
	if(token=='+'){
		precedence = 2;
		return true;
	}
	else if(token=='-'){
		precedence = 2;
		return true;
	}
	else if(token=='*'){
		precedence = 3;
		return true;
	}
	else if(token=='/'){
		precedence = 3;
		return true;
	}
	else if(token=='^'){
		precedence = 4;
		return true;
	}
	else
		return false;
}

bool is_operator(const string & token){
	if(token=="+"){
		return true;
	}
	else if(token=="-"){
		return true;
	}
	else if(token=="*"){
		return true;
	}
	else if(token=="/"){
		return true;
	}
	else if(token=="^"){
		return true;
	}
	else
		return false;
}


void shunting_yard(string & tokens, stack<string> & numbers){


	// stack to store operators.
	stack <string> operators;
	string pivot_str;
	string::size_type  next_position = 0;
	int flag[n_flags] = {}, old_precedence = 0, new_precedence = 0;

	lower_case(tokens);

	for(int i = 0; (unsigned)i < tokens.length(); i++){


/*************** se ingresa un espacio *******************/
		if(tokens[i] == ' ')
			continue;

/*************** se abre un parentesis *******************/
		else if(tokens[i] == '('){
			pivot_str = "(";
			operators.push(pivot_str);
			old_precedence = 1;
			if (tokens[i+1]=='-'){
				flag[negative]=1;
			}
		}

/*************** se ingresa un numero *******************/
		else if(isdigit(tokens[i]) || (tokens[i] == '.' && isdigit(tokens[i+1]))){

			double val = stod(tokens.substr(i), &next_position);
			i += next_position-1;
			pivot_str = to_string(val);

			if (tokens[i+1]=='j' || tokens[i+1]=='i' || flag[imaginary]==1){
				pivot_str+='j';
				flag[imaginary]=0;
			}
			if (flag[negative] == 1){
				pivot_str = '-' + pivot_str;
				flag[negative]=0;
			}
			numbers.push(pivot_str);
		}

/*************** se cierra un parentesis *******************/
		else if(tokens[i] == ')'){
			while(!operators.empty() && operators.get_top() != "("){
				numbers.push(operators.pop());
			}
			// pop opening brace.
			if(operators.get_top() == "("){
				operators.pop();
			}
			else{
				cerr<< "Invalid parenthesis match" <<endl;
				exit(1);
			}
			old_precedence = 0;
			if(operators.empty()){
				continue;
			}
			pivot_str = operators.get_top();
			if(is_a_function(pivot_str) == true){
				pivot_str = operators.pop();
				numbers.push(pivot_str);
				if(!operators.empty()){
					pivot_str = operators.get_top();
				}
			}
			if(is_operator(pivot_str[0], new_precedence) == true){
				old_precedence = new_precedence;
			}

		}

/*************** se ingresa una coma  *******************/
		else if(tokens[i] == ','){
			continue;
		}

/*************** se ingresa una variable compleja *******************/
		else if(tokens[i] == 'z'){
			pivot_str = "z";
			numbers.push(pivot_str);
		}

/************************ se ingresa una funcion ************************/
		else if(is_a_function(tokens,pivot_str,i)){
			operators.push(pivot_str);
		}

/*************** se ingresa un numero imaginario *******************/
		else if(tokens[i] == 'i' || tokens[i] == 'j'){
			if(isdigit(tokens[i-1])){
				continue;
			}
			else if(isdigit(tokens[i+1])){
				flag[imaginary]=1;
			}
			else{
				pivot_str = "j";
				if (flag[negative]==1){
					pivot_str = "-" + pivot_str;
					flag[negative]=0;
				}
				numbers.push(pivot_str);
			}
		}

/*************** se ingresa la constante de Euler *******************/
		else if(tokens[i] == 'e'){
			pivot_str = to_string(M_E);
			numbers.push(pivot_str);
		}

/*************** se ingresa la constante Pi *******************/
		else if(tokens[i] == 'p' && tokens[i+1] == 'i'){
			pivot_str = to_string(M_PI);
			numbers.push(pivot_str);
			i++;
		}

/*************** se ingresa un operador *******************/
		else if (is_operator(tokens[i],new_precedence,pivot_str)==true && flag[negative]==0){
			if ((operators.empty() && numbers.empty()) && pivot_str=="-"){
				flag[negative]=1;
				continue;
			}
			while (new_precedence<=old_precedence){
				numbers.push(operators.pop());
				if(operators.empty()){
					break;
				}
				if(!is_operator(operators.get_top()[0],old_precedence)){
					break;
				}
			}
			operators.push(pivot_str);
			old_precedence = new_precedence;
		}
	}



	while(!operators.empty()){
		if (operators.get_top() == "("){
			cerr << "Missing Brackets" << endl;
			exit(1);
		}
		numbers.push(operators.pop());
	}
}

complex make_operation(const string & operation, complex  left_value,  complex  right_value){
	if(operation == "+"){
		return left_value+right_value;
	}
	else if(operation == "-"){
		return left_value-right_value;
	}
	else if(operation == "*"){
		return left_value*right_value;
	}
	else if(operation == "/"){
		return left_value/right_value;
	}
	else if(operation == "^"){
		return left_value^right_value;
	}
	else{
		cerr << "Cannot be solved" << endl;
		exit(1);
	}
}

complex make_function(const string & function, const complex  value){
    complex new_value(value);
	if(function == "exp"){
		return new_value.z_exp(value);
	}
	else if(function == "ln"){
		return new_value.z_ln(value);
	}
	else if(function == "sin"){
		return new_value.z_sin(value);
	}
	else if(function == "cos"){
		return new_value.z_cos(value);
	}
	else if(function == "tan"){
		return new_value.z_tan(value);
	}
	else if(function == "abs"){
		return complex(new_value.z_abs(),0.0);
	}
	else if(function == "phase"){
		return complex(new_value.z_arg(),0.0);
	}
	else if(function == "re"){
		return complex(new_value.get_real(),0.0);
	}
	else if(function == "im"){
		return complex(new_value.get_imag(),0.0);
	}
	else{
		cerr << "Cannot be solved" << endl;
		exit(1);
	}
}


complex  calculator_rpn(stack<string> & stack_output, const complex & variable){
	if(stack_output.empty()){
		cerr << "Error calculator RPN" << endl;
		exit(1);
	}
	string pivot_str;
	pivot_str = stack_output.pop();

	//stack<string> stack_aux(stack_output.get_next_top(),stack_output.get_size()-1);

	if (is_operator(pivot_str)){
		return make_operation(pivot_str, calculator_rpn(stack_output, variable), calculator_rpn(stack_output, variable));
	}

	else if (isdigit(pivot_str[0]) || isdigit(pivot_str[1])){
		if (pivot_str[pivot_str.length()-1] == 'j'){
			pivot_str.pop_back();
			return complex (0.0,stod(pivot_str));
		}

		return complex (stod(pivot_str),0.0);
	}

	else if (is_a_function(pivot_str)){
		return make_function(pivot_str, calculator_rpn(stack_output, variable));
	}

	else if (pivot_str == "z"){
		return variable;
	}

	else if (pivot_str == "j"){
		return complex(0.0,1);
	}

	else if (pivot_str == "-j"){
			return complex(0.0,-1);
		}

	else{
		cerr << "Error in calculator eweweewRPN" << endl;
		exit(1);
	}
}


