#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

// Estructura para almacenar información de una canción
struct Cancion {
    int id;
    string artist_name;
    string track_name;
    string track_id;
    int popularity;
    int year;
    string genre;
    float danceability;
    float energy;
    int key;
    float loudness;
    int mode;
    float speechiness;
    float acousticness;
    float instrumentalness;
    float liveness;
    float valence;
    float tempo;
    int duration_ms;
    int time_signature;

    void mostrar() const {
        cout << left << setw(5) << id
             << setw(20) << artist_name
             << setw(25) << track_name
             << setw(15) << popularity
             << setw(10) << year
             << setw(15) << genre
             << setw(10) << duration_ms << "ms"
             << endl;
    }
};

// Nodo de la lista doblemente enlazada
struct Nodo {
    Cancion cancion;
    Nodo* siguiente;
    Nodo* anterior;
};

// Punteros globales para manejar la lista
Nodo* cabeza = nullptr;
Nodo* cola = nullptr;

// Función para liberar memoria de toda la lista
void liberarMemoria() {
    Nodo* actual = cabeza;
    while (actual) {
        Nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = cola = nullptr;
}

// Función para agregar una canción al final de la lista
void agregarCancion(const Cancion& cancion) {
    Nodo* nuevo = new Nodo{cancion, nullptr, cola};
    if (!cabeza) {
        cabeza = cola = nuevo;
    } else {
        cola->siguiente = nuevo;
        cola = nuevo;
    }
}

// Función para eliminar una canción por ID
void eliminarPorID(int id) {
    Nodo* actual = cabeza;
    while (actual) {
        if (actual->cancion.id == id) {
            if (actual->anterior) actual->anterior->siguiente = actual->siguiente;
            else cabeza = actual->siguiente;

            if (actual->siguiente) actual->siguiente->anterior = actual->anterior;
            else cola = actual->anterior;

            delete actual;
            cout << "Canción con ID " << id << " eliminada.\n";
            return;
        }
        actual = actual->siguiente;
    }
    cout << "No se encontró una canción con ID " << id << ".\n";
}

// Función para eliminar canciones por nombre de artista o canción
void eliminarPorNombre(const string& nombre) {
    Nodo* actual = cabeza;
    bool encontrado = false;
    while (actual) {
        if (actual->cancion.artist_name == nombre || actual->cancion.track_name == nombre) {
            Nodo* aEliminar = actual;
            if (actual->anterior) actual->anterior->siguiente = actual->siguiente;
            else cabeza = actual->siguiente;

            if (actual->siguiente) actual->siguiente->anterior = actual->anterior;
            else cola = actual->anterior;

            actual = actual->siguiente;
            delete aEliminar;
            encontrado = true;
        } else {
            actual = actual->siguiente;
        }
    }
    if (encontrado) {
        cout << "Canciones con el nombre \"" << nombre << "\" eliminadas.\n";
    } else {
        cout << "No se encontraron canciones con el nombre \"" << nombre << "\".\n";
    }
}

// Función para mostrar toda la lista de canciones
void mostrarLista() {
    if (!cabeza) {
        cout << "La lista de canciones está vacía.\n";
        return;
    }
    Nodo* actual = cabeza;
    cout << left << setw(5) << "ID" << setw(20) << "Artista" << setw(25) << "Nombre de la canción"
         << setw(15) << "Popularidad" << setw(10) << "Año" << setw(15) << "Género" << setw(10) << "Duración" << endl;
    cout << string(100, '-') << endl;
    while (actual) {
        actual->cancion.mostrar();
        actual = actual->siguiente;
    }
}

// Función para ordenar la lista por un criterio específico
void ordenarPorCriterio(const string& criterio) {
    vector<Cancion> canciones;
    Nodo* actual = cabeza;

    while (actual) {
        canciones.push_back(actual->cancion);
        actual = actual->siguiente;
    }

    sort(canciones.begin(), canciones.end(), [&criterio](const Cancion& a, const Cancion& b) {
        if (criterio == "popularity") return a.popularity > b.popularity;
        if (criterio == "year") return a.year < b.year;
        if (criterio == "artist_name") return a.artist_name < b.artist_name;
        return false;
    });

    liberarMemoria();
    for (const auto& cancion : canciones) {
        agregarCancion(cancion);
    }
    cout << "Lista ordenada por " << criterio << ".\n";
}

// Función para buscar canciones por nombre de la canción
void buscarPorNombre(const string& nombre, bool &hay) {
    Nodo* actual = cabeza;
    bool encontrado = false;
    cout << "Resultados de búsqueda para el nombre de canción \"" << nombre << "\":\n";
    cout << left << setw(5) << "ID" << setw(20) << "Artista" << setw(25) << "Nombre de la canción"
         << setw(15) << "Popularidad" << setw(10) << "Año" << setw(15) << "Género" << setw(10) << "Duración" << endl;
    cout << string(100, '-') << endl;

    while (actual) {
        if (actual->cancion.track_name == nombre) {
            actual->cancion.mostrar();
            encontrado = true;
        }
        actual = actual->siguiente;
    }
    hay=encontrado;
    if (!encontrado) {
        cout << "No se encontraron canciones con el nombre \"" << nombre << "\".\n";
    }
}

// Función para buscar canciones por nombre del artista
void buscarPorArtista(const string& artista, bool& hay) {
    Nodo* actual = cabeza;
    bool encontrado = false;
    cout << "Resultados de búsqueda para el artista \"" << artista << "\":\n";
    cout << left << setw(5) << "ID" << setw(20) << "Artista" << setw(25) << "Nombre de la canción"
         << setw(15) << "Popularidad" << setw(10) << "Año" << setw(15) << "Género" << setw(10) << "Duración" << endl;
    cout << string(100, '-') << endl;

    while (actual) {
        if (actual->cancion.artist_name == artista) {
            actual->cancion.mostrar();
            encontrado = true;
        }
        actual = actual->siguiente;
    }
    hay=encontrado;
    if (!encontrado) {
        cout << "No se encontraron canciones del artista \"" << artista << "\".\n";
    }
}

// Función para mostrar el menú principal
void mostrarMenu() {
    cout << "\nMenú de opciones:\n";
    cout << "1. Agregar una nueva canción\n";
    cout << "2. Mostrar lista de canciones\n";
    cout << "3. Ordenar canciones por criterio\n";
    cout << "4. Buscar canción por nombre\n";
    cout << "5. Buscar canciones por artista\n";
    cout << "0. Salir\n";
    cout << "Ingrese su opción: ";
}

int main() {
    int opcion;

    // Canciones iniciales para probar
    agregarCancion({0, "Jason Mraz", "I Won't Give Up", "53QF56cjZA9RTuuMZDrSA6", 68, 2012, "acoustic", 0.483, 0.303, 4, -10.058, 1, 0.0429, 0.694, 0.0, 0.115, 0.139, 133.406, 240166, 3});
    agregarCancion({1, "Jason Mraz", "93 Million Miles", "1s8tP3jP4GZcyHDsjvw218", 50, 2012, "acoustic", 0.572, 0.454, 3, -10.286, 1, 0.0258, 0.477, 1.37e-05, 0.0974, 0.515, 140.182, 216387, 4});
    agregarCancion({2, "Joshua Hyslop", "Do Not Let Me Go", "7BRCa8MPiyuvr2VU3O9W0F", 57, 2012, "acoustic", 0.409, 0.234, 3, -13.711, 1, 0.0323, 0.338, 5e-05, 0.0895, 0.145, 139.832, 158960, 4});
    agregarCancion({3, "Boyce Avenue", "Fast Car", "63wsZUhUZLlh1OsyrZq7sz", 58, 2012, "acoustic", 0.392, 0.251, 10, -9.845, 1, 0.0363, 0.807, 0.0, 0.0797, 0.508, 204.961, 304293, 4});
    agregarCancion({4, "Andrew Belle", "Sky's Still Blue", "6nXIYClvJAfi6ujLiKqEq8", 54, 2012, "acoustic", 0.43, 0.791, 6, -5.419, 0, 0.0302, 0.0726, 0.0193, 0.11, 0.217, 171.864, 244320, 4});
    agregarCancion({5, "Chris Smither", "What They Say", "24NvptbNKGs6sPy1Vh1O0v", 48, 2012, "acoustic", 0.566, 0.57, 2, -6.42, 1, 0.0329, 0.688, 1.73e-06, 0.0943, 0.96, 83.403, 166240, 4});
    agregarCancion({6, "Matt Wertz", "Walking in a Winter Wonderland", "0BP7hSvLAG3URGrEvNNbGM", 48, 2012, "acoustic", 0.575, 0.606, 9, -8.197, 1, 0.03, 0.0119, 0.0, 0.0675, 0.364, 121.083, 152307, 4});
    agregarCancion({7, "Green River Ordinance", "Dancing Shoes", "3Y6BuzQCg9p4yH347Nn8OW", 45, 2012, "acoustic", 0.586, 0.423, 7, -7.459, 1, 0.0261, 0.252, 5.83e-06, 0.0976, 0.318, 138.133, 232373, 4});
    agregarCancion({8, "Jason Mraz", "Living in the Moment", "3ce7k1L4EkZppZPz1EJWTS", 44, 2012, "acoustic", 0.65, 0.628, 7, -7.16, 1, 0.0232, 0.0483, 0.0, 0.119, 0.7, 84.141, 235080, 4});
    agregarCancion({9, "Boyce Avenue", "Heaven", "2EKxmYmUdAVXlaHCnnW13o", 58, 2012, "acoustic", 0.619, 0.28, 8, -10.238, 0, 0.0317, 0.73, 0.0, 0.103, 0.292, 129.948, 250063, 4});
    agregarCancion({10, "Tristan Prettyman", "Say Anything", "1RjEDlhTp2iJXWPdLpa8OM", 45, 2012, "acoustic", 0.657, 0.43, 1, -10.202, 1, 0.0314, 0.534, 0.000238, 0.12, 0.335, 91.967, 236379, 4});
    agregarCancion({11, "David Gray", "Money (That's What I Want) - From Jim Beam's Live Music Series", "38sSJ12azM6Mic7ajbHKBi", 45, 2012, "acoustic", 0.655, 0.692, 5, -6.217, 1, 0.0326, 0.568, 2.34e-05, 0.119, 0.547, 121.455, 234270, 4});
    agregarCancion({12, "Boyce Avenue", "Someone Like You", "6VtoP2sJt5oCmPOQIve2sf", 55, 2012, "acoustic", 0.439, 0.207, 1, -9.573, 1, 0.0297, 0.608, 0.0, 0.186, 0.264, 136.514, 276147, 4});
    agregarCancion({13, "Jason Mraz", "The Woman I Love", "0AYG9AcwqEeqgAw3OvshPC", 40, 2012, "acoustic", 0.591, 0.647, 4, -8.34, 1, 0.0277, 0.067, 6.57e-05, 0.231, 0.678, 79.68, 190752, 4});
    agregarCancion({14, "Eddie Vedder", "I Shall Be Released", "0J1iFISejodqBIy0Q9AS0N", 44, 2012, "acoustic", 0.45, 0.713, 6, -7.503, 0, 0.0386, 0.157, 0.0, 0.992, 0.36, 74.71, 283587, 4});
    agregarCancion({15, "The Civil Wars", "Kingdom Come", "1IZc5f9ulw7Ge2eOpQH7w6", 41, 2012, "acoustic", 0.497, 0.277, 4, -11.382, 0, 0.0373, 0.846, 4.77e-06, 0.111, 0.179, 81.367, 222560, 4});
    agregarCancion({16, "Gabrielle Aplin", "Home", "20kpTTSvI4ok6Gm1uZqtcz", 57, 2012, "acoustic", 0.439, 0.265, 2, -10.72, 1, 0.0343, 0.736, 0.0, 0.093, 0.382, 140.494, 247002, 4});
    agregarCancion({17, "Harley Poe", "Transvestities Can Be Cannibals Too", "46KacVTVWMkyXS0jf7TwOX", 39, 2012, "acoustic", 0.499, 0.614, 7, -8.175, 1, 0.0621, 0.151, 3.52e-06, 0.0555, 0.605, 89.038, 276973, 4});
    agregarCancion({18, "Ron Pope", "One Grain of Sand", "3yqJGfvXtPZLiWHVeLWtm8", 49, 2012, "acoustic", 0.713, 0.824, 3, -7.168, 1, 0.0393, 0.106, 8.03e-05, 0.13, 0.696, 120.028, 207240, 4});
    agregarCancion({19, "Sara Bareilles", "Once Upon Another Time", "7KG9zriC6iP8F1CNihtR8Y", 39, 2012, "acoustic", 0.275, 0.216, 2, -14.504, 1, 0.0493, 0.896, 0.0, 0.231, 0.0551, 95.421, 324333, 5});
    agregarCancion({20, "Harley Poe", "The Hearse Song", "09ibWmdrePCN2E2Gbm4Aen", 39, 2012, "acoustic", 0.512, 0.375, 11, -9.525, 0, 0.0652, 0.527, 0.0, 0.109, 0.445, 183.452, 166467, 3});


    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1: {
                Cancion nuevaCancion;
                cout << "Ingrese los datos de la canción:\n";
                cout << "ID: "; cin >> nuevaCancion.id;
                cin.ignore();
                cout << "Nombre del artista: "; getline(cin, nuevaCancion.artist_name);
                cout << "Nombre de la canción: "; getline(cin, nuevaCancion.track_name);
                cout << "Track ID: "; cin >> nuevaCancion.track_id;
                cout << "Popularidad: "; cin >> nuevaCancion.popularity;
                cout << "Año: "; cin >> nuevaCancion.year;
                cout << "Género: "; cin >> nuevaCancion.genre;
                cout << "Duración (ms): "; cin >> nuevaCancion.duration_ms;
                agregarCancion(nuevaCancion);
                cout << "Canción agregada exitosamente.\n";
                break;
            }
            case 2:
                mostrarLista();
                break;
            case 3: {
                string criterio;
                cout << "Ingrese el criterio para ordenar (popularity, year, artist_name): ";
                cin >> criterio;
                ordenarPorCriterio(criterio);
                break;
            }
            case 4: {
                string nombre;
                bool hay;
                cout << "Ingrese el nombre de la canción a buscar: ";
                cin.ignore();
                getline(cin, nombre);
                buscarPorNombre(nombre, hay);

                if(hay){
                    string id;
                    cout<<endl;
                    cout<<"Para eliminar coloca ( ID ) - Para cancelar ( N o n ): ";
                    cin >> id;

                    try{
                    int num = stoi(id);
                        eliminarPorID(num);

                    }catch(exception& e){
                    }
                }

                break;
            }
            case 5: {
                string artista;
                bool hay;
                cout << "Ingrese el nombre del artista a buscar: ";
                cin.ignore();
                getline(cin, artista);
                buscarPorArtista(artista,hay);

                if(hay){
                    string id;
                    cout<<endl;
                    cout<<"Para eliminar coloca ( ID ) - Para cancelar ( N o n ): ";
                    cin >> id;

                    try{
                    int num = stoi(id);
                        eliminarPorID(num);

                    }catch(exception& e){
                    }
                }

                break;
            }
            case 0:
                cout << "Saliendo del programa. ¡Hasta luego!\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 0);

    liberarMemoria();
    return 0;
}
