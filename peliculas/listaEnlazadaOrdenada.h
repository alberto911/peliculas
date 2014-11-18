#ifndef T3E4_listaEnlazadaOrdenada_h
#define T3E4_listaEnlazadaOrdenada_h

#include "listaEnlazada.h"

template <class T>
class ListaEnlazadaOrdenada : public ListaEnlazada<T> {
public:
    void insert(T value, bool(*)(T, T));
    static bool asc(T, T);
    static bool desc(T, T);
};

template <class T>
void ListaEnlazadaOrdenada<T>::insert(T value, bool compara(T, T)) {
    Nodo<T> * aux = this->inicio;
    Nodo<T> * nuevo = new Nodo<T>(value);
    
    if (this->tamano == 0 || (aux && compara(value, aux->getInfo()))) {
        nuevo->setSiguiente(aux);
        this->inicio = nuevo;
    }
    
    else {
        while (aux->getSiguiente() && compara(aux->getSiguiente()->getInfo(), value))
            aux = aux->getSiguiente();
        
        nuevo->setSiguiente(aux->getSiguiente());
        aux->setSiguiente(nuevo);
    }
    ++this->tamano;
};

template <class T>
bool ListaEnlazadaOrdenada<T>::asc(T a, T b) {
    return (a < b);
}

template <class T>
bool ListaEnlazadaOrdenada<T>::desc(T a, T b) {
    return (a > b);
}

#endif

