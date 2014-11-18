#ifndef __peliculas__cine__
#define __peliculas__cine__

#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include "grafo.h"
#include "persona.h"
#include "usuario.h"
#include "pelicula.h"

class Cine {
    std::map<std::string, Pelicula*> *peliculas;
    std::map<std::string, Persona*> *actores;
    std::map<std::string, Persona*> *directores;
    Grafo<Usuario*, int> *usuarios;
    
    Usuario* buscarUsuario(std::string &username, std::string &password);
    Critica* buscarCritica(Usuario*, Pelicula*);

public:
    Cine();
    ~Cine();
    
    Pelicula* agregarPelicula();
    Persona* agregarPersona(std::map<std::string, Persona*> *, std::string);
    void agregarUsuario();
    void agregarActor(Pelicula*);
    void eliminarActor(Pelicula*);
    
    Pelicula* editarPelicula(Pelicula*);
    void editarPersona(std::map<std::string, Persona*> *, std::string);
    
    void eliminarPelicula(Pelicula *p = nullptr);
    void eliminarDirector();
    void eliminarActor();
    
    Usuario* login();
    void agregarCritica(Usuario*, Pelicula* = nullptr);
    void editarCritica(Usuario*, Pelicula* = nullptr);
    void eliminarCritica(Usuario*, Pelicula* = nullptr);
    
    std::map<std::string, Pelicula*>* getPeliculas();
    std::map<std::string, Persona*>* getDirectores();
    std::map<std::string, Persona*>* getActores();
    
    template <class T>
    T* buscar(std::map<std::string, T*> *mapa, std::string texto);
    
    template <class T>
    void imprimirMapa(std::map<std::string, T*> *);
    
    std::vector<Pelicula*> obtenerRanking(std::function<std::string(Pelicula*)> = nullptr, std::string = "", std::string = "");
    std::vector<Persona*> rankingPersona(std::map<std::string, Persona*> *, std::string);
    void filtroPeliculas(std::function<std::string(Pelicula*)>, std::string, std::string = "");
};

template <class T>
T* Cine::buscar(std::map<std::string, T *> *mapa, std::string texto) {
    std::string nombre;
    std::cout << texto << ": ";
    getline(std::cin, nombre);
    if (mapa->find(nombre) != mapa->end())
        return mapa->find(nombre)->second;
    else
        return nullptr;
}

template <class T>
void Cine::imprimirMapa(std::map<std::string, T*> *mapa) {
    for (auto elemento : *mapa) {
        std::cout << elemento.first << " " << *elemento.second << std::endl;
    }
}

#endif /* defined(__peliculas__cine__) */
