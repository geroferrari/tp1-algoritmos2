/*
 * pixel.h
 *
 *
 */

#ifndef PIXEL_H_
#define PIXEL_H_
#include "complex.h"


class pixel {
public:
	/*contructores */
	pixel(); //contructor por defecto
	pixel(const pixel&); // constructor por copia

	/*Destructor */
	~pixel();

	/*Metodos */
	void set_color(int); //seteo el color con el valor pasado
	int get_color(); // obtengo el color de un pixel
	void set_position(complex); //seteo la posicion compleja
	complex get_position(); // obtengo la posicion de un pixel



private:
	complex position; //posicion del pixel - tipo complejo
	int color; // color del pixel - tipo entero

};

#endif /* PIXEL_H_ */
