#include <iostream>
#include "image.h"
#include "stack.h"
#include <cmath>
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
            (pixel_val[i][j]).setColor(0);
        cout << (pixel_val[i][j]).getColor() << '\t';
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

	 pixel_val = new pixel* [rows];  // pide memoria para las filas

	 /*variables auxiliares */
	 int color;
	 /* se definen los saltos entre posiciones */
	 double x = (double) 2/(columns-1);
	 double y = (double) 2/(rows-1);

	 complex x_position(x,0.0);
	 complex y_position(0.0,y);
	 complex init_position(-1, 1);
	 complex init_position_n(-1, 1);

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

			 pixel_val[r][c].setColor(color);
			 pixel_val[r][c].setPosition(init_position_n + (x_position*c));

		 }
		 pixel_val[r][0].setPosition(init_position_n);

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
			 pixel_val[r][c].setColor(0);
			 pixel_val[r][c].setPosition(old_image.pixel_val[r][c].getPosition());
		 }
	 }
}


/******************** DESTRUCTOR ************************/
image::~image()
{
	comment = "\n";
    rows = 0;
    columns = 0;
    greys = 0;
    for(int i = 0; i < rows; i++)
        delete[] pixel_val [rows];
    delete[] pixel_val;
    pixel_val = NULL;
}

/*
void image::transformation(const image & origen, const string &factor){
	if (factor == 0){
		this->id_z(origen);
	}
	else if (factor == 1){
		this->exp_z(origen);
	}
	else if (factor == 2){
		this->ln_z(origen);
	}
	else if(factor == 3){
		this->add_exp_ln(origen);

	} else if (factor == 4){
		this->negateimage(origen);
	}
	else{
		cerr << "Invalid Transformation function" << endl;
		exit(1);
	}

}

*/
void image::add_exp_ln(const image& old_image){
     rows = old_image.rows;
     columns = old_image.columns;
     greys = old_image.greys;

     image aux(old_image);

     this->exp_z(old_image);
	 aux.ln_z(old_image);

	 for(int r = 0; r < rows; r++){
		 for (int c = 0; c < columns; c++) {
		 	pixel_val[r][c].setColor(pixel_val[r][c].getColor() + aux.pixel_val[r][c].getColor());
		 }
	 }

}

void image::id_z(const image& old_image)
{
    rows = old_image.rows;
    columns = old_image.columns;
    greys = old_image.greys;

	for(int r = 0; r < rows; r++){
		for (int c = 0; c < columns; c++) {
			 pixel_val[r][c].setColor(old_image.pixel_val[r][c].getColor());
			 pixel_val[r][c].setPosition(old_image.pixel_val[r][c].getPosition());
		 }
	 }
}

void image::exp_z(const image & origen)
{
    complex new_value;

    for(int i = 0; i < rows; i++){ //Hace una busqueda binaria para reales e imaginarios, para cada pixel
        for(int j = 0; j < columns; j++){
        	new_value.C_exp(pixel_val[i][j].getPosition());
            if(abs(new_value.getReal()) <= 1.0 && abs(new_value.getImag()) <= 1.0)
            {	
			
				double real_part = new_value.getReal();
				double imag_part = new_value.getImag();
				double distance1, distance2;

				int f=-1,h=-1;
				int first_real, last_real, mid_real, first_imag, last_imag, mid_imag;

				/*Se hace busqueda binaria para ubicacion en filas*/

				first_imag = 0;
				last_imag = rows - 1;
				mid_imag = (first_imag + last_imag)/2;
				while(first_imag<=last_imag)
				{
					if(origen.pixel_val[mid_imag][0].getPosition().getImag() > imag_part)
					{
						first_imag = mid_imag + 1;
					}
					else if (origen.pixel_val[mid_imag][0].getPosition().getImag() == imag_part)
					{
						f = mid_imag;
						break;
					}
					else
					{
						last_imag = mid_imag - 1;
					}
					mid_imag = (first_imag + last_imag)/2;
				}
				if(first_imag>last_imag)
				{
					if (first_imag > (rows-1)) // Para evitar que acceda a una memoria no permitida
					{
						first_imag = first_imag - 1;
					}
					distance1 = abs(origen.pixel_val[first_imag][0].getPosition().getImag() - imag_part);
					distance2 = abs(origen.pixel_val[last_imag][0].getPosition().getImag() - imag_part);
					if(distance1<=distance2) // Se compara con que fila se esta mas cerca
					{
						f = first_imag;
					}
					else
					{
						f = last_imag;
					}
					
				}

				/*Se hace busqueda binaria para ubicacion en columnas*/

				first_real = 0;
				last_real = columns - 1;
				mid_real = (first_real + last_real)/2;
				while(first_real<=last_real)
				{
					if(origen.pixel_val[0][mid_real].getPosition().getReal() < real_part)
					{
						first_real = mid_real + 1;
					}
					else if (origen.pixel_val[0][mid_real].getPosition().getReal() == real_part)
					{
						h = mid_real;
						break;
					}
					else
					{
						last_real = mid_real - 1;
					}
					mid_real = (first_real + last_real)/2;
				}
				if(first_real>last_real)
				{
					distance1 = abs(origen.pixel_val[0][first_real].getPosition().getReal() - real_part);
					distance2 = abs(origen.pixel_val[0][last_real].getPosition().getReal() - real_part);
					if(distance1<=distance2) // Se compara con que columna se esta mas cerca
					{
						h = first_real;
					}
					else
					{
						h = last_real;
					}
					
				}

				if (f >= 0 && h >= 0) {
            	 	pixel_val[i][j].setColor(origen.pixel_val[f][h].getColor());
            	}

            }
        }
    }

}


void image::ln_z(const image & origen)
{
    complex new_value;

    for(int i = 0; i < rows; i++){ // Se realiza busqueda binaria similar a la de la exponencial
        for(int j = 0; j < columns; j++){
        	new_value.ln(pixel_val[i][j].getPosition());
            if(abs(new_value.getReal()) <= 1.0 && abs(new_value.getImag()) <= 1.0)
            {	
				double real_part = new_value.getReal();
				double imag_part = new_value.getImag();
				double distance1, distance2;

				int f=-1,h=-1;
				int first_real, last_real, mid_real, first_imag, last_imag, mid_imag;

				first_imag = 0;
				last_imag = rows - 1;
				mid_imag = (first_imag + last_imag)/2;
				while(first_imag<=last_imag)
				{
					if(origen.pixel_val[mid_imag][0].getPosition().getImag() > imag_part)
					{
						first_imag = mid_imag + 1;
					}
					else if (origen.pixel_val[mid_imag][0].getPosition().getImag() == imag_part)
					{
						f = mid_imag;
						break;
					}
					else
					{
						last_imag = mid_imag - 1;
					}
					mid_imag = (first_imag + last_imag)/2;
				}
				if(first_imag>last_imag)
				{
					if (first_imag > (rows-1))
					{
						first_imag = first_imag - 1;
					}
					distance1 = abs(origen.pixel_val[first_imag][0].getPosition().getImag() - imag_part);
					distance2 = abs(origen.pixel_val[last_imag][0].getPosition().getImag() - imag_part);
					if(distance1<=distance2)
					{
						f = first_imag;
					}
					else
					{
						f = last_imag;
					}
					
				}

				first_real = 0;
				last_real = columns - 1;
				mid_real = (first_real + last_real)/2;
				while(first_real<=last_real)
				{
					if(origen.pixel_val[0][mid_real].getPosition().getReal() < real_part)
					{
						first_real = mid_real + 1;
					}
					else if (origen.pixel_val[0][mid_real].getPosition().getReal() == real_part)
					{
						h = mid_real;
						break;
					}
					else
					{
						last_real = mid_real - 1;
					}
					mid_real = (first_real + last_real)/2;
				}
				if(first_real>last_real)
				{
					distance1 = abs(origen.pixel_val[0][first_real].getPosition().getReal() - real_part);
					distance2 = abs(origen.pixel_val[0][last_real].getPosition().getReal() - real_part);
					if(distance1<=distance2)
					{
						h = first_real;
					}
					else
					{
						h = last_real;
					}
					
				}

				if (f >= 0 && h >= 0) {
            	 	pixel_val[i][j].setColor(origen.pixel_val[f][h].getColor());
            	}


            }
        }
    }

}


