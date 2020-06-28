/*
 * complex.cpp
 *
 */
#include <cmath>
#include "complex.h"
#include <iostream>

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

double complex::get_real(){
	return real;
}

double complex::get_imag(){
	return imaginario;
}

void complex::set_real(const double & xx){
	real=xx;
}

void complex::set_imag(const double & yy){
	imaginario=yy;
}


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

complex complex::operator^(complex &c){
	return z_exp(c*(z_ln(*this)));
}

complex complex::operator^(const double &d){
	double abs, arg;
	abs = this->z_abs();
	arg = this->z_arg();
	abs = pow(abs,d);
	arg *=d;
	return convert_to_binomial(abs, arg);
}

complex complex::operator^(const int &e){
	double abs, arg;
	abs = this->z_abs();
	arg = this->z_arg();
	abs = pow(abs,e);
	arg *=e;
	return convert_to_binomial(abs, arg);
}



double complex::z_abs(){
	return  sqrt(real * real + imaginario * imaginario);
}

double complex::z_arg(){
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



complex complex::z_exp(const complex & c){
	real = exp(c.real)*cos(c.imaginario);
	imaginario = exp(c.real)*sin(c.imaginario);
	return *this;
}

complex complex::z_ln(complex c){
	real = log(c.z_abs());
	imaginario = c.z_arg();
	return *this;
}

complex complex::z_sin(const complex & c){
	complex i(0,1);
	*this=((z_exp(i*c)-z_exp(i*c*(-1)))/(i*2));
	return *this;
}

complex complex::z_cos(const complex & c){
	complex i(0,1);
	*this=((z_exp(i*c)+z_exp(i*c*(-1)))/(2));
	return *this;
}

complex complex::z_tan(const complex & c){
	*this=(z_sin(c)/z_cos(c));
	return *this;
}

complex& complex::operator= (const complex & c){
	real = c.real;
	imaginario= c.imaginario;
return *this;
}



