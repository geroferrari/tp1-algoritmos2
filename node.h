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
  node(const T&, node<T> *);

  T getdata();
  void setdata(const T&);
  node* getnext();
  void setnext(node*);

};

template <class T>
node<T>::node(const T& d,node<T> *p=0){
	data = d;
	next = p;
}

template <class T>
T node<T>::getdata(){
	return data;
}

template <class T>
void node<T>::setdata(const T&d){
	 data = d;
}

template <class T>
node* node<T>::getnext(){
	return next;
}

template <class T>
void node<T>::setnext(node *n){
	 next = n;
}

#endif

