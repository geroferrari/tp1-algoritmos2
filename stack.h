#ifndef _STACK_H_INCLUDED_
#define _STACK_H_INCLUDED_

#include <iostream>
#include "node.h"

using namespace std;

template <class T>
class stack {

private:
  node<T>* top;
   int size;

public:
   /******* CONSTRUCTORES *****/
  stack();
  stack(node<T> *,  int);
  stack(stack<T> &);

  /***** DESTRUCTOR *********/
  ~stack();

  /****** METODOS *********/
  void push(T); //guardo valores
  T pop(); //obtengo valores
  T get_top(); //obtengo el valor del tope
  node<T> * get_next_top(); //accedo al siguiente valor
  stack<T> & get_next_stack();
  int get_size(); //obtengo el tamaño
  bool empty(); //para saber si esta vacia
  T copy(node<T> *, stack <T> &); //se usa para copiar la pila en otra
};


template <class T>
stack<T>::stack() {
	if(top != NULL){
		top = NULL;
	}
    size = 0;
}

template <class T>
void stack<T>::push(T  val) {
	node <T> * temp = new node<T> (val) ;
	if (top == NULL) {
        top = temp;
    }
    else {
        temp->set_next(top);
        top = temp;
    }
	size++;
}

template <class T>
T stack<T>::copy(node<T> *n, stack <T> &s){
	if (n->get_next()==NULL){
		return n->get_data();
	}
	s.push(copy(n->get_next(), s));
	return n->get_data();
}

template <class T>
stack<T>::stack(stack<T> &s){
	top=NULL;
	size=0;

	this->push(copy(s.top, *this));
}


template <class T>
stack<T>::~stack() {
	while(!empty()){
		pop();
	}
}


template <class T>
bool stack<T>::empty() {
    return (top == NULL);
}


template <class T>
T stack<T>::get_top() {
    if (top)
        return top->get_data();
    else{
    	cerr << "Stack is empty TOP" << endl;
		exit(1);
    }
}

template <class T>
node<T> * stack<T>::get_next_top() {
    if (top)
        return top->get_next();
    else{
    	cerr << "Stack is empty TOP" << endl;
		exit(1);
    }
}

template <class T>
stack<T>::stack(node<T> *t,  int s){
	top = t;
	size = s;
}



template <class T>
T stack<T>::pop() {
    if (!empty()) {
        T aux = top->get_data();
        node<T>* temp = top;
        top = temp->get_next();
        delete temp;
        size--;
        return aux;
    }
    else {
    	cout << "hola" <<endl;
    	   exit(1);
    }
}

template <class T>
int stack<T>::get_size() {
	return size;
}

#endif
