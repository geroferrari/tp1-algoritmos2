/*
 * stack.h
 *
 *  Created on: 7 jun. 2020
 *      Author: gerof
 */
#ifndef _STACK_H_INCLUDED_
#define _STACK_H_INCLUDED_

#include <iostream>
using namespace std;
#include "node.h"

template <class T>
class stack {

private:
  node<T>* top;
  unsigned int size;

public:
  stack();
  ~stack();
  void push(T);
  T pop();
  T gettop();
  int getsize();
  bool empty();
};


template <class T>
stack<T>::stack() {
	if(top != NULL){
		top = NULL;
	}
    size = 0;
}



template <class T>
stack<T>::~stack() {
  if (top){
	  node<T> *aux=top;
	  while (aux){
		  top=top->getnext();
	      delete aux;
	      aux=top;
	  }
	  top = NULL;
	  size = 0;
  }

}


template <class T>
bool stack<T>::empty() {
    if (top == NULL)
        return true;
    else
        return false;
}

template <class T>
T stack<T>::gettop() {
    if (top)
        return top->getdata();
    else
        return NULL;

}

template <class T>
void stack<T>::push(T  val) {
	node <T> * temp = new node<T> (val) ;
	if (top == NULL) {
        top = temp;
    }
    else {
        temp->setnext(top);
        top = temp;
    }
	size++;
}


template <class T>
T stack<T>::pop() {
    if (top == NULL) {
        cerr << "Stack is empty" << endl;
        exit(1);
    }
    else {
        node<T>* temp = top;
        top = top->getnext();
        T aux = temp->getdata();
        delete temp;
        size--;
        return aux;
    }
}

template <class T>
int stack<T>::getsize() {
	return size;
}

#endif
