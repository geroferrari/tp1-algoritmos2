/*
 * complex.h
 *
 */

#ifndef complex_INCLUDED
#define complex_INCLUDED


class complex {
private:
	double real;
	double imaginario;

public:
	/**********CONSTRUCTORES **********/
	complex();
	complex(const double &, const double &);
	complex(const complex &);

	/***********DESTRUCTOR *************/
	~complex() ;

	/******* METODOS *****************/
	double get_real();
	double get_imag() ;

	void set_real(const double &);
	void set_imag(const double &);


	/******** FUNCIONES MATEMATICAS *******/
	double z_abs();
	double z_arg();
	complex z_ln(complex);
	complex z_exp(const complex &);
	complex z_sin(const complex &);
	complex z_cos(const complex &);
	complex z_tan(const complex &);

	complex convert_to_binomial(const double &, const double &);

	/******** OPERADORES *******/
	complex operator*(const double &);
	complex operator*(const complex &);

	complex operator/(const double &);
	complex operator/(const complex &);

	complex operator+(const double &);
	complex operator+(const complex &);

	complex operator-(const double &);
	complex operator-(const complex &);

	complex operator^(const double &);
	complex operator^(const int &);
	complex operator^(complex &);

	complex& operator = (const complex &);


};

#endif
