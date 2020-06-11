// Prueba de la clase cmdline: dado un factor entero pasado por la
// línea de comando, leemos una secuencia de números que ingresan
// por la entrada estándar, los multiplicamos por ese factor, y
// luego mostramos el resultado por std::cout.
//
// $Id: main.cc,v 1.5 2012/09/15 12:23:57 lesanti Exp $

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <iostream>
#include <ctime>


#include "stack.h"
#include "cmdline.h"
#include "image.h"
#include "complex.h"
#include "pixel.h"

#define MASK_FLAG_IMAGIN 254 // 1111 1110
#define MASK_FLAG_NUMBER 253 // 1111 1101
#define MASK_FLAG_FUNCTION 251 // 1111 1011
#define MASK_FLAG_OPERATOR 247 // 1111 0111
#define MASK_FLAG_PARENTHESIS 239 // 1110 1111
#define MASK_FLAG_NEGATIVE 223 // 1101 1111


using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_factor(string const &);
static void opt_help(string const &);

/*enum flags {
	imaginary,
	number,
	function,
	operation,
	parenthesis,
	n_flags
};
*/

void lower_case (string &);

void lower_case (string & s){
	for(int i =0 ; i < s.length(); i++){
	    if (isalpha(s[i])){
	        if(isupper(s[i])){
	            s[i]=s[i]+32;
	        }
	    }
	}
}


stack<string> shunting_yard(string &);

