#include "lista_enlazada.h"

Nodo* cabeza = nullptr;
Nodo* cola = nullptr;

void Cancionn::mostrar() const {
    cout << left << setw(5) << id
         << setw(20) << artist_name
         << setw(25) << track_name
         << setw(15) << popularity
         << setw(10) << year
         << setw(15) << genre
         << setw(10) << duration_ms << "ms"
         << endl;
}

void liberarMemoria() {
    Nodo* actual = cabeza;
    while (actual) {
        Nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = cola = nullptr;
}

void agregarCancion(const Cancionn& cancion) {
    Nodo* nuevo = new Nodo{cancion, nullptr, cola};
    if (!cabeza) {
        cabeza = cola = nuevo;
    } else {
        cola->siguiente = nuevo;
        cola = nuevo;
    }
}

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

void ordenarPorCriterio(const string& criterio) {
    vector<Cancionn> canciones;
    Nodo* actual = cabeza;

    while (actual) {
        canciones.push_back(actual->cancion);
        actual = actual->siguiente;
    }

    sort(canciones.begin(), canciones.end(), [&criterio](const Cancionn& a, const Cancionn& b) {
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

void buscarPorNombre(const string& nombre, bool& hay) {
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
    hay = encontrado;
}

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
    hay = encontrado;
}
