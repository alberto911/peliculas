#ifndef pila_pila_h
#define pila_pila_h

#include <iostream>
#include "listaEnlazada.h"

template <class T>
class Pila : protected ListaEnlazada<T> {
public:
    Pila();
    ~Pila();
    
    void push(T value);
    Nodo<T> * pop();
    Nodo<T> * top();
    
    int size() override;
    bool empty() override;
    
    bool operator!=(Pila<T> l);
    
    template <class Tn>
    friend std::ostream& operator<< (std::ostream&, Pila<Tn>&);
};

template <class T>
Pila<T>::Pila() : ListaEnlazada<T>() { }

template <class T>
Pila<T>::~Pila() {
    this->clear();
}

template <class T>
void Pila<T>::push(T value) {
    this->insertFront(value);
}

template <class T>
Nodo<T> * Pila<T>::pop() {
    return this->deleteFront();
}

template <class T>
Nodo<T> * Pila<T>::top() {
    return this->start();
}

template <class T>
int Pila<T>::size() {
    return ListaEnlazada<T>::size();
}

template <class T>
bool Pila<T>::empty() {
    return ListaEnlazada<T>::empty();
}

template <class T>
bool Pila<T>::operator!=(Pila<T> l) {
    return (this->inicio != l.inicio);
}

template <class T>
std::ostream& operator<< (std::ostream& os, Pila<T>& pila) {
    /*Nodo<T> * aux = pila.inicio;
     
     while (aux) {
     os << *aux << std::endl;
     aux = aux->getSiguiente();
     }*/
    
    for (auto p : pila)
        std::cout << p << std::endl;
    
    return os;
}

#endif

