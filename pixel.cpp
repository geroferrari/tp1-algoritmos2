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
	position.setReal(0.0);
	position.setImag(0.0);
}

pixel::pixel(const pixel& p){
	/*copio los valores de otro pixel */
	position = p.position;
	color = p.color;
}

void pixel::setColor(int pix){
	color = pix;
}

int pixel::getColor(){
	return color;
}


void pixel::setPosition(complex c){
	position = c;
}

complex pixel::getPosition(){
	return position;
}


pixel::~pixel(){
	color = 0;
}
