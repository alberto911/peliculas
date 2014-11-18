#ifndef __peliculas__persona__
#define __peliculas__persona__

#include <iostream>
#include "pelicula.h"

class Persona {
protected:
    std::string nombre;
    ListaEnlazadaOrdenada<Pelicula*> * peliculas;
    float puntuacion = 0;
public:
    Persona();
    Persona(std::string);
    ~Persona();
    
    void agregarPelicula(Pelicula*);
    void eliminarPelicula(Pelicula*);
    
    std::string getNombre();
    float getPuntuacion();
    void setNombre(std::string);
    ListaEnlazadaOrdenada<Pelicula*> * getPeliculas();
    
    void calcularPuntuacion();
    
    static bool compara(Persona *p1, Persona *p2);
    static bool comparaPuntuacion(Persona *p1, Persona *p2);
    
    void imprimirPeliculas();
    friend std::ostream& operator<<(std::ostream& os, Persona& Persona);
};

#endif /* defined(__peliculas__persona__) */
