#ifndef __Cola__Cola__
#define __Cola__Cola__

#include <stdio.h>
#include <iostream>
#include "listaEnlazada.h"

using namespace std;

template <class T>
class Cola: protected ListaEnlazada<T>
{
    
public:
    Cola(); //Constructor
    ~Cola(); //Destructor
    
    void enqueue(T n); //Inserta un elemento a la cola
    Nodo<T> * dequeue(); //Borra un elemento de la cola y lo regresa
    Nodo<T> * inicio(); //Regresa el inicio de la cola
    
    //Metodos que se reescriben de la clase lista enlazada
    int size() override; //Regresa el tamaño de la cola
    bool empty() override; //Vacía la cola
    
    //Overload
    template <class Tn>
    friend std::ostream & operator <<(std::ostream &, Cola<Tn> &);  //Overload operador <<
    
};

template <class T>
Cola<T>::Cola():ListaEnlazada<T>()
{
    
}


template <class T>
Cola<T>::~Cola()
{
    this->clear();
}

template <class T>
void Cola<T>::enqueue(T n)
{
    this->insertBack(n);
}

template <class T>
Nodo<T> * Cola<T>::dequeue()
{
    return this->deleteFront();
}

template <class T>
Nodo<T> * Cola<T>::inicio()
{
    return this->start();
}

template <class T>
int Cola<T>::size()
{
    return ListaEnlazada<T>::size();
}

template <class T>
bool Cola<T>::empty()
{
    return ListaEnlazada<T>::empty();
}

template <class T>
std::ostream & operator <<(std::ostream & os, Cola<T> & col)
{
    for(auto p: col)
    {
        os << p << " ";
    }
    
    return os;
}

#endif /* defined(__Cola__Cola__) */

