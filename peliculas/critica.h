#ifndef __peliculas__critica__
#define __peliculas__critica__

#include "pelicula.h"
#include <string>
#include <iostream>

class Usuario;

class Critica {
    Usuario* usuario;
    Pelicula* pelicula;
    std::string texto;
    int puntuacion = 0;
public:
    Critica();
    Critica(Usuario* usuario, Pelicula* pelicula, std::string texto);
    Critica(Usuario* usuario, Pelicula* pelicula, std::string texto, int puntuacion);
    
    Pelicula* getPelicula();
    void setTexto(std::string);
    void setPuntuacion(int);
    static int pedirPuntuacion();
    
    int getPuntuacion();
    
    void imprimirRecomendacion();
    friend std::ostream& operator<<(std::ostream& os, Critica &critica);
};

#endif /* defined(__peliculas__critica__) */
