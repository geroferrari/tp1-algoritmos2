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

  T getdata();
  void setdata(T);
  node* getnext();
  void setnext(node <T>*);

};

template <class T>
node<T>::node(T d, node<T> *p){
	data = d;
	next = p;
}

template <class T>
T node<T>::getdata(){
	return data;
}

template <class T>
void node<T>::setdata(T d){
	 data = d;
}

template <class T>
node<T>* node<T>::getnext(){
	return next;
}

template <class T>
void node<T>::setnext(node <T> *n){
	 next = n;
}

#endif

