#include <iostream>
#include <cmath>
#include "image.h"
#include "calculator.h"

using namespace std;


/******************** CONSTRUCTORES ************************/
/* constructor por defecto - inicializa los valores en 0 */
image::image(){
	comment = '\0';
	rows = 0;
    columns = 0;
    greys = 0;
    pixel_val = 0;
}

/*constructor a partir del tamaño y cantidad de colores, inicializa
 * la matriz con valor 0
 */
image::image(const int &num_row, const int &num_col, const int &grey_scale){
    comment = '\0';
	rows = num_row;
    columns = num_col;
    greys = grey_scale;

    pixel_val = new pixel* [rows];
    for(int i = 0; i < rows; i++){
        pixel_val[i] = new pixel [columns];
        for(int j = 0; j < columns; j++){
            (pixel_val[i][j]).set_color(0);
        }
    }
}

image::image(istream *is){
	string hashtag;
	/* primero se verifica si la imagen posee comentario */
	(*is) >> hashtag;
	if (hashtag[0] == '#'){
		 getline(*is,comment); // si tiene comentario se lo guarda
		 comment = hashtag + comment;
		 (*is) >> columns; // obtiene el tamaño de las columnas
	}
	 else{
		 comment = '\0'; // si no tiene comentario guarda un "\0"
		 columns = stoi(hashtag); //si no tiene comentarios, lo que leyó antes era el tamaño de las columnas
	 }

	 (*is) >> rows >> greys; //guarda el valor de las  filas y de la escala grises


	 /*variables auxiliares */
	 int color;
	 /* se definen los saltos entre posiciones */
	 double x = (double) 2/(columns-1);
	 double y = (double) 2/(rows-1);

	 complex x_position(x,0.0);
	 complex y_position(0.0,y);
	 complex init_position(-1, 1);
	 complex init_position_n(-1, 1);
	 pixel_val = new pixel* [rows];  // pide memoria para las filas
	 for(int r = 0; r < rows; r++){
		 pixel_val[r] = new pixel [columns]; //pido memoria para las columnas
		 init_position_n = init_position - (y_position*r);
		 for (int c = 0; c < columns; c++) {
			 if (is->eof()){
					 cerr << "The file has less elements than it says" << endl;
					 exit(1);
				 }
			 *is >> color;
			 if (color > greys) {
				 cerr << "The color is bigger than the scale." <<endl;
				 exit(1);
			 }

			 pixel_val[r][c].set_color(color);
			 pixel_val[r][c].set_position(init_position_n + (x_position*c));

		 }
		 pixel_val[r][0].set_position(init_position_n);

	 }
	 string aux;
	 if(!is->eof()){
		 *is >> aux;
		 if (aux != "\0"){
			cerr << "The file has more elements than it says"
			     << endl;
			exit(1);
		 }
	 }
	 if (is->bad()) {
		cerr << "cannot read from input stream."
			 << endl;
		exit(1);
	}
}

/* constructor por copia */
image::image(const image& old_image)
{
    rows = old_image.rows;
    columns = old_image.columns;
    greys = old_image.greys;
	comment = old_image.comment;
    pixel_val = new pixel* [rows];


	for(int r = 0; r < rows; r++){
		pixel_val[r] = new pixel [columns];

		for (int c = 0; c < columns; c++) {
			 pixel_val[r][c].set_color(0);
			 pixel_val[r][c].set_position(old_image.pixel_val[r][c].get_position());
		 }
	 }
}


/******************** DESTRUCTOR ************************/
image::~image()
{
    for(int i = 0; i < rows; i++){
        delete[] pixel_val [i];
    }
    delete[] pixel_val;
    pixel_val = NULL;

	comment = "\n";
    rows = 0;
    columns = 0;
    greys = 0;

}




void image::transformation(const image & origen,  stack<string> &stack_equation){
	complex new_value;
	double x_step = (double) 2/(columns-1);
	double y_step = (double) 2/(rows-1);

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			new_value = pixel_val[i][j].get_position(); //obtengo el valor del pixel
			stack<string> stack_temp(stack_equation); //constructor por copia de stack, para no perder el original

			new_value = calculator_rpn(stack_temp, new_value); //realizo el calculo con el stack nuevo
			if (!stack_temp.empty()){
				cerr << "Invalid argument in equation" << endl;
				exit(1);
			}

			if(abs(new_value.get_real()) <= 1.0 && abs(new_value.get_imag()) <= 1.0){
				int r = round((-new_value.get_imag()+1)/y_step);
				int c = round((new_value.get_real()+1)/x_step);
				pixel_val[i][j].set_color(origen.pixel_val[r][c].get_color());
			}
		}
	}

}



void image::negate_image(const image &origen)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
            pixel_val[i][j].set_color(-(origen.pixel_val[i][j]).get_color() + greys);
    }

}


ostream& operator<<(ostream &os, const image& img){
	os << "P2" <<endl;

	if(img.comment != "\0")
	{
		os << img.comment <<endl;
	}
	os << img.columns << " " << img.rows << endl;
	os << img.greys << endl;

	for(int i = 0; i < img.rows; i++){
          for(int j = 0; j < img.columns; j++){
        	  os << img.pixel_val[i][j].get_color() << " ";
          }
          os << endl;
    }
	if (os.bad()) {
		cerr << "cannot write to output stream."
			 << endl;
		exit(1);
	}
	return os;
}

void image::set_image( int &num_rows,  int &num_cols,  int &grey_scale)
{
    rows = num_rows;
    columns = num_cols;
    greys = grey_scale;
}

/**
 * returns the number of rows, columns and gray levels
 */
void image::get_image(int &num_rows,  int &num_cols,  int &grey_scale)
{
    num_rows = rows;
    num_cols = columns;
    grey_scale = greys;

}

void image::set_rows(const int &num_rows){
		rows = num_rows;
}

void image::set_columns(const int &num_columns){
	columns = num_columns;
}

void image::set_greys(const int &grey_scale){
	 greys = grey_scale;
}


int& image::get_rows(){
	return rows;
}

int& image::get_columns(){
	return columns;
}

int& image::get_greys(){
	return greys;
}

/**
 * returns the gray value of a specific pixel
 */

int image::get_pixel_color(const int num_row, const int num_col)
{
	if ((rows < num_row) || (columns < num_col)){
		cerr << "error: very long rows or columns" <<endl;
		exit(1);
	}

    return pixel_val[num_row][num_col].get_color();
}

