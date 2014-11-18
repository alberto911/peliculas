#include "pelicula.h"
#include "persona.h"
#include "critica.h"
#include <regex>

using namespace std;

Pelicula::Pelicula() {
    actores = new ListaEnlazadaOrdenada<Persona*>;
    criticas = new ListaEnlazada<Critica*>;
}

Pelicula::Pelicula(string titulo, Persona* director, string fecha, string pais, string genero)
    : titulo(titulo), director(director), fecha(fecha), pais(pais), genero(genero) {
        actores = new ListaEnlazadaOrdenada<Persona*>;
        criticas = new ListaEnlazada<Critica*>;
}

Pelicula::~Pelicula() {
    delete actores;
    delete criticas;
}

bool Pelicula::comparaFecha(Pelicula *p1, Pelicula *p2) {
    return p1->fecha < p2->fecha;
}

bool Pelicula::comparaPuntuacion(Pelicula *p1, Pelicula *p2) {
    return p1->puntuacion > p2->puntuacion;
}

void Pelicula::agregarActor(Persona *actor) {
    actores->insert(actor, Persona::compara);
}

void Pelicula::agregarCritica(Critica *critica) {
    float score = puntuacion * criticas->size();
    criticas->insertBack(critica);
    score += critica->getPuntuacion();
    score /= criticas->size();
    puntuacion = score;
}

void Pelicula::eliminarCritica(Critica *critica) {
    criticas->deleteAt(criticas->pos(critica));
}

void Pelicula::calcularPuntuacion() {
    if (criticas->empty())
        puntuacion = 0;
    else {
        float score = 0;
        for (auto critica : *criticas)
            score += critica.getInfo()->getPuntuacion();
        score /= criticas->size();
        puntuacion = score;
    }
}

string Pelicula::getTitulo() {
    return titulo;
}

string Pelicula::getPais() {
    return pais;
}

string Pelicula::getGenero() {
    return genero;
}

float Pelicula::getPuntuacion() {
    return puntuacion;
}

Persona* Pelicula::getDirector() {
    return director;
}

ListaEnlazadaOrdenada<Persona*> * Pelicula::getActores() {
    return actores;
}

void Pelicula::setPais(std::string pais) {
    this->pais = pais;
}

void Pelicula::setGenero(std::string genero) {
    this->genero = genero;
}

void Pelicula::setFecha(std::string fecha) {
    this->fecha = fecha;
}

void Pelicula::setDirector(Persona * director) {
    this->director = director;
}

void Pelicula::setActores(ListaEnlazadaOrdenada<Persona*> *actores) {
    this->actores = actores;
}

bool Pelicula::validarFecha(string fecha) {
    regex validacion ("^\\d{2}[\\/]\\d{2}[\\/]\\d{4}$");
    if (regex_match(fecha, validacion))
        return true;
    return false;
}

string Pelicula::getYear() {
    return fecha.substr(6,4);
}

void Pelicula::imprimirInfo() {
    cout << "\n---- " << titulo << " ----" << endl;
    cout << "Director: " << director->getNombre() << endl;
    cout << "Actores:" << endl;
    for (auto actor : *actores)
        cout << "   - " << actor.getInfo()->getNombre() << endl;
    cout << "Fecha de estreno: " << fecha << endl;
    cout << "País: " << pais << endl;
    cout << "Género: " << genero << endl;
    cout << "Puntuación: " << puntuacion << endl;
}

void Pelicula::imprimirCriticas() {
    cout << "\n---- CRÍTICAS (" << criticas->size() << ") ----" << endl;
    for (auto critica : *criticas)
        cout << "* " << *critica.getInfo();
    cout << "Puntuación total: " << puntuacion << endl;
}

ostream& operator<<(ostream& os, Pelicula& pelicula) {
    os << "(" << pelicula.getYear() << ")";
    return os;
}