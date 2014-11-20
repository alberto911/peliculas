#include "cine.h"
#include "critica.h"
#include <algorithm>
#include <regex>
#include <fstream>
#include <sstream>

using namespace std;

Cine::Cine() {
    peliculas = new map<string, Pelicula*>;
    directores = new map<string, Persona*>;
    actores = new map<string, Persona*>;
    usuarios = new Grafo<Usuario*, int>;
}

Cine::~Cine() {
    for (auto pelicula : *peliculas)
        delete pelicula.second;
    delete peliculas;
    
    for (auto director : *directores)
        delete director.second;
    delete directores;
    
    for (auto actor : *actores)
        delete actor.second;
    delete actores;
}

Pelicula* Cine::agregarPelicula() {
    string titulo, fecha, pais, genero, nombreDirector;
    cout << "\n---- NUEVA PELICULA ----" << endl;
    cout << "Título: ";
    getline(cin, titulo);
    cout << "Director: ";
    getline(cin, nombreDirector);
    
    do {
        cout << "Fecha de estreno (dd/mm/aaaa): ";
        getline(cin,fecha);
    } while (!Pelicula::validarFecha(fecha));
    
    cout << "País: ";
    getline(cin, pais);
    cout << "Género: ";
    getline(cin, genero);
    
    if (!(*peliculas)[titulo]) {
        agregarPelicula(titulo, nombreDirector, fecha, pais, genero);
    }
    else
        cout << "La película ya existe" << endl;
    return (*peliculas)[titulo];
}

Pelicula* Cine::agregarPelicula(string titulo, string nombreDirector, string fecha, string pais, string genero) {
    if (!(*directores)[nombreDirector])
        (*directores)[nombreDirector] = new Persona(nombreDirector);
    Persona *director = (*directores)[nombreDirector];
    
    Pelicula * p = new Pelicula(titulo, director, fecha, pais, genero);
    (*peliculas)[titulo] = p;
    director->agregarPelicula(p);
    return (*peliculas)[titulo];
}

Persona* Cine::agregarPersona(map<string, Persona *> *mapa, string texto) {
    string nombre;
    cout << "\n---- Nuevo " << texto << " ----" << endl;
    cout << texto << ": ";
    getline(cin, nombre);
    
    if (!(*mapa)[nombre])
        (*mapa)[nombre] = new Persona(nombre);
    else {
        texto[0] += ('a' - 'A');
        cout << "El " << texto << " ya existe" << endl;
    }
    return (*mapa)[nombre];
}

void Cine::agregarUsuario() {
    string username, password;
    Usuario* usuario = buscarUsuario(username);
    if (usuario)
        cout << "El usuario ya existe" << endl;
    else {
        cout << "Contraseña: ";
        getline(cin, password);
        usuarios->insertarVertice(new Usuario(username, password));
    }
}

void Cine::agregarActor(Pelicula *pelicula) {
    string nombre;
    cout << "Actor: ";
    getline(cin, nombre);
    
    agregarActor(nombre, pelicula);
}

void Cine::agregarActor(string nombre, Pelicula *pelicula) {
    if (!(*actores)[nombre])
        (*actores)[nombre] = new Persona(nombre);
    Persona* actor = (*actores)[nombre];
    if (!pelicula->getActores()->search(actor)) {
        pelicula->agregarActor(actor);
        actor->agregarPelicula(pelicula);
        actor->calcularPuntuacion();
    }
}

void Cine::eliminarActor(Pelicula *pelicula) {
    Persona *actor = buscar(actores, "Nombre");
    if (!actor)
        cout << "El actor no existe" << endl;
    else {
        Nodo<Persona*> *borrado = pelicula->getActores()->deleteAt(pelicula->getActores()->pos(actor));
        if (borrado) {
            actor->getPeliculas()->deleteAt(actor->getPeliculas()->pos(pelicula));
            actor->calcularPuntuacion();
            cout << "Actor borrado exitosamente de la película" << endl;
        }
        else
            cout << "El actor no está en la película" << endl;
    }
}

