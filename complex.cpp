/*
 * complex.cpp
 *
 */
#include <cmath>
#include <iostream>
#include <string>
#include "complex.h"

using namespace std;



complex ::complex (){
	real=0.0;
	imaginario=0.0;
}

complex ::complex (const complex & c){
	real=c.real;
	imaginario=c.imaginario;
}

complex ::complex (const double& a, const double& b){
	real=a;
	imaginario=b;
}

complex:: ~complex(){
	real = 0;
	imaginario =0;
}

double complex::getReal(){
	return real;
}

double complex::getImag(){
	return imaginario;
}

void complex::setReal(const double & xx){
	real=xx;
}

void complex::setImag(const double & yy){
	imaginario=yy;
}

/*
complex complex:: operator*(const int & c){
	return  complex (real *c, imaginario *c );
}
*/

complex complex:: operator*(const double &c){
	return complex (real * c, imaginario *c );
}



complex complex:: operator*(const complex &c){
	return complex (real * c.real - imaginario *c.imaginario , c.real*imaginario + c.imaginario *real);
}



complex complex:: operator/(const double &c){
	return complex (real/c, imaginario/c );
}



complex complex:: operator/(const complex &c){
	complex num(c);
	num.imaginario = -c.imaginario;
	num = (*this) * num;
	double denom = c.real*c.real + c.imaginario*c.imaginario;
	return (num/denom);
}




complex complex::operator+(const double &c){
	return complex(real + c , imaginario);
}

complex complex::operator+(const complex &c){
	return complex(real + c.real , imaginario + c.imaginario );
}


complex complex::operator-(const double &c){
	return complex(real - c , imaginario);
}

complex complex::operator-(const complex &c){
	return complex(real - c.real , imaginario - c.imaginario);
}



complex complex::operator^(const double &d){
	double abs, arg;
	abs = this->C_abs();
	arg = this->C_arg();
	abs = pow(abs,d);
	arg *=d;
	return convert_to_binomial(abs, arg);
}

complex complex::operator^(const int &e){
	double abs, arg;
	abs = this->C_abs();
	arg = this->C_arg();
	abs = pow(abs,e);
	arg *=e;
	return convert_to_binomial(abs, arg);
}


double complex::C_abs(){
	return  sqrt(real * real + imaginario * imaginario);
}

double complex::C_arg(){
	if (real > 0) {
		return atan(imaginario/real);
	}
	else if (real < 0){
		if(imaginario >=0){
			return (atan(imaginario/real) + M_PI);
		}
		else if (imaginario <0){
			return (atan(imaginario/real) - M_PI);
		}
	}
	else if (real == 0) {
		if(imaginario == 0){
			return 0.0;
		}
		else if (imaginario > 0){
			return (M_PI/2);
		}
		else if (imaginario < 0) {
			return  (-M_PI/2);
		}
	  }
	return 0;
}

complex complex::convert_to_binomial(const double &abs, const double &arg){
	return complex(abs * cos(arg), abs * sin(arg));
}



void complex::C_exp(const complex & c){
	real = exp(c.real)*cos(c.imaginario);
	imaginario = exp(c.real)*sin(c.imaginario);
}

void complex::ln(complex c){
	real = log(c.C_abs());
	imaginario = c.C_arg();
}

complex& complex::operator= (const complex & c){
	real = c.real;
	imaginario= c.imaginario;
return *this;
}

complex complex::string2Complex(const string &s)
{
	size_t division;
	string first, second;
	bool neg = 0;
	
	division = s.find('j');

	//cout << "Pos: " << division << endl;

	first = s.substr(0,division-1);
	second = s.substr(division+1);

	//cout << "First: " << first << " , Second: " << second << endl;

	real = stod(first);
	if(s[division] == '+')
	{
		imaginario = stod(second);
	}
	else
	{
		imaginario = stod(second);
	}
	
	return complex(real, imaginario);

}

string complex::complex2String(const complex & c)
{
	if(c.imaginario >= 0)
	{
		return to_string(c.real) + "+j" + to_string(c.imaginario);
	}
	else
	{
		return to_string(c.real) + "-j" + to_string(c.imaginario);
	}
}
