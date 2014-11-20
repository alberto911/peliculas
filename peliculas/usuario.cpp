#include "usuario.h"
#include "critica.h"

Usuario::Usuario() {
    criticas = new ListaEnlazada<Critica*>;
    recomendaciones = new Pila<Critica*>;
    solicitudes = new Cola<Usuario*>;
}

Usuario::Usuario(std::string username, std::string password)
: username(username), password(password) {
    criticas = new ListaEnlazada<Critica*>;
    recomendaciones = new Pila<Critica*>;
    solicitudes = new Cola<Usuario*>;
}

Usuario::~Usuario() {
    delete criticas;
    delete recomendaciones;
    delete solicitudes;
}

std::string Usuario::getUsername() {
    return username;
}

ListaEnlazada<Critica*> * Usuario::getCriticas() {
    return criticas;
}

Cola<Usuario*> * Usuario::getSolicitudes() {
    return solicitudes;
}

Pila<Critica*> * Usuario::getRecomendaciones() {
    return recomendaciones;
}

bool Usuario::haySolicitud(Usuario *usuario) {
    Cola<Usuario*> *aux = new Cola<Usuario*>;
    bool encontrado = false;
    while (solicitudes->inicio()) {
        if (*solicitudes->inicio()->getInfo() == *usuario)
            encontrado = true;
        aux->enqueue(solicitudes->dequeue()->getInfo());
    }
    Cola<Usuario*> *tmp = solicitudes;
    solicitudes = aux;
    delete tmp;
    return encontrado;
}

void Usuario::agregarCritica(Critica *critica) {
    criticas->insertBack(critica);
}

void Usuario::agregarSolicitud(Usuario *usuario) {
    solicitudes->enqueue(usuario);
}

bool Usuario::validarPassword(std::string password) {
    return this->password == password;
}

void Usuario::agregarRecomendacion(Critica* critica) {
    recomendaciones->push(critica);
}

bool Usuario::operator==(Usuario &u) {
    return username == u.username;
}

bool Usuario::operator!=(Usuario &u) {
    return username != u.username;
}

std::ostream& operator<<(std::ostream& os, Usuario &usuario) {
    os << usuario.username;
    return os;
}