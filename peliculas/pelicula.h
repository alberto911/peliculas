#ifndef __peliculas__pelicula__
#define __peliculas__pelicula__

#include "listaEnlazadaOrdenada.h"
#include <iostream>

class Persona;
class Critica;

class Pelicula {
    std::string titulo;
    Persona* director;
    ListaEnlazadaOrdenada<Persona*> *actores;
    std::string fecha;
    std::string pais;
    std::string genero;
    ListaEnlazada<Critica*> *criticas;
    float puntuacion = 0;
    
public:
    Pelicula();
    Pelicula(std::string titulo, Persona* director, std::string fecha, std::string pais, std::string genero);
    ~Pelicula();
    
    void agregarActor(Persona *actor);
    static bool comparaFecha(Pelicula *p1, Pelicula *p2);
    static bool comparaPuntuacion(Pelicula *p1, Pelicula *p2);
    
    void agregarCritica(Critica *critica);
    void eliminarCritica(Critica *critica);
    void calcularPuntuacion();
    
    static bool validarFecha(std::string);
    std::string getYear();
    
    std::string getTitulo();
    std::string getPais();
    std::string getGenero();
    float getPuntuacion();
    Persona* getDirector();
    ListaEnlazadaOrdenada<Persona*> * getActores();
    
    void setPais(std::string);
    void setGenero(std::string);
    void setFecha(std::string);
    void setDirector(Persona*);
    void setActores(ListaEnlazadaOrdenada<Persona*> *actores);
    
    void imprimirInfo();
    void imprimirCriticas();
    friend std::ostream& operator<<(std::ostream& os, Pelicula& pelicula);
};

#endif /* defined(__peliculas__pelicula__) */