void image::negateimage(const image &origen)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
            pixel_val[i][j].setColor(-(origen.pixel_val[i][j]).getColor() + greys);
    }

}

void calculatorRPN(stack<string> & pila_original ,stack<string> & pila_final, bool & flag_empty)
{
	string aux;
	double arg1, arg2;

	if(flag_empty == 0)
	{
		aux = pila_original.pop();

		pila_final.push(aux);

		if(!pila_original.empty())
		{
			return calculatorRPN(pila_original, pila_final, flag_empty);
		}
		else{
			flag_empty = 1;
		}
		
	}
	if(flag_empty == 1)
	{
		if(pila_final.empty())
		{
			return;
		}
		aux = pila_final.pop();
		cout << aux << endl;

		if(isdigit(aux[0]))
		{
			pila_original.push(aux);
			return calculatorRPN(pila_original, pila_final, flag_empty);

		}
		else if(aux == "+")
		{
			arg2 = stod(pila_original.pop(),NULL);
			arg1 = stod(pila_original.pop(),NULL);
			pila_original.push(to_string(arg1 + arg2));
			return calculatorRPN(pila_original, pila_final, flag_empty);
		}
		else if(aux == "-")
		{
			arg2 = stod(pila_original.pop(),NULL);
			arg1 = stod(pila_original.pop(),NULL);
			pila_original.push(to_string(arg1 - arg2));
			return calculatorRPN(pila_original, pila_final, flag_empty);
		}
		else if(aux == "*")
		{
			arg2 = stod(pila_original.pop(),NULL);
			arg1 = stod(pila_original.pop(),NULL);
			pila_original.push(to_string(arg1 * arg2));
			return calculatorRPN(pila_original, pila_final, flag_empty);
		}
		else if(aux == "/")
		{
			arg2 = stod(pila_original.pop(),NULL);
			arg1 = stod(pila_original.pop(),NULL);
			pila_original.push(to_string(arg1 / arg2));
			return calculatorRPN(pila_original, pila_final, flag_empty);
		}
		else if(aux == "^")
		{
			arg2 = stod(pila_original.pop(),NULL);
			arg1 = stod(pila_original.pop(),NULL);
			pila_original.push(to_string(pow(arg1,arg2)));
			return calculatorRPN(pila_original, pila_final, flag_empty);
		}
		else if (aux == "sin")
		{
			arg1 = stod(pila_original.pop(),NULL);
			pila_original.push(to_string(sin(arg1)));
			return calculatorRPN(pila_original, pila_final, flag_empty);
		}
		else if (aux == "cos")
		{
			arg1 = stod(pila_original.pop(),NULL);
			pila_original.push(to_string(cos(arg1)));
			return calculatorRPN(pila_original, pila_final, flag_empty);
		}
		else if (aux == "tan")
		{
			arg1 = stod(pila_original.pop(),NULL);
			pila_original.push(to_string(tan(arg1)));
			return calculatorRPN(pila_original, pila_final, flag_empty);
		}
		else if (aux == "ln")
		{
			arg1 = stod(pila_original.pop(),NULL);
			pila_original.push(to_string(log(arg1)));
			return calculatorRPN(pila_original, pila_final, flag_empty);
		}
		else if (aux == "exp")
		{
			arg1 = stod(pila_original.pop(),NULL);
			pila_original.push(to_string(exp(arg1)));
			return calculatorRPN(pila_original, pila_final, flag_empty);
		}
	}
	
}

