/*
 * node.cpp
 *
 *  Created on: 7 jun. 2020
 *      Author: gerof
 */

#ifndef _NODE_H_INCLUDED_
#define _NODE_H_INCLUDED_

#include <iostream>
using namespace std;


template <class T>

class node {
private:
  T data;
  node<T>* next;

public:
  node(T , node<T> *p =NULL);
  ~node();

  T get_data();
  void set_data(T);
  node* get_next();
  void set_next(node <T>*);

};

template <class T>
node<T>::node(T d, node<T> *p){
	data = d;
	next = p;
}

template <class T>
node<T>::~node(){
	next = NULL;
}

template <class T>
T node<T>::get_data(){
	return data;
}

template <class T>
void node<T>::set_data(T d){
	 data = d;
}

template <class T>
node<T>* node<T>::get_next(){
	return next;
}

template <class T>
void node<T>::set_next(node <T> *n){
	 if(n==NULL)
		 next = NULL;
	 else
		 next = n;
}

#endif

