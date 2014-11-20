#ifndef __peliculas__usuario__
#define __peliculas__usuario__

#include "pelicula.h"
#include "cola.h"
#include "pila.h"
#include <iostream>

class Usuario {
    std::string username;
    std::string password;
    ListaEnlazada<Critica*> *criticas;
    Cola<Usuario*> *solicitudes;
    Pila<Critica*> *recomendaciones;

public:
    Usuario();
    Usuario(std::string username, std::string password);
    ~Usuario();
    
    std::string getUsername();
    void agregarCritica(Critica *critica);
    void agregarSolicitud(Usuario*);
    
    ListaEnlazada<Critica*> * getCriticas();
    Cola<Usuario*> * getSolicitudes();
    Pila<Critica*> * getRecomendaciones();
    bool haySolicitud(Usuario*);
    
    void agregarRecomendacion(Critica*);
    
    bool validarPassword(std::string);
    bool operator==(Usuario&);
    bool operator!=(Usuario&);
    
    friend std::ostream& operator<<(std::ostream& os, Usuario &usuario);
};

#endif /* defined(__peliculas__usuario__) */