Pelicula* Cine::editarPelicula(Pelicula *pelicula) {
    string fecha, pais, genero, nombreDirector;
    cout << "\n---- EDITAR PELICULA ----" << endl;
    cout << "Director: ";
    getline(cin, nombreDirector);
    
    if (!(*directores)[nombreDirector])
        (*directores)[nombreDirector] = new Persona(nombreDirector);
    Persona *director = (*directores)[nombreDirector];
    
    do {
        cout << "Fecha de estreno (dd/mm/aaaa): ";
        getline(cin,fecha);
    } while (!Pelicula::validarFecha(fecha));
    pelicula->setFecha(fecha);
    
    cout << "País: ";
    getline(cin, pais);
    pelicula->setPais(pais);
    cout << "Género: ";
    getline(cin, genero);
    pelicula->setGenero(genero);

    ListaEnlazadaOrdenada<Pelicula*> * peliculasDirector = pelicula->getDirector()->getPeliculas();
    peliculasDirector->deleteAt(peliculasDirector->pos(pelicula));
    pelicula->getDirector()->calcularPuntuacion();
    pelicula->setDirector(director);
    director->agregarPelicula(pelicula);
    director->calcularPuntuacion();
    
    return pelicula;
}

void Cine::editarPersona(std::map<std::string, Persona*> *mapa, std::string texto) {
    string nombre;
    cout << texto << ": ";
    getline(std::cin, nombre);
    if (mapa->find(nombre) != mapa->end()) {
        Persona *persona = mapa->find(nombre)->second;
        string nuevoNombre;
        cout << "Nuevo nombre: ";
        getline(cin, nuevoNombre);
        persona->setNombre(nuevoNombre);
        (*mapa)[nuevoNombre] = persona;
        mapa->erase(nombre);
    }
    else {
        texto[0] += ('a' - 'A');
        cout << "El " << texto << " no existe" << endl;
        return;
    }
}

void Cine::eliminarPelicula(Pelicula * p) {
    Pelicula *pelicula = nullptr;
    if (!p)
        pelicula = buscar(peliculas, "Título");
    else {
        if (peliculas->find(p->getTitulo()) != peliculas->end())
            pelicula = (*peliculas)[p->getTitulo()];
    }
    
    if (pelicula) {
        ListaEnlazadaOrdenada<Pelicula*> * peliculasDirector = pelicula->getDirector()->getPeliculas();
        peliculasDirector->deleteAt(peliculasDirector->pos(pelicula));
        pelicula->getDirector()->calcularPuntuacion();
        Nodo<Persona*> *actor = pelicula->getActores()->start();
        while (actor) {
            ListaEnlazadaOrdenada<Pelicula*> * peliculasActor = actor->getInfo()->getPeliculas();
            peliculasActor->deleteAt(peliculasActor->pos(pelicula));
            actor->getInfo()->calcularPuntuacion();
            actor = actor->getSiguiente();
        }
        peliculas->erase(pelicula->getTitulo());
        delete pelicula;
        cout << "Película borrada exitosamente" << endl;
        return;
    }
    cout << "La película no existe" << endl;
}

void Cine::eliminarDirector() {
    Persona *director = buscar(directores, "Nombre");
    if (!director)
        cout << "El director no existe" << endl;
    else {
        Nodo<Pelicula*> *pelicula = director->getPeliculas()->start();
        while (pelicula) {
            Nodo<Persona*> *actor = pelicula->getInfo()->getActores()->start();
            while (actor) {
                ListaEnlazadaOrdenada<Pelicula*> * peliculasActor = actor->getInfo()->getPeliculas();
                peliculasActor->deleteAt(peliculasActor->pos(pelicula->getInfo()));
                actor = actor->getSiguiente();
            }
            peliculas->erase(pelicula->getInfo()->getTitulo());
            pelicula = pelicula->getSiguiente();
        }
        directores->erase(director->getNombre());
        delete director;
        cout << "Director borrado exitosamente" << endl;
    }
}

void Cine::eliminarActor() {
    Persona* actor = buscar(actores, "Nombre");
    if (!actor)
        cout << "El actor no existe" << endl;
    else {
        Nodo<Pelicula*> *pelicula = actor->getPeliculas()->start();
        while (pelicula) {
            ListaEnlazadaOrdenada<Persona*> * actores = pelicula->getInfo()->getActores();
            actores->deleteAt(actores->pos(actor));
            pelicula = pelicula->getSiguiente();
        }
        actores->erase(actor->getNombre());
        delete actor;
        cout << "Actor borrado exitosamente" << endl;
    }
}

