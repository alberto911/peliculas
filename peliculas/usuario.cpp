#include "usuario.h"
Usuario::Usuario() {
    criticas = new ListaEnlazada<Critica*>;
}

Usuario::Usuario(std::string username, std::string password)
: username(username), password(password) {
    criticas = new ListaEnlazada<Critica*>;
}

Usuario::~Usuario() {
    delete criticas;
}

std::string Usuario::getUsername() {
    return username;
}

ListaEnlazada<Critica*> * Usuario::getCriticas() {
    return criticas;
}

void Usuario::agregarCritica(Critica *critica) {
    criticas->insertBack(critica);
}

bool Usuario::validarPassword(std::string password) {
    return this->password == password;
}

bool Usuario::operator!=(Usuario &u) {
    return username != u.username;
}

std::ostream& operator<<(std::ostream& os, Usuario &usuario) {
    os << usuario.username;
    return os;
}