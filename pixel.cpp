/*
 * pixel.cpp
 *
 *  Created on: 15 may. 2020
 *      Author: gerof
 */

#include "pixel.h"

pixel::pixel(){
	/*inicializo el color en 0 */
	color = 0;
	position.set_real(0.0);
	position.set_imag(0.0);
}

pixel::pixel(const pixel& p){
	/*copio los valores de otro pixel */
	position = p.position;
	color = p.color;
}

void pixel::set_color(int pix){
	color = pix;
}

int pixel::get_color(){
	return color;
}


void pixel::set_position(complex c){
	position = c;
}

complex pixel::get_position(){
	return position;
}


pixel::~pixel(){
	color = 0;

}