Usuario* Cine::login() {
    string username, password;
    Usuario *usuario = buscarUsuario(username);
    cout << "Contraseña: ";
    getline(cin, password);
    if (usuario) {
        if (usuario->validarPassword(password))
            return usuario;
    }
    cout << "Usuario o contraseña incorrectos" << endl;
    return nullptr;
}

void Cine::agregarCritica(Usuario *usuario, Pelicula *pelicula) {
    cout << "\n---- NUEVA CRÍTICA ----" << endl;
    if (!pelicula) {
        pelicula = buscar(peliculas, "Película");
        if (!pelicula) {
            cout << "La película no existe" << endl;
            return;
        }
    }
    Critica *critica = buscarCritica(usuario, pelicula);
    if (critica) {
        cout << "Ya existe una crítica para esta película" << endl;
        return;
    }
    
    string texto;
    cout << "Crítica: ";
    getline(cin, texto);
    
    int puntuacion = Critica::pedirPuntuacion();
    
    critica = new Critica(usuario, pelicula, texto, puntuacion);
    pelicula->agregarCritica(critica);
    usuario->agregarCritica(critica);
    
    pelicula->getDirector()->calcularPuntuacion();
    for (auto actor : *pelicula->getActores())
        actor.getInfo()->calcularPuntuacion();
}

void Cine::editarCritica(Usuario *usuario, Pelicula *pelicula) {
    cout << "\n---- EDITAR CRÍTICA ----" << endl;
    if (!pelicula) {
        pelicula = buscar(peliculas, "Película");
        if (!pelicula) {
            cout << "La película no existe" << endl;
            return;
        }
    }
    Critica *critica = buscarCritica(usuario, pelicula);
    
    if (critica) {
        string texto;
        cout << "Crítica: ";
        getline(cin, texto);
        critica->setTexto(texto);
        
        int puntuacion = Critica::pedirPuntuacion();
        critica->setPuntuacion(puntuacion);
        pelicula->calcularPuntuacion();
        pelicula->getDirector()->calcularPuntuacion();
        for (auto actor : *pelicula->getActores())
            actor.getInfo()->calcularPuntuacion();
        cout << "Crítica editada exitosamente" << endl;
        return;
    }
    cout << "No existe una crítica para esta película" << endl;
}

void Cine::eliminarCritica(Usuario *usuario, Pelicula *pelicula) {
    cout << "\n---- ELIMINAR CRÍTICA ----" << endl;
    if (!pelicula) {
        pelicula = buscar(peliculas, "Película");
        if (!pelicula) {
            cout << "La película no existe" << endl;
            return;
        }
    }
    Critica *critica = buscarCritica(usuario, pelicula);
    
    if (critica) {
        usuario->getCriticas()->deleteAt(usuario->getCriticas()->pos(critica));
        pelicula->eliminarCritica(critica);
        pelicula->calcularPuntuacion();
        pelicula->getDirector()->calcularPuntuacion();
        for (auto actor : *pelicula->getActores())
            actor.getInfo()->calcularPuntuacion();
        delete critica;
        cout << "Crítica borrada exitosamente" << endl;
        return;
    }
    cout << "No existe una crítica para esta película" << endl;
}

void Cine::agregarSolicitud(Usuario* usuario) {
    string username;
    Usuario *usuario2 = buscarUsuario(username);
    bool solicitudExistente;
    if (usuario2) {
        if (sonAmigos(usuario, usuario2)) {
            cout << "Ya son amigos" << endl;
            return;
        }
        solicitudExistente = usuario2->haySolicitud(usuario);
        if (!solicitudExistente) {
            usuario2->agregarSolicitud(usuario);
            cout << "Solicitud enviada" << endl;
        }
        else
           cout << "Ya has enviado una solicitud de amistad" << endl;
    }
    else
        cout << "El usuario no existe" << endl;
}

void Cine::responderSolicitud(Usuario *usuario) {
    if (usuario->getSolicitudes()->empty()) {
        cout << "No tienes solicitudes de amistad" << endl;
        return;
    }
    
    while (!usuario->getSolicitudes()->empty()) {
        Usuario* usuario2 = usuario->getSolicitudes()->dequeue()->getInfo();
        cout << "\nSolicitud de " << usuario2->getUsername() << endl;
        
        bool respuesta = confirmacion("Aceptar solicitud?");
        if (respuesta) {
            usuarios->inserarArista(0, usuarios->buscarVertice(usuario), usuarios->buscarVertice(usuario2));
            usuarios->inserarArista(0, usuarios->buscarVertice(usuario2), usuarios->buscarVertice(usuario));
            cout << "Amistad confirmada" << endl;
        }
        else
            cout << "Amistad rechazada" << endl;
    }
    
    cout << "\nNo tienes más solicitudes de amistad" << endl;
}

bool Cine::sonAmigos(Usuario *usuario, Usuario *usuario2) {
    NodoA<int, Usuario*> *arista = usuarios->buscarVertice(usuario)->getAristas();
    while (arista) {
        if (arista->getDestino()->getInfo() == usuario2)
            return true;
        arista = arista->getNext();
    }
    return false;
}

Critica* Cine::crearRecomendacion(Usuario* usuario, Pelicula* pelicula) {
    if (!pelicula)
        pelicula = buscar(peliculas, "Película");
    if (!pelicula) {
        cout << "La película no existe" << endl;
        return nullptr;
    }
    string texto;
    cout << "Recomendación: ";
    getline(cin, texto);
    return new Critica(usuario, pelicula, texto);
}

void Cine::recomendarAAmigo(Usuario *usuario, Pelicula *pelicula) {
    cout << "\n---- NUEVA RECOMENDACIÓN ----" << endl;
    string username;
    Usuario *amigo = buscarUsuario(username);
    if (amigo) {
        if (sonAmigos(usuario, amigo)) {
            Critica *recomendacion = crearRecomendacion(usuario, pelicula);
            if (recomendacion) {
                amigo->agregarRecomendacion(recomendacion);
                cout << "Recomendación enviada exitosamente" << endl;
            }
        }
        else
            cout << "El usuario no es tu amigo" << endl;
    }
    else
        cout << "El usuario no existe" << endl;
}

void Cine::recomendarATodos(Usuario *usuario, Pelicula *pelicula) {
    cout << "\n---- NUEVA RECOMENDACIÓN ----" << endl;
    NodoA<int, Usuario*> *arista = usuarios->buscarVertice(usuario)->getAristas();
    if (!arista) {
        cout << "Aún no tienes amigos!" << endl;
        return;
    }
    Critica *recomendacion = crearRecomendacion(usuario, pelicula);
    if (recomendacion) {
        while (arista) {
            arista->getDestino()->getInfo()->agregarRecomendacion(recomendacion);
            arista = arista->getNext();
        }
        cout << "Recomendación enviada exitosamente" << endl;
    }
}

void Cine::verRecomedaciones(Usuario *usuario) {
    Pila<Critica*> aux;
    bool respuesta;
    
    cout << "\n---- RECOMENDACIONES ----" << endl;
    if (usuario->getRecomendaciones()->empty()) {
        cout << "No hay recomendaciones" << endl;
        return;
    }
    
    do {
        int i = 0;
        while (usuario->getRecomendaciones()->top() && i < 2) {
            usuario->getRecomendaciones()->top()->getInfo()->imprimirRecomendacion();
            cout << endl;
            aux.push(usuario->getRecomendaciones()->pop()->getInfo());
            ++i;
        }
        if (usuario->getRecomendaciones()->empty()) {
            cout << "No hay más recomendaciones" << endl;
            break;
        }
        
        respuesta = confirmacion("Imprimir más recomendaciones?");
    } while (respuesta);
    
    while (aux.top())
        usuario->getRecomendaciones()->push(aux.pop()->getInfo());
}

map<string, Pelicula*> * Cine::getPeliculas() {
    return peliculas;
}

map<string, Persona*> * Cine::getDirectores() {
    return directores;
}

map<string, Persona*> * Cine::getActores() {
    return actores;
}

