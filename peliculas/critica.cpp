#include "critica.h"
#include "usuario.h"

Critica::Critica() {
}

Critica::Critica(Usuario* usuario, Pelicula* pelicula, std::string texto, int puntuacion)
: usuario(usuario), pelicula(pelicula), texto(texto), puntuacion(puntuacion) {
}

int Critica::getPuntuacion() {
    return puntuacion;
}

Pelicula* Critica::getPelicula() {
    return pelicula;
}

void Critica::setTexto(std::string texto) {
    this->texto = texto;
}

void Critica::setPuntuacion(int score) {
    puntuacion = score;
}

int Critica::pedirPuntuacion() {
    int puntuacion;
    std::cout << "Calificación (0-10): ";
    while (!(std::cin >> puntuacion) || puntuacion < 0 || puntuacion > 10) {
        std::cout << "Entrada incorrecta.\nCalificación (0-10): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore();
    return puntuacion;
}

std::ostream& operator<<(std::ostream& os, Critica &critica) {
    os << *critica.usuario << ": " << critica.texto << std::endl;
    os << "   - Puntuación: " << critica.puntuacion << std::endl;
    return os;
}