#ifndef listaEnlazada_listaEnlazada_h
#define listaEnlazada_listaEnlazada_h

#include <iostream>
#include "nodo.h"

template <class T>
class ListaEnlazada {
protected:
    Nodo<T> * inicio = nullptr;
    int tamano = 0;
    
    class Iterator {
        ListaEnlazada<T> * data;
        int position;
    public:
        Iterator(ListaEnlazada<T> * data, int position) : data(data), position(position) { }
        
        Nodo<T> operator*() const { return *(data->at(position)); }
        const Iterator& operator++() { ++position; return *this; }
        bool operator!=(const Iterator& it) const { return position != it.position; }
    };
    
public:
    ListaEnlazada();
    ~ListaEnlazada();
    
    Nodo<T> * start();
    virtual int size();
    virtual bool empty();
    
    virtual void insertAt(T value, int pos);
    void insertFront(T value);
    void insertBack(T value);
    
    virtual Nodo<T> * deleteAt(int pos);
    Nodo<T> * deleteFront();
    Nodo<T> * deleteBack();
    virtual void clear();
    
    virtual Nodo<T> * search(T value);
    virtual Nodo<T> * searchPrev(T value);
    Nodo<T> * at(int pos);
    Nodo<T> * atPrev(int pos);
    int pos(T value);
    
    Nodo<T> * operator[](const int i);
    
    template <class Tn>
    friend std::ostream& operator<< (std::ostream&, ListaEnlazada<Tn>&);
    
    Iterator begin() { return { this, 0 }; }
    Iterator end() { return { this, tamano }; }
};

template <class T>
ListaEnlazada<T>::ListaEnlazada() { }

template <class T>
ListaEnlazada<T>::~ListaEnlazada() {
    clear();
}

template <class T>
Nodo<T> * ListaEnlazada<T>::start() {
    return inicio;
}

template <class T>
int ListaEnlazada<T>::size() {
    return tamano;
}

template <class T>
bool ListaEnlazada<T>::empty() {
    return (tamano == 0);
}

template <class T>
void ListaEnlazada<T>::insertAt(T value, int pos) {
    if (pos < 0 || pos > tamano)
        return;
    
    // Insertar al inicio
    if (pos == 0) {
        Nodo<T> * nuevo = new Nodo<T>(value);
        nuevo->setSiguiente(inicio);
        inicio = nuevo;
    }
    else {
        Nodo<T> * prev = atPrev(pos);
        Nodo<T> * nuevo = new Nodo<T>(value);
        nuevo->setSiguiente(prev->getSiguiente());
        prev->setSiguiente(nuevo);
    }
    ++tamano;
}

template <class T>
void ListaEnlazada<T>::insertFront(T value) {
    insertAt(value, 0);
}

template <class T>
void ListaEnlazada<T>::insertBack(T value) {
    insertAt(value, tamano);
}

template <class T>
Nodo<T> * ListaEnlazada<T>::deleteAt(int pos) {
    if (pos < 0 || pos >= tamano)
        return nullptr;
    
    Nodo<T> * borrado = nullptr;
    if (pos == 0) {
        borrado = inicio;
        inicio = inicio->getSiguiente();
    }
    else {
        Nodo<T> * prev = atPrev(pos);
        borrado = prev->getSiguiente();
        prev->setSiguiente(borrado->getSiguiente());
    }
    
    borrado->setSiguiente(nullptr);
    --tamano;
    return borrado;
}

template <class T>
Nodo<T> * ListaEnlazada<T>::deleteFront() {
    return deleteAt(0);
}

template <class T>
Nodo<T> * ListaEnlazada<T>::deleteBack() {
    return deleteAt(tamano-1);
}

template <class T>
void ListaEnlazada<T>::clear() {
    Nodo<T> * aux;
    while (inicio) {
        aux = inicio;
        inicio = inicio->getSiguiente();
        delete aux;
    }
    tamano = 0;
}

template <class T>
Nodo<T> * ListaEnlazada<T>::search(T value) {
    Nodo<T> * aux = inicio;
    while (aux && aux->getInfo() != value) {
        aux = aux->getSiguiente();
    }
    return aux;
}

template <class T>
Nodo<T> * ListaEnlazada<T>::searchPrev(T value) {
    Nodo<T> * aux = inicio;
    Nodo<T> * prev = aux;
    
    while (aux && aux->getInfo() != value) {
        prev = aux;
        aux = aux->getSiguiente();
    }
    return prev;
}

template <class T>
Nodo<T> * ListaEnlazada<T>::at(int pos) {
    int i = 0;
    Nodo<T> * aux = nullptr;
    
    if (pos < 0 || pos >= tamano)
        return aux;
    
    aux = inicio;
    while (i < pos) {
        aux = aux->getSiguiente();
        ++i;
    }
    return aux;
}

template <class T>
Nodo<T> * ListaEnlazada<T>::atPrev(int pos) {
    int i = 0;
    Nodo<T> * aux = nullptr;
    
    if (pos < 0 || pos > tamano)
        return aux;
    
    aux = inicio;
    while (i < pos-1) {
        aux = aux->getSiguiente();
        ++i;
    }
    return aux;
}

template <class T>
int ListaEnlazada<T>::pos(T value) {
    Nodo<T> * aux = inicio;
    int i = 0;
    while (aux && aux->getInfo() != value) {
        aux = aux->getSiguiente();
        ++i;
    }
    return i;
}

template <class T>
Nodo<T> * ListaEnlazada<T>::operator[](const int i) {
    return at(i);
}

template <class T>
std::ostream& operator<< (std::ostream& os, ListaEnlazada<T>& lista) {
    /*Nodo<T> * aux = lista.inicio;
     
     while (aux) {
     os << *aux << std::endl;
     aux = aux->getSiguiente();
     }*/
    
    for (auto l : lista)
        std::cout << l << std::endl;
    
    return os;
}

#endif