#include <iostream>
#include <regex>
#include "usuario.h"
#include "persona.h"
#include "cine.h"

using namespace std;

void pedirOpcion(int &opcion);
void menuPelicula(Cine &baseDeDatos, Pelicula *pelicula, Usuario *usuario);
void listarPeliculas(Cine &baseDeDatos);
bool menuUsuario(Cine &baseDeDatos, Usuario *usuario);
void menuCriticas(Cine &baseDeDatos, Usuario *usuario, Pelicula *pelicula = nullptr);
void top10(Cine &baseDeDatos);
void menuSolicitudes(Cine &baseDeDatos, Usuario *usuario);
void menuRecomendaciones(Cine &baseDeDatos, Usuario *usuario, Pelicula *pelicula = nullptr);

int main()
{
    Cine baseDeDatos;
    Usuario* usuarioActual = nullptr;
    int opcion;
    
    do {
        cout << "\n---- BASE DE DATOS DE CINE ----" << endl;
        cout << "1. Películas\n2. Directores\n3. Actores\n4. Usuario\n0. Salir" << endl;
        pedirOpcion(opcion);
        
        if (opcion == 1) {
            int opcion2;
            do {
                cout << "\n---- PELÍCULAS -----" << endl;
                if (!usuarioActual) {
                    cout << "1. Listar películas\n2. Top 10\n3. Buscar película\n4. Agregar película\n5. Eliminar película\n6. Importar archivo\n0. Regresar" << endl;
                    pedirOpcion(opcion2);
                    switch (opcion2) {
                        case 1:
                            listarPeliculas(baseDeDatos);
                            break;
                        case 2:
                            top10(baseDeDatos);
                            break;
                        case 3: {
                            Pelicula *pelicula = baseDeDatos.buscar(baseDeDatos.getPeliculas(), "Título");
                            if (pelicula)
                                menuPelicula(baseDeDatos, pelicula, usuarioActual);
                            else
                                cout << "La película no existe" << endl;
                            break;
                        }
                        case 4: {
                            Pelicula *pelicula = baseDeDatos.agregarPelicula();
                            if (pelicula)
                                menuPelicula(baseDeDatos, pelicula, usuarioActual);
                            break;
                        }
                        case 5:
                            baseDeDatos.eliminarPelicula();
                            break;
                        case 6: {
                            cout << "\nImporta un archivo TXT con cada columna separada por coma: título, director, fecha, país y género." << endl;
                            int cant = baseDeDatos.importarArchivo(&Cine::vectorAPelicula);
                            cout << cant << " películas creadas" << endl;
                            break;
                        }
                        case 0:
                            break;
                        default:
                            cout << "Opción no válida" << endl;
                            break;
                    }
                }
                
                else {
                    cout << "1. Listar películas\n2. Top 10\n3. Buscar película\n0. Regresar" << endl;
                    pedirOpcion(opcion2);
                    switch (opcion2) {
                        case 1:
                            listarPeliculas(baseDeDatos);
                            break;
                        case 2:
                            top10(baseDeDatos);
                            break;
                        case 3: {
                            Pelicula *pelicula = baseDeDatos.buscar(baseDeDatos.getPeliculas(), "Título");
                            if (pelicula)
                                menuPelicula(baseDeDatos, pelicula, usuarioActual);
                            else
                                cout << "La película no existe" << endl;
                            break;
                        }
                        case 0:
                            break;
                        default:
                            cout << "Opción no válida" << endl;
                            break;
                    }
                }
            } while (opcion2 != 0);
        }
        
        else if (opcion == 2) {
            int opcion2;
            do {
                cout << "\n---- DIRECTORES -----" << endl;
                if (!usuarioActual) {
                    cout << "1. Listar directores\n2. Top 10\n3. Buscar director\n4. Agregar director\n5. Editar director\n6. Eliminar director\n0. Regresar" << endl;
                    pedirOpcion(opcion2);
                    switch (opcion2) {
                        case 1:
                            cout << "\n---- DIRECTORES -----" << endl;
                            baseDeDatos.imprimirMapa(baseDeDatos.getDirectores());
                            break;
                        case 2:
                            baseDeDatos.rankingPersona(baseDeDatos.getDirectores(), "directores");
                            break;
                        case 3: {
                            Persona *director = baseDeDatos.buscar(baseDeDatos.getDirectores(), "Nombre");
                            if (director) {
                                cout << "\n---- " << director->getNombre() << " ----" << endl;
                                director->imprimirPeliculas();
                            }
                            break;
                        }
                        case 4:
                            baseDeDatos.agregarPersona(baseDeDatos.getDirectores(), "Director");
                            break;
                        case 5:
                            baseDeDatos.editarPersona(baseDeDatos.getDirectores(), "Director");
                            break;
                        case 6:
                            baseDeDatos.eliminarDirector();
                            break;
                        case 0:
                            break;
                        default:
                            cout << "Opción no válida" << endl;
                            break;
                    }
                }
                
                else {
                    cout << "1. Listar directores\n2. Top 10\n3. Buscar director\n0. Regresar" << endl;
                    pedirOpcion(opcion2);
                    switch (opcion2) {
                        case 1:
                            cout << "\n---- DIRECTORES -----" << endl;
                            baseDeDatos.imprimirMapa(baseDeDatos.getDirectores());
                            break;
                        case 2:
                            baseDeDatos.rankingPersona(baseDeDatos.getDirectores(), "directores");
                            break;
                        case 3: {
                            Persona *director = baseDeDatos.buscar(baseDeDatos.getDirectores(), "Nombre");
                            if (director) {
                                cout << "\n---- " << director->getNombre() << " ----" << endl;
                                director->imprimirPeliculas();
                            }
                            break;
                        }
                        case 0:
                            break;
                        default:
                            cout << "Opción no válida" << endl;
                            break;
                    }
                }
            } while (opcion2 != 0);
        }
        
        else if (opcion == 3) {
            int opcion2;
            do {
                cout << "\n---- ACTORES -----" << endl;
                if (!usuarioActual) {
                    cout << "1. Listar actores\n2. Top 10\n3. Buscar actor\n4. Agregar actor\n5. Editar actor\n6. Eliminar actor\n0. Regresar" << endl;
                    pedirOpcion(opcion2);
                    switch (opcion2) {
                        case 1:
                            cout << "\n---- ACTORES -----" << endl;
                            baseDeDatos.imprimirMapa(baseDeDatos.getActores());
                            break;
                        case 2:
                            baseDeDatos.rankingPersona(baseDeDatos.getActores(), "actores");
                            break;
                        case 3: {
                            Persona *actor = baseDeDatos.buscar(baseDeDatos.getActores(), "Nombre");
                            if (actor) {
                                cout << "\n---- " << actor->getNombre() << " ----" << endl;
                                actor->imprimirPeliculas();
                            }
                            break;
                        }
                        case 4:
                            baseDeDatos.agregarPersona(baseDeDatos.getActores(), "Actor");
                            break;
                        case 5:
                            baseDeDatos.editarPersona(baseDeDatos.getActores(), "Actor");
                            break;
                        case 6:
                            baseDeDatos.eliminarActor();
                            break;
                        case 0:
                            break;
                        default:
                            cout << "Opción no válida" << endl;
                            break;
                    }
                }
                
                else {
                    cout << "1. Listar actores\n2. Top 10\n3. Buscar actor\n0. Regresar" << endl;
                    pedirOpcion(opcion2);
                    switch (opcion2) {
                        case 1:
                            cout << "\n---- ACTORES -----" << endl;
                            baseDeDatos.imprimirMapa(baseDeDatos.getActores());
                            break;
                        case 2:
                            baseDeDatos.rankingPersona(baseDeDatos.getActores(), "actores");
                            break;
                        case 3: {
                            Persona *actor = baseDeDatos.buscar(baseDeDatos.getActores(), "Nombre");
                            if (actor) {
                                cout << "\n---- " << actor->getNombre() << " ----" << endl;
                                actor->imprimirPeliculas();
                            }
                            break;
                        }
                        case 0:
                            break;
                        default:
                            cout << "Opción no válida" << endl;
                            break;
                    }
                }
            } while (opcion2 != 0);
        }
        
        else if (opcion == 4) {
            if (!usuarioActual) {
                int opcion2;
                do {
                    cout << "\n---- USUARIO -----" << endl;
                    cout << "1. Iniciar sesión \n2. Agregar usuario\n0. Regresar" << endl;
                    pedirOpcion(opcion2);
                    switch (opcion2) {
                        case 1: {
                            usuarioActual = baseDeDatos.login();
                            break;
                        }
                        case 2:
                            baseDeDatos.agregarUsuario();
                            break;
                        case 0:
                            break;
                        default:
                            cout << "Opción no válida" << endl;
                            break;
                    }
                } while (opcion2 != 0 && !usuarioActual);
            }
            
            if (usuarioActual) {
                bool sesion = menuUsuario(baseDeDatos, usuarioActual);
                if (!sesion)
                    usuarioActual = nullptr;
            }
        }
        
    } while (opcion != 0);
}

void pedirOpcion(int &opcion) {
    cout << "Opción: ";
    while (!(cin >> opcion)) {
        cout << "Tipo de dato incorrecto.\nOpción: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
}

void menuPelicula(Cine &baseDeDatos, Pelicula *pelicula, Usuario* usuario) {
    int opcion3;
    do {
        cout << "\n---- " << pelicula->getTitulo() << " ----" << endl;
        if (!usuario) {
            cout << "1. Mostrar información\n2. Ver críticas\n3. Editar película\n4. Agregar actor\n5. Eliminar actor\n0. Regresar" << endl;
            pedirOpcion(opcion3);
            switch (opcion3) {
                case 1:
                    pelicula->imprimirInfo();
                    break;
                case 2:
                    pelicula->imprimirCriticas();
                    break;
                case 3:
                    pelicula = baseDeDatos.editarPelicula(pelicula);
                    break;
                case 4:
                    baseDeDatos.agregarActor(pelicula);
                    break;
                case 5:
                    baseDeDatos.eliminarActor(pelicula);
                    break;
                case 0:
                    break;
                default:
                    cout << "Opción no válida" << endl;
                    break;
            }
        }
        
        else {
            cout << "1. Mostrar información\n2. Ver críticas\n3. Editar críticas\n4. Recomendar esta película\n0. Regresar" << endl;
            pedirOpcion(opcion3);
            switch (opcion3) {
                case 1:
                    pelicula->imprimirInfo();
                    break;
                case 2:
                    pelicula->imprimirCriticas();
                    break;
                case 3:
                    menuCriticas(baseDeDatos, usuario, pelicula);
                    break;
                case 4:
                    menuRecomendaciones(baseDeDatos, usuario, pelicula);
                    break;
                case 0:
                    break;
                default:
                    cout << "Opción no válida" << endl;
                    break;
            }
        }
    } while (opcion3 != 0);
}

void listarPeliculas(Cine &baseDeDatos) {
    int opcion;
    do {
        cout << "\n---- LISTAR PELÍCULAS -----" << endl;
        cout << "1. Todas\n2. Por año\n3. Por país\n4. Por género\n0. Regresar" << endl;
        pedirOpcion(opcion);
        switch (opcion) {
            case 1:
                cout << "\n---- TODAS LAS PELÍCULAS ----" << endl;
                baseDeDatos.imprimirMapa(baseDeDatos.getPeliculas());
                break;
            case 2: {
                string fecha;
                do {
                    cout << "Año: ";
                    getline(cin, fecha);
                } while (!regex_match(fecha, regex("^\\d{4}$")));
                
                baseDeDatos.filtroPeliculas([](Pelicula* p) {return p->getYear();}, "Fecha", fecha);
                break;
            }
            case 3:
                baseDeDatos.filtroPeliculas([](Pelicula* p) {return p->getPais();}, "País");
                break;
            case 4:
                baseDeDatos.filtroPeliculas([](Pelicula* p) {return p->getGenero();}, "Género");
                break;
            case 0:
                break;
            default:
                cout << "Opción no válida" << endl;
                break;
        }
    } while (opcion != 0);
}

void top10(Cine &baseDeDatos) {
    int opcion;
    do {
        cout << "\n---- TOP 10 -----" << endl;
        cout << "1. Todas\n2. Por año\n3. Por país\n4. Por género\n0. Regresar" << endl;
        pedirOpcion(opcion);
        switch (opcion) {
            case 1:
                baseDeDatos.obtenerRanking();
                break;
            case 2: {
                string fecha;
                do {
                    cout << "Año: ";
                    getline(cin, fecha);
                } while (!regex_match(fecha, regex("^\\d{4}$")));
                
                baseDeDatos.obtenerRanking([](Pelicula* p) { return p->getYear();}, "Fecha", fecha);
                break;
            }
            case 3:
                baseDeDatos.obtenerRanking([](Pelicula* p) {return p->getPais();}, "País");
                break;
            case 4:
                baseDeDatos.obtenerRanking([](Pelicula* p) {return p->getGenero();}, "Género");
                break;
            case 0:
                break;
            default:
                cout << "Opción no válida" << endl;
                break;
        }
    } while (opcion != 0);
}

bool menuUsuario(Cine &baseDeDatos, Usuario *usuario) {
    int opcion3;
    do {
        cout << "\n---- " << usuario->getUsername() << " ----" << endl;
        cout << "1. Críticas\n2. Recomendaciones\n3. Solicitudes de amistad\n4. Cerrar sesión\n0. Regresar" << endl;
        pedirOpcion(opcion3);
        switch (opcion3) {
            case 1:
                menuCriticas(baseDeDatos, usuario);
                break;
            case 2:
                menuRecomendaciones(baseDeDatos, usuario);
                break;
            case 3:
                menuSolicitudes(baseDeDatos, usuario);
                break;
            case 4:
                return false;
                break;
            case 0:
                break;
            default:
                cout << "Opción no válida" << endl;
                break;
        }
    } while (opcion3 != 0);
    return true;
}

void menuCriticas(Cine &baseDeDatos, Usuario *usuario, Pelicula *pelicula) {
    int opcion;
    do {
        cout << "\n---- CRÍTICAS ----" << endl;
        cout << "1. Agregar crítica\n2. Editar crítica\n3. Borrar crítica\n0. Regresar" << endl;
        pedirOpcion(opcion);
        switch (opcion) {
            case 1:
                baseDeDatos.agregarCritica(usuario, pelicula);
                break;
            case 2:
                baseDeDatos.editarCritica(usuario, pelicula);
                break;
            case 3:
                baseDeDatos.eliminarCritica(usuario, pelicula);
                break;
            case 0:
                break;
            default:
                cout << "Opción no válida" << endl;
                break;
        }
    } while (opcion != 0);
}

void menuSolicitudes(Cine &baseDeDatos, Usuario *usuario) {
    int opcion;
    do {
        cout << "\n---- SOLICITUDES DE AMISTAD ----" << endl;
        cout << "1. Enviar solicitud\n2. Ver solicitudes\n0. Regresar" << endl;
        pedirOpcion(opcion);
        switch (opcion) {
            case 1:
                baseDeDatos.agregarSolicitud(usuario);
                break;
            case 2:
                baseDeDatos.responderSolicitud(usuario);
                break;
            case 0:
                break;
            default:
                cout << "Opción no válida" << endl;
                break;
        }
    } while (opcion != 0);
}

void menuRecomendaciones(Cine &baseDeDatos, Usuario *usuario, Pelicula *pelicula) {
    int opcion;
    do {
        cout << "\n---- RECOMENDACIONES DE PELÍCULAS ----" << endl;
        if (!pelicula) {
            cout << "1. Hacer recomendación a un amigo\n2. Hacer recomendación a todos mis amigos\n3. Ver recomendaciones\n0. Regresar" << endl;
            pedirOpcion(opcion);
            switch (opcion) {
                case 1:
                    baseDeDatos.recomendarAAmigo(usuario, pelicula);
                    break;
                case 2:
                    baseDeDatos.recomendarATodos(usuario, pelicula);
                    break;
                case 3:
                    baseDeDatos.verRecomedaciones(usuario);
                    break;
                case 0:
                    break;
                default:
                    cout << "Opción no válida" << endl;
                    break;
            }
        }
        
        else {
            cout << "1. Hacer recomendación a un amigo\n2. Hacer recomendación a todos mis amigos\n0. Regresar" << endl;
            pedirOpcion(opcion);
            switch (opcion) {
                case 1:
                    baseDeDatos.recomendarAAmigo(usuario, pelicula);
                    break;
                case 2:
                    baseDeDatos.recomendarATodos(usuario, pelicula);
                    break;
                case 0:
                    break;
                default:
                    cout << "Opción no válida" << endl;
                    break;
            }
        }
    } while (opcion != 0);
}