stack<string> shunting_yard(string & tokens){

	// stack to store integers and operators.
	stack <string> numbers;
	stack <string> operators;
	string aux;
	string::size_type  next_position = 0;
	//int flag[n_flags];
	int flags = 128;
	int count_left_paren = 0 , count_right_paren = 0;

	lower_case(tokens);

	for(int i = 0; i < tokens.length(); i++){

/*************** se ingresa un espacio *******************/
		if(tokens[i] == ' ')
			continue;

/*************** se ingresa un parentesis ( *******************/
		else if(tokens[i] == '('){
			count_left_paren++;
			tokens[i] >> aux;
			operators.push(aux);
			flags = ~(flags | MASK_FLAG_PARENTHESIS); //FLAG = 0001 0000
		}

/*************** se ingresa un numero *******************/
		else if(isdigit(tokens[i]) || (tokens[i] == '.' && isdigit(tokens[i+1]))){

			double val = stod(tokens.substr(i), &next_position);
			if (flags == MASK_FLAG_NEGATIVE){
				val *= -1;
			}
			i += next_position;
			val >> aux;
			if (tokens[i]=='j' || tokens[i]=='i' || flags== MASK_FLAG_IMAGIN){
				aux+='j';
				i++;
			}
			numbers.push(aux);
			flags = ~(flags | MASK_FLAG_NUMBER); // FLAG = 0000 0010
		}



/*************** se ingresa un parentesis ) *******************/
		else if(tokens[i] == ')'){
			count_right_paren++;

			while(!operators.empty() && operators.top() != '(')
			{
				aux = operators.pop();
				numbers.push(aux);
			}
			// pop opening brace.
			if(operators.top() == '('){
				operators.pop();
			}
			else{
				cerr<< "Invalid arguments" <<endl;
				exit(1);
			}
			flags = ~(flags | MASK_FLAG_PARENTHESIS); //FLAG = 0001 0000
		}

/*************** se ingresa una coma  *******************/
		else if(tokens[i] == ','){
		}

/*************** se ingresa un numero complejo *******************/
		else if(tokens[i] == 'z'){
			tokens[i] >> aux;
			numbers.push(aux);
			flags = ~(flags | MASK_FLAG_NUMBER); // FLAG = 0000 0010
		}

/*************** se ingresa un numero imaginario *******************/
		else if(tokens[i] == 'i' || tokens[i] == 'j'){
			if (tokens[i]=='i' && tokens[i+1]=='m'){
				aux = "im";
				operators.push(aux);
				i++;
				flags = ~(flags | MASK_FLAG_FUNCTION); //FLAG = 0000 0100
			}
			else if(isdigit(tokens[i+1])){
				flags = ~(flags | MASK_FLAG_IMAGIN); // FLAG = 0000 0001
			}
			else{
				aux = "j";
				numbers.push(aux);
				flags = ~(flags | MASK_FLAG_IMAGIN); // FLAG = 0000 0001
			}
		}

		else if(tokens[i] == 'r' && tokens[i+1] == 'e'){
				aux = "re";
				operators.push(aux);
				i++;
				flags = ~(flags | MASK_FLAG_FUNCTION); //FLAG = 0000 0100
		}


		else if(tokens[i] == 'e'){
			if (tokens[i+1]=='x' && tokens[i+2]=='p'){
				aux = "exp";
				operators.push(aux);
				i+=2;
				flags = ~(flags | MASK_FLAG_FUNCTION); //FLAG = 0000 0100
			}
			else if (tokens[i+1]=='^'){
				aux = "exp";
				operators.push(aux);
				i++;
				flags = ~(flags | MASK_FLAG_FUNCTION); //FLAG = 0000 0100
			}
			else{
				aux = "e";
				numbers.push(aux);
				flags = ~(flags | MASK_FLAG_NUMBER); // FLAG = 0000 0010
			}
		}

		else if(tokens[i] == 'l'  && tokens[i+1]=='n'){
				aux = "ln";
				operators.push(aux);
				i++;
				flags = ~(flags | MASK_FLAG_FUNCTION); //FLAG = 0000 0100
		}

		else if(tokens[i] == 'a'  && tokens[i+1]=='b' && tokens[i+2]=='s'){
				aux = "abs";
				operators.push(aux);
				i+=2;
				flags = ~(flags | MASK_FLAG_FUNCTION); //FLAG = 0000 0100
		}

		else if(tokens[i] == 'p'  && tokens[i+1]=='h' && tokens[i+2]=='a'  && tokens[i+3]=='s' && tokens[i+4]=='e'){
				aux = "arg";
				operators.push(aux);
				i+=4;
				flags = ~(flags | MASK_FLAG_FUNCTION); //FLAG = 0000 0100
		}

		else if(tokens[i] == 's'  && (tokens[i+1]=='i' || tokens[i+1]=='e') && tokens[i+2]=='n'){
				aux = "sin";
				operators.push(aux);
				i+=2;
				flags = ~(flags | MASK_FLAG_FUNCTION); //FLAG = 0000 0100
		}

		else if(tokens[i] == 'c'  && tokens[i+1]=='o' && tokens[i+2]=='s'){
				aux = "cos";
				operators.push(aux);
				i+=2;
				flags = ~(flags | MASK_FLAG_FUNCTION); //FLAG = 0000 0100
		}

		else if(tokens[i] == 't'  && tokens[i+1]=='a' && tokens[i+2]=='n'){
				aux = "tan";
				operators.push(aux);
				i+=2;
				flags = ~(flags | MASK_FLAG_FUNCTION); //FLAG = 0000 0100
		}

/*************** se ingresa una letra distinta a las anteriores *******************/
				else if(isalpha(token[i])){
				}


		// Current token is an operator.
		else
		{

			while(!operators.empty() && operators(operators.top())
								>= operators(tokens[i])){
				int val2 = numbers.top();
				numbers.pop();

				int val1 = numbers.top();
				numbers.pop();

				char op = operators.top();
				operators.pop();

				numbers.push(maths(val1, val2, op));
			}

			// Push current token to 'operators'.
			operators.push(tokens[i]);
		}
	}

	//Do remaining operations
	while(!operators.empty()){
		int val2 = numbers.top();
		numbers.pop();

		int val1 = numbers.top();
		numbers.pop();

		char op = operators.top();
		operators.pop();

		numbers.push(maths(val1, val2, op));
	}

	// Top of 'numbers' contains result, return
	return numbers.top();
}

	return factor;
}

