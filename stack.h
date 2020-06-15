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
   int size;


public:
  stack();
  stack(node<T> *,  int);
  stack(const stack<T> &);
  ~stack();
  node<T> * destructor(node<T> *);
  void push(T);
  T pop();
  T get_top();
  node<T> * get_next_top();
  stack<T> & get_next_stack();
  int get_size();
  bool empty();
  T copy(node<T> *, stack <T> &);
  stack<T> & operator=(const stack<T> &);
};


template <class T>
stack<T>::stack() {
	if(top != NULL){
		top = NULL;
	}
    size = 0;
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
stack<T>::stack(const stack<T> &s){
		cout << "llegue" << endl;
		this->push(copy(s.top, *this));
		cout << "sali" << endl;

}



template <class T>
stack<T>::~stack() {
	while(!empty()){
		pop();
/*	cout << "destructor " <<endl;
  if (top){
			cout << top <<endl;

	      delete destructor(top);
	  	cout << "delete " <<endl;
*/
		cout << "borre" <<endl;
	}
}

template <class T>
node<T> * stack<T>::destructor(node<T> *n){
	cout << "gato" << endl;
	if (n->get_next()==NULL){
		return n;
	}
	cout << "KE" << endl;
	delete destructor(n->get_next());
	return n;
}


template <class T>
bool stack<T>::empty() {
    return (top == NULL);
}
/*        return true;
    else
        return false;
}
*/
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
    	   exit(1);
    }
}

template <class T>
int stack<T>::get_size() {
	return size;
}

#endif
