#ifndef grafo_nodoA_h
#define grafo_nodoA_h

#include <iostream>
#include "nodoV.h"

template <class A, class V>
class NodoA {
    A info;
    NodoA<A, V> * next;
    NodoV<V, A> * destino;
    
public:
    NodoA();
    NodoA(A info, NodoV<V, A> *destino);
    
    A getInfo();
    void setInfo(A value);
    
    NodoA<A, V> * getNext();
    void setNext(NodoA<A, V> * value);
    
    NodoV<V, A> * getDestino();
    
    template <class An, class Vn>
    friend std::ostream& operator << (std::ostream& os, NodoA<An, Vn> & arista);
};

template <class A, class V>
NodoA<A, V>::NodoA() { }

template <class A, class V>
NodoA<A, V>::NodoA(A info, NodoV<V, A> *destino) {
    this->info = info;
    next = nullptr;
    this->destino = destino;
}

template <class A, class V>
A NodoA<A, V>::getInfo() {
    return info;
}

template <class A, class V>
void NodoA<A, V>::setInfo(A value) {
    info = value;
}

template <class A, class V>
NodoA<A, V> * NodoA<A, V>::getNext() {
    return next;
}

template <class A, class V>
void NodoA<A, V>::setNext(NodoA<A, V> * value) {
    next = value;
}

template <class A, class V>
NodoV<V, A> * NodoA<A, V>::getDestino() {
    return destino;
}

template <class A, class V>
std::ostream& operator << (std::ostream& os, NodoA<A, V> & arista) {
    os << arista.info << " ---> " << arista.destino->getInfo() << std::endl;
    
    return os;
}

#endif