// Tabla de opciones de línea de comando. El formato de la tabla
// consta de un elemento por cada opción a definir. A su vez, en
// cada entrada de la tabla tendremos:
//
// o La primera columna indica si la opción lleva (1) o no (0) un
//   argumento adicional.
//
// o La segunda columna representa el nombre corto de la opción.
//
// o Similarmente, la tercera columna determina el nombre largo.
//
// o La cuarta columna contiene el valor por defecto a asignarle
//   a esta opción en caso que no esté explícitamente presente
//   en la línea de comandos del programa. Si la opción no tiene
//   argumento (primera columna nula), todo esto no tiene efecto.
//
// o La quinta columna apunta al método de parseo de la opción,
//   cuyo prototipo debe ser siempre void (*m)(string const &arg);
//
// o La última columna sirve para especificar el comportamiento a
//   adoptar en el momento de procesar esta opción: cuando la
//   opción es obligatoria, deberá activarse OPT_MANDATORY.
//
// Además, la última entrada de la tabla debe contener todos sus
// elementos nulos, para indicar el final de la misma.
//

/**************** Elementos globales ******************/
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "f", "factor", NULL, opt_factor, OPT_MANDATORY},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

static string factor;
static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)



/*****************************************************/

static void
opt_input(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la entrada
	// estándar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	//
	if (arg == "-") {
		iss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
	}
	else {
		ifs.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
										// sequence of characters (i.e., a C-string) representing
										// the current value of the string object.
		iss = &ifs;
	}

	// Verificamos que el stream este OK.
	//
	if (!iss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void
opt_output(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la salida
	// estándar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	if (arg == "-") {
		oss = &cout;	// Establezco la salida estandar cout como flujo de salida
	} else {
		ofs.open(arg.c_str(), ios::out | ios::binary);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);		// EXIT: Terminación del programa en su totalidad
	}
}

static void
opt_factor(string const &arg)
{
	istringstream iss(arg);
	// Intentamos extraer el factor de la línea de comandos.
	// Para detectar argumentos que únicamente consistan de
	// números enteros, vamos a verificar que EOF llegue justo
	// después de la lectura exitosa del escalar.
	//
	if (!(iss >> factor)
	    || !iss.eof()) {
		cerr << "non-integer factor: "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}

	if (iss.bad()) {
		cerr << "cannot read integer factor."
		     << endl;
		exit(1);
	}
}

static void
opt_help(string const &arg)
{
	cout << "cmdline -f factor [-i file] [-o file]"
	     << endl;
	exit(0);
}

void
multiply(istream *is, ostream *os)
{
	int num;

	while (*is >> num) {
		*os << num * factor
		    << "\n";
	}

	if (os->bad()) {
		cerr << "cannot write to output stream."
		     << endl;
		exit(1);
	}
	if (is->bad()) {
		cerr << "cannot read from input stream."
		     << endl;
		exit(1);
	}
	if (!is->eof()) {
		cerr << "cannot find EOF on input stream."
		     << endl;
		exit(1);
	}
}


void validate_img_format(){
	 string input_line;
	 getline(*iss,input_line);// read the first line : P2

	 if(input_line[0] != 'P' || input_line[1] != '2') {
		   cerr << "Error: Invalid image format" <<endl;
		  exit(1);
	 }
}

int main(int argc, char * const argv[])
{

	/*
	cmdline cmdl(options);	// Objeto con parametro tipo option_t (struct) declarado globalmente. Ver línea 51 main.cc
	cmdl.parse(argc, argv); // Metodo de parseo de la clase cmdline
	*/

	/***************************************************
	/* utilizado para calcular el tiempo de ejecucion *
	unsigned t0, t1;
	t0=clock();
	***************************************************/


	/* valido que la imagen sea la adecuada
	validate_img_format();

	image img_origin(iss); // crea la imagen a partir de lo que lee por cmdline

	multiply(iss, oss);	    // Función externa, no es un metodo de ninguna clase o estructura usada en el código

	image img_destin(img_origin); // crea la imagen de salida copiando la de entrada

	img_destin.transformation(img_origin , factor);  // se elige que funcion se aplicará a partir del valor de factor

	img_destin.export_to_file(oss); // se guarda el archivo en  la imagen de salida


	/***************************************************/
	/* utilizado para calcular el tiempo de ejecucion *
	t1 = clock();

	double time = (double(t1-t0)/CLOCKS_PER_SEC);
	cout << "Execution Time: " << time << endl;
	***************************************************/























}


