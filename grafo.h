#ifndef grafo_grafo_h
#define grafo_grafo_h

#include <iostream>
#include "nodoA.h"

template <class V, class A>
class Grafo {
    NodoV<V, A> * vertices;
    int numeroVertices;
    
public:
    Grafo();
    ~Grafo();
    
    void clear();
    int size();
    bool empty();
    
    void insertarVertice(V info);
    void insertarVertice(NodoV<V, A> *vertice);
    void inserarArista(A info, NodoV<V, A> *orgien, NodoV<V, A> *destino);
    
    NodoV<V, A> * buscarVertice(V info);
    NodoV<V, A> * inicio();
    
    template <typename Vn, typename An>
    friend std::ostream& operator<<(std::ostream& os, Grafo<Vn, An> &grafo);
};

template <class V, class A>
Grafo<V, A>::Grafo() {
    vertices = nullptr;
    numeroVertices = 0;
}

template <class V, class A>
Grafo<V, A>::~Grafo() {
    clear();
}

template <class V, class A>
void Grafo<V, A>::clear(){
    NodoV<V, A> *tmp = vertices;
    while (tmp) {
        vertices = vertices->getNext();
        delete tmp;
        tmp = vertices;
    }
    
    vertices = nullptr;
    numeroVertices = 0;
}

template <class V, class A>
int Grafo<V, A>::size() {
    return numeroVertices;
}

template <class V, class A>
bool Grafo<V, A>::empty() {
    return (size() == 0);
}

template <class V, class A>
void Grafo<V, A>::insertarVertice(V info) {
    NodoV<V, A> *tmp = vertices;
    NodoV<V, A> *prev = nullptr;
    
    while (tmp) {
        prev = tmp;
        tmp = tmp->getNext();
    }
    
    NodoV<V, A> *nuevo = new NodoV<V, A>(info);
    if (prev)
        prev->setNext(nuevo);
    else
        vertices = nuevo;
    ++numeroVertices;
}

template <class V, class A>
void Grafo<V, A>::insertarVertice(NodoV<V, A> *vertice) {
    NodoV<V, A> *tmp = vertices;
    NodoV<V, A> *prev = nullptr;
    
    while (tmp) {
        prev = tmp;
        tmp = tmp->getNext();
    }
    
    if (prev)
        prev->setNext(vertice);
    else
        vertices = vertice;
    ++numeroVertices;
}

template <class V, class A>
void Grafo<V, A>::inserarArista(A info, NodoV<V, A> *orgien, NodoV<V, A> *destino) {
    orgien->adicionarArista(info, destino);
}

template <class V, class A>
NodoV<V, A> * Grafo<V, A>::buscarVertice(V info) {
    NodoV<V, A> *tmp = vertices;
    while (tmp && *tmp->getInfo() != *info) {
        tmp = tmp->getNext();
    }
    return tmp;
}

template <class V, class A>
NodoV<V, A> * Grafo<V, A>::inicio() {
    return vertices;
}

template <class V, class A>
std::ostream& operator<<(std::ostream& os, Grafo<V, A> &grafo) {
    NodoV<V, A> *tmp = grafo.vertices;
    
    while(tmp) {
        os << *tmp << std::endl;
        tmp = tmp->getNext();
    }
    
    return os;
}

#endif
