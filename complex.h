/*
 * complex.h
 *
 */

#ifndef complex_INCLUDED
#define complex_INCLUDED

#include <string>
#include <iostream>

class complex {
private:
	double real;
	double imaginario;

public:
	/*CONSTRUCTORES */
	complex();
	complex(const double &, const double &);
	complex(const complex &);

	/*DESTRUCTOR */
	~complex() ;

	/*FUNCIONES */
	double getReal();
	double getImag() ;

	void setReal(const double &);
	void setImag(const double &);

	double C_abs();
	double C_arg();
	void C_exp(const complex &);
	void ln(complex);

	complex convert_to_binomial(const double &, const double &);

	complex operator*(const double &);
	complex operator*(const complex &);

	complex operator/(const double &);
	complex operator/(const complex &);
	//complex operator*(const int &);
	complex operator+(const double &);
	complex operator+(const complex &);

	complex operator-(const double &);
	complex operator-(const complex &);

	complex operator^(const double &);
	complex operator^(const int &);
	complex operator^(const complex &);

	complex& operator = (const complex &);

	complex string2Complex(const std::string &);
	std::string complex2String(const complex &);

};

#endif
