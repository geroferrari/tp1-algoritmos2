#ifndef CODIGO_CALCULATOR_H_
#define CODIGO_CALCULATOR_H_

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

using namespace std;


bool is_a_function(const string &, string &, int &);
bool is_a_function(const string &);

bool is_operator(const char &, int &, string &);
bool is_operator(const char &, int &);
bool is_operator(const string &);

complex make_operation(const string &, complex, complex);
complex make_function(const string &, const complex);

enum type_flags {
	imaginary,
	negative,
	n_flags
};


void lower_case (string &);
void shunting_yard(string &, stack<string> &);
complex  calculator_rpn(stack<string>  &, const complex &);




#endif /* CODIGO_CALCULATOR_H_ */