void Cine::filtroPeliculas(function<string(Pelicula*)> compara, string texto, string filtro) {
    if (filtro == "") {
        cout << texto << ": ";
        getline(cin, filtro);
    }
    
    bool encontrado = false;
    cout << "\n---- " << filtro << " ----" << endl;
    for (auto pelicula : *peliculas) {
        if (compara(pelicula.second) == filtro) {
            cout << pelicula.first << " " << *pelicula.second << endl;
            encontrado = true;
        }
    }
    
    if (!encontrado)
        cout << "No se encontró ninguna película" << endl;
}

vector<Pelicula*> Cine::obtenerRanking(function<string (Pelicula *)> compara, string texto, string filtro) {
    if (compara && filtro == "") {
        cout << texto << ": ";
        getline(cin, filtro);
    }
    if (!compara)
        cout << "\n---- TODAS LAS PELÍCULAS ----" << endl;
    else
        cout << "\n---- " << filtro << " ----" << endl;
    
    vector<Pelicula*> ranking;
    for (auto pelicula : *peliculas) {
        if ((compara && compara(pelicula.second) == filtro) || !compara) {
            if (ranking.size() < 10 || pelicula.second->getPuntuacion() > ranking.back()->getPuntuacion()) {
                ranking.push_back(pelicula.second);
                sort(ranking.begin(), ranking.end(), Pelicula::comparaPuntuacion);
                if (ranking.size() > 10)
                    ranking.pop_back();
            }
        }
    }
    
    int i = 1;
    for (auto pelicula : ranking)
        cout << i++ << ". " << pelicula->getTitulo() << " " << pelicula->getPuntuacion() << endl;
    return ranking;
}

vector<Persona*> Cine::rankingPersona(std::map<std::string, Persona*> *mapa, std::string texto) {
    cout << "\n---- Top 10 " << texto << " ----" << endl;
    vector<Persona*> ranking;
    for (auto persona : *mapa) {
        if (ranking.size() < 10 || persona.second->getPuntuacion() > ranking.back()->getPuntuacion()) {
            ranking.push_back(persona.second);
            sort(ranking.begin(), ranking.end(), Persona::comparaPuntuacion);
            if (ranking.size() > 10)
                ranking.pop_back();
        }
    }
    
    int i = 1;
    for (auto persona : ranking)
        cout << i++ << ". " << persona->getNombre() << " " << persona->getPuntuacion() << endl;
    return ranking;
}

Usuario* Cine::buscarUsuario(string &username) {
    cout << "Usuario: ";
    getline(cin, username);
    
    NodoV<Usuario*, int> *tmp = usuarios->inicio();
    while (tmp && tmp->getInfo()->getUsername() != username) {
        tmp = tmp->getNext();
    }
    
    if (tmp)
        return tmp->getInfo();
    else
        return nullptr;
}

Critica* Cine::buscarCritica(Usuario* usuario, Pelicula* pelicula) {
    for (auto critica : *usuario->getCriticas()) {
        if (critica.getInfo()->getPelicula() == pelicula) {
            return critica.getInfo();
        }
    }
    return nullptr;
}

bool Cine::confirmacion(std::string texto) {
    char respuesta;
    cout << texto << " (y/n): ";
    cin >> respuesta;
    while (respuesta != 'y' && respuesta != 'n') {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Respuesta no válida.\n" << texto << " (y/n): ";
        cin >> respuesta;
    }
    cin.ignore();
    
    if (respuesta == 'y')
        return true;
    return false;
}

int Cine::importarArchivo(bool (Cine::*agregar)(vector<string>)) {
    string nombre;
    cout << "Nombre del archivo: ";
    cin >> nombre;
    
    ifstream myfile(nombre);
    
    if (myfile.is_open()) {
        int i = 0;
        string linea, token;
        while (getline(myfile, linea)) {
            vector<string> tokens;
            stringstream stream(linea);
            while (getline(stream, token, ','))
                tokens.push_back(token);
            
            if ((this->*agregar)(tokens))
                ++i;
        }
        myfile.close();
        return i;
    }
    
    else
        cout << "El archivo no se pudo abrir." << endl;
    return 0;
}

bool Cine::vectorAPelicula(vector<string> tokens) {
    if (tokens.size() == 5 && Pelicula::validarFecha(tokens[2]) && !(*peliculas)[tokens[0]]) {
        agregarPelicula(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
        return true;
    }
    return false;
}
