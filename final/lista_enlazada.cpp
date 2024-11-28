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
void buscarPorNombre(const string& nombre) {
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

    if (!encontrado) {
        cout << "No se encontraron canciones con el nombre \"" << nombre << "\".\n";
    }
}

// Función para buscar canciones por nombre del artista
void buscarPorArtista(const string& artista) {
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

    if (!encontrado) {
        cout << "No se encontraron canciones del artista \"" << artista << "\".\n";
    }
}

// Programa principal para probar las funciones
int main() {
    // Agregar canciones
    agregarCancion({0, "Jason Mraz", "I Won't Give Up", "53QF56cjZA9RTuuMZDrSA6", 68, 2012, "acoustic", 0.483, 0.303, 4, -10.058, 1, 0.0429, 0.694, 0.0, 0.115, 0.139, 133.406, 240166, 3});
    agregarCancion({1, "Jason Mraz", "93 Million Miles", "1s8tP3jP4GZcyHDsjvw218", 50, 2012, "acoustic", 0.572, 0.454, 3, -10.286, 1, 0.0258, 0.477, 1.37e-05, 0.0974, 0.515, 140.182, 216387, 4});
    cout<<endl;
    // Mostrar lista de canciones
    mostrarLista();
    cout<<endl;
    // Eliminar una canción por ID
    eliminarPorID(0);
    cout<<endl;
    // Mostrar lista actualizada
    mostrarLista();
    cout<<endl;
    // Ordenar por popularidad
    ordenarPorCriterio("popularity");
    mostrarLista();
    cout<<endl;

    // Buscar por nombre de canción
    cout << "\nBusqueda por nombre de cancion:\n";
    buscarPorNombre("93 Million Miles");

    // Buscar por nombre de artista
    cout << "\nBusqueda por nombre de artista:\n";
    buscarPorArtista("Jason Mraz");


    // Liberar memoria antes de finalizar
    liberarMemoria();
    return 0;
}
