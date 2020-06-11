/*
 * stack.cpp
 *
 *  Created on: 7 jun. 2020
 *      Author: gerof
 */


#include<iostream>
#include<cstdlib>
using namespace std;


Pila::Pila(void){
    cima=NULL;
}

bool Pila::PilaVacia(void){
    if(cima==NULL)
        return true;
    else
        return false;
}

void Pila::Apilar(int x){

    Puntero p_aux;
    p_aux=new(struct nodo);
    p_aux->nro=x;
    p_aux->sgte=cima;
    cima=p_aux;

}

void Pila::Cima(){
    int x;
    if(cima==NULL)
        cout<<"\n\n\tPila Vacia...!";

    else {
        x=cima->nro;
        cout<<"\n\tLa Cima es :"<<x<<endl;
    }
}

int Pila::Desapilar(void){
    int x;
    Puntero p_aux;
    if(cima==NULL)
        cout<<"\n\n\tPila Vacia...!!";
    else{
        p_aux=cima;
        x=p_aux->nro;
        cima=cima->sgte;
        delete(p_aux);
    }
    return x;
}

void Pila::MostrarPila(void){
    Puntero p_aux;
    p_aux=cima;

    while(p_aux!=NULL){
        cout<<"\t "<<p_aux->nro<<endl;
        p_aux=p_aux->sgte;
    }
}

void Pila::DestruirPila(void){
    Puntero p_aux;

    while(cima!=NULL){
            p_aux=cima;
            cima=cima->sgte;
            delete(p_aux);
    }
}
