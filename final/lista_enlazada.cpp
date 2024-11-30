#include "lista_enlazada.h"

Nodo* cabeza = nullptr;
Nodo* cola = nullptr;

void Cancionn::mostrar() const {
    cout << left
    //<< setw(7) << id
    << setw(20) << artist_name
    << setw(45) << track_name
    << setw(26) << track_id
    << setw(13) << popularity
    << setw(7) << year
    << setw(20) << genre
    /*<< setw(13) << danceability
    << setw(7) << energy
    << setw(4) << key
    << setw(9) << loudness
    << setw(5) << mode
    << setw(12) << speechiness
    << setw(13) << acousticness
    << setw(17) << instrumentalness
    << setw(8) << liveness
    << setw(8) << valence
    << setw(8) << tempo*/
    << setw(13) << duration_ms<< "ms"
    //<< setw(15) << time_signature


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
            cout << "Cancion con ID " << id << " eliminada.\n";
            return;
        }
        actual = actual->siguiente;
    }
    cout << "No se encontro una cancion con ID " << id << ".\n";
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
        cout << "La lista de canciones est� vacia.\n";
        return;
    }
    Nodo* actual = cabeza;
    cout << left <<setw(4) <<"N."
         //<< setw(7) << "id"
         << setw(20) << "artist_name"
         << setw(45) << "track_name"
         << setw(26) << "track_id"
         << setw(13) << "popularity"
         << setw(7) << "year"
         << setw(20) << "genre"
         /*<< setw(13) << "danceability"
         << setw(7) << "energy"
         << setw(4) << "key"
         << setw(9) << "loudness"
         << setw(5) << "mode"
         << setw(12) << "speechiness"
         << setw(13) << "acousticness"
         << setw(17) << "instrumentalness"
         << setw(8) << "liveness"
         << setw(8) << "valence"
         << setw(8) << "tempo"*/
         << setw(13) << "duration_ms"<< "ms"
         //<< setw(15) << "time_signature"
         << endl;

    cout << string(145, '-') << endl;
    int sumar1=1;
    while (actual) {
        cout << setw(4) << sumar1++;
        actual->cancion.mostrar();
        actual = actual->siguiente;
    }
}

void ordenarPorCriterio(int criterio,int orden) {
    vector<Cancionn> canciones;
    Nodo* actual = cabeza;

    while (actual) {
        canciones.push_back(actual->cancion);
        actual = actual->siguiente;
    }

    sort(canciones.begin(), canciones.end(), [criterio, orden](const Cancionn& a, const Cancionn& b) {
        if (orden == 1) {
            switch (criterio) {
                case 1: return a.id > b.id; break;
                case 2: return a.artist_name > b.artist_name; break;
                case 3: return a.track_name > b.track_name; break;
                case 4: return a.track_id > b.track_id; break;
                case 5: return a.popularity > b.popularity; break;
                case 6: return a.year > b.year; break;
                case 7: return a.genre > b.genre; break;
                case 8: return a.danceability > b.danceability; break;
                case 9: return a.energy > b.energy; break;
                case 10: return a.key > b.key; break;
                case 11: return a.loudness > b.loudness; break;
                case 12: return a.mode > b.mode; break;
                case 13: return a.speechiness > b.speechiness; break;
                case 14: return a.acousticness > b.acousticness; break;
                case 15: return a.instrumentalness > b.instrumentalness; break;
                case 16: return a.liveness > b.liveness; break;
                case 17: return a.valence > b.valence; break;
                case 18: return a.tempo > b.tempo; break;
                case 19: return a.duration_ms > b.duration_ms; break;
                case 20: return a.time_signature > b.time_signature; break;
                default:
                    cout << "Vuelve a ingresar una opci�n v�lida" << endl;
                    return false;
            }
        } else if (orden == 0) {
            switch (criterio) {
                case 1: return a.id < b.id; break;
                case 2: return a.artist_name < b.artist_name; break;
                case 3: return a.track_name < b.track_name; break;
                case 4: return a.track_id < b.track_id; break;
                case 5: return a.popularity < b.popularity; break;
                case 6: return a.year < b.year; break;
                case 7: return a.genre < b.genre; break;
                case 8: return a.danceability < b.danceability; break;
                case 9: return a.energy < b.energy; break;
                case 10: return a.key < b.key; break;
                case 11: return a.loudness < b.loudness; break;
                case 12: return a.mode < b.mode; break;
                case 13: return a.speechiness < b.speechiness; break;
                case 14: return a.acousticness < b.acousticness; break;
                case 15: return a.instrumentalness < b.instrumentalness; break;
                case 16: return a.liveness < b.liveness; break;
                case 17: return a.valence < b.valence; break;
                case 18: return a.tempo < b.tempo; break;
                case 19: return a.duration_ms < b.duration_ms; break;
                case 20: return a.time_signature < b.time_signature; break;
                default:
                    cout << "Vuelve a ingresar una opci�n v�lida" << endl;
                    return false;
            }
        } else {
            cout << "Ingresa una opci�n v�lida" << endl;
            return false;
        }
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
    cout << "Resultados de busqueda para el nombre de cancion \"" << nombre << "\":\n";

    cout << left <<setw(4) <<"N."
         //<< setw(7) << "id"
         << setw(20) << "artist_name"
         << setw(45) << "track_name"
         << setw(26) << "track_id"
         << setw(13) << "popularity"
         << setw(7) << "year"
         << setw(20) << "genre"
         /*<< setw(13) << "danceability"
         << setw(7) << "energy"
         << setw(4) << "key"
         << setw(9) << "loudness"
         << setw(5) << "mode"
         << setw(12) << "speechiness"
         << setw(13) << "acousticness"
         << setw(17) << "instrumentalness"
         << setw(8) << "liveness"
         << setw(8) << "valence"
         << setw(8) << "tempo"*/
         << setw(13) << "duration_ms"<< "ms"
         //<< setw(15) << "time_signature"
         << endl;

    cout << string(145, '-') << endl;

    int sumar2=1;
    while (actual) {
        if (actual->cancion.track_name == nombre) {
            cout << setw(3) << sumar2++;
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
    cout << "Resultados de busqueda para el artista \"" << artista << "\":\n";

    cout << left <<setw(4) <<"N."
         //<< setw(7) << "id"
         << setw(20) << "artist_name"
         << setw(45) << "track_name"
         << setw(26) << "track_id"
         << setw(13) << "popularity"
         << setw(7) << "year"
         << setw(20) << "genre"
         /*<< setw(13) << "danceability"
         << setw(7) << "energy"
         << setw(4) << "key"
         << setw(9) << "loudness"
         << setw(5) << "mode"
         << setw(12) << "speechiness"
         << setw(13) << "acousticness"
         << setw(17) << "instrumentalness"
         << setw(8) << "liveness"
         << setw(8) << "valence"
         << setw(8) << "tempo"*/
         << setw(13) << "duration_ms"<< "ms"
         //<< setw(15) << "time_signature"
         << endl;

    cout << string(145, '-') << endl;
    int sumar3=0;
    while (actual) {
        if (actual->cancion.artist_name == artista) {
            cout << setw(4) << sumar3++;
            actual->cancion.mostrar();
            encontrado = true;
        }
        actual = actual->siguiente;
    }
    hay = encontrado;
}