void image::convertFunction(stack<string> & numbers)
{
	stack<string> pila_resultado;
	bool vacio = 0;

	calculatorRPN(numbers,pila_resultado,vacio);
	cout << numbers.pop() << endl;
	// stack<string> numbers_straight;
	// string aux;
	// double arg1, arg2;

	// while (!numbers.empty()){
	// 	aux = numbers.pop();
	// 	cout << aux << endl;
	//  	numbers_straight.push(aux);
	// }

	// while (!numbers_straight.empty()){
	// 	aux = numbers_straight.pop();
	// 	cout << aux <<endl;
	// 	if(isdigit(aux[0]))
	// 	{
	// 		pila_resultado.push(aux);
	// 	}
	// 	else if(aux == "+")
	// 	{
	// 		arg2 = stod(pila_resultado.pop(),NULL);
	// 		arg1 = stod(pila_resultado.pop(),NULL);
	// 		pila_resultado.push(to_string(arg1 + arg2));
	// 	}
	// 	else if(aux == "-")
	// 	{
	// 		arg2 = stod(pila_resultado.pop(),NULL);
	// 		arg1 = stod(pila_resultado.pop(),NULL);
	// 		pila_resultado.push(to_string(arg1 - arg2));
	// 	}
	// 	else if(aux == "*")
	// 	{
	// 		arg2 = stod(pila_resultado.pop(),NULL);
	// 		arg1 = stod(pila_resultado.pop(),NULL);
	// 		pila_resultado.push(to_string(arg1 * arg2));
	// 	}
	// 	else if(aux == "/")
	// 	{
	// 		arg2 = stod(pila_resultado.pop(),NULL);
	// 		arg1 = stod(pila_resultado.pop(),NULL);
	// 		pila_resultado.push(to_string(arg1 / arg2));
	// 	}
	// 	else if(aux == "^")
	// 	{
	// 		arg2 = stod(pila_resultado.pop(),NULL);
	// 		arg1 = stod(pila_resultado.pop(),NULL);
	// 		pila_resultado.push(to_string(pow(arg1,arg2)));
	// 	}
	// 	else if (aux == "sin")
	// 	{
	// 		arg1 = stod(pila_resultado.pop(),NULL);
	// 		pila_resultado.push(to_string(sin(arg1)));
	// 	}
	// 	else if (aux == "cos")
	// 	{
	// 		arg1 = stod(pila_resultado.pop(),NULL);
	// 		pila_resultado.push(to_string(cos(arg1)));
	// 	}
	// 	else if (aux == "tan")
	// 	{
	// 		arg1 = stod(pila_resultado.pop(),NULL);
	// 		pila_resultado.push(to_string(tan(arg1)));
	// 	}
	// 	else if (aux == "ln")
	// 	{
	// 		arg1 = stod(pila_resultado.pop(),NULL);
	// 		pila_resultado.push(to_string(log(arg1)));
	// 	}
	// 	else if (aux == "exp")
	// 	{
	// 		arg1 = stod(pila_resultado.pop(),NULL);
	// 		pila_resultado.push(to_string(exp(arg1)));
	// 	}
	// }
	//cout << pila_resultado.pop() << endl;
}


void image::export_to_file(ostream *os){
	(*os) << "P2" <<endl;
	if(comment != "\0")
	{
		(*os) << comment <<endl;
	}
	(*os) << columns << " " << rows << endl;
	(*os) << greys << endl;

	for(int i = 0; i < rows; i++){
          for(int j = 0; j < columns; j++){
        	  (*os) << pixel_val[i][j].getColor() << " ";
          }
          (*os) << endl;
    }
}

void image::setimage( int &num_rows,  int &num_cols,  int &grey_scale)
{
    rows = num_rows;
    columns = num_cols;
    greys = grey_scale;
}

/**
 * returns the number of rows, columns and gray levels
 */
void image::getimage(int &num_rows,  int &num_cols,  int &grey_scale)
{
    num_rows = rows;
    num_cols = columns;
    grey_scale = greys;

}

void image::setRows(const int &num_rows){
		rows = num_rows;
}

void image::setColumns(const int &num_columns){
	columns = num_columns;
}

void image::setGreys(const int &grey_scale){
	 greys = grey_scale;
}


int& image::getRows(){
	return rows;
}

int& image::getColumns(){
	return columns;
}

int& image::getGreys(){
	return greys;
}

/**
 * returns the gray value of a specific pixel
 */

int image::getPixelColor(const int num_row, const int num_col)
{
	if ((rows < num_row) || (columns < num_col)){
		cerr << "error: very long rows or columns" <<endl;
		exit(1);
	}

    return pixel_val[num_row][num_col].getColor();
}

