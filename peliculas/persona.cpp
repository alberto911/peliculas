#include "persona.h"

Persona::Persona() {
    peliculas = new ListaEnlazadaOrdenada<Pelicula*>;
}

Persona::Persona(std::string nombre) : nombre(nombre) {
    peliculas = new ListaEnlazadaOrdenada<Pelicula*>;
}

Persona::~Persona() {
    delete peliculas;
}

void Persona::agregarPelicula(Pelicula *pelicula) {
    peliculas->insert(pelicula, Pelicula::comparaFecha);
}

void Persona::eliminarPelicula(Pelicula *pelicula) {
    peliculas->deleteAt(peliculas->pos(pelicula));
}

std::string Persona::getNombre() {
    return nombre;
}

float Persona::getPuntuacion() {
    return puntuacion;
}

void Persona::setNombre(std::string nombre) {
    this->nombre = nombre;
}

ListaEnlazadaOrdenada<Pelicula*> * Persona::getPeliculas() {
    return peliculas;
}

void Persona::calcularPuntuacion() {
    if (peliculas->empty())
        puntuacion = 0;
    else {
        float score = 0;
        for (auto pelicula : *peliculas)
            score += pelicula.getInfo()->getPuntuacion();
        score /= peliculas->size();
        puntuacion = score;
    }
}

bool Persona::compara(Persona *p1, Persona *p2) {
    return p1->nombre < p2->nombre;
}

bool Persona::comparaPuntuacion(Persona *p1, Persona *p2) {
    return p1->puntuacion > p2->puntuacion;
}

void Persona::imprimirPeliculas() {
    for (auto pelicula : *peliculas)
        std::cout << "   - " << pelicula.getInfo()->getTitulo() << " " << *pelicula.getInfo() << std::endl;
}

std::ostream& operator<<(std::ostream& os, Persona& persona) {
    os << persona.puntuacion;
    return os;
}