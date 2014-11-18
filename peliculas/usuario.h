#ifndef __peliculas__usuario__
#define __peliculas__usuario__

#include "pelicula.h"
#include <iostream>

class Usuario {
    std::string username;
    std::string password;
    ListaEnlazada<Critica*> *criticas;
    ListaEnlazada<Pelicula*> recomendaciones;
public:
    Usuario();
    Usuario(std::string username, std::string password);
    ~Usuario();
    
    std::string getUsername();
    void agregarCritica(Critica *critica);
    
    ListaEnlazada<Critica*> * getCriticas();
    
    bool validarPassword(std::string);
    bool operator!=(Usuario&);
    
    friend std::ostream& operator<<(std::ostream& os, Usuario &usuario);
};

#endif /* defined(__peliculas__usuario__) */
