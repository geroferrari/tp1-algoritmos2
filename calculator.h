#ifndef CODIGO_CALCULATOR_H_
#define CODIGO_CALCULATOR_H_

#include <string>
#include <cmath>

#include "stack.h"
#include "complex.h"


enum type_flags {
	IMAGINARY,
	NEGATIVE,
	NUMBER,
	OPERATOR,
	FUNCTION,
	N_FLAGS
};

void shunting_yard(string &, stack<string> &); //pasa el string de entrada arpn
complex  calculator_rpn(stack<string>  &, const complex &); // realiza la cuenta a partir del rpn


/******** FUNCIONES UTILIZADAS POR SHUNTING_YARD  Y CALCULATOR_RPN *********/
void lower_case (string &);

/* para saber si el string es una funcion */
bool is_a_function(const string &, string &, int &);
bool is_a_function(const string &);

/* para saber si el string es un operador */
bool is_operator(const char &, int &, string &);
bool is_operator(const char &, int &);
bool is_operator(const string &);

/* utilizada en calculator_rpn, realiza la operacion */
complex make_operation(const string &, complex, complex);

/*utilizada en calculator_rpn , realiza la funcion */
complex make_function(const string &, const complex);


#endif /* CODIGO_CALCULATOR_H_ */
