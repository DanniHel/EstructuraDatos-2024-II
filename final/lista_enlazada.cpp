#include "lista_enlazada.h"

Nodo* cabeza = nullptr;
Nodo* cola = nullptr;

void Cancionn::mostrar() const {
    cout << left
    << setw(7) << id
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
        cout << "La lista de canciones está vacia.\n";
        return;
    }
    Nodo* actual = cabeza;
    cout << left <<setw(4) <<"N."
         << setw(7) << "id"
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
void ordenarPorCriterio(int criterio, int orden) {
    vector<Cancionn> canciones;
    Nodo* actual = cabeza;

    while (actual) {
        canciones.push_back(actual->cancion);
        actual = actual->siguiente;
    }

    if (criterio == 21) {
        // Orden aleatorio usando shuffle
        random_device rd;  // Obtener una semilla aleatoria
        mt19937 g(rd());   // Generador de números aleatorios
        shuffle(canciones.begin(), canciones.end(), g);  // Mezclar aleatoriamente
    } else if (criterio == 22) {
        // Mover una canción
        int idCancion;
        int espacios; // Cantidad de espacios a mover
        int posicion;
        cout << "Ingresa el ID de la cancion que deseas mover: ";
        cin >> idCancion;
        cout << "A que posicion desea mover: ";
        cin >> posicion;

        // Buscar la canción en la lista
        auto it = find_if(canciones.begin(), canciones.end(), [idCancion](const Cancionn& c) {
            return c.id == idCancion;
        });


        if (it != canciones.end()) {
            int index = distance(canciones.begin(), it);
            espacios=posicion-1 - index;
            int nuevoIndex = index + espacios;

            // Verificar que el movimiento esté dentro de los límites
            if (nuevoIndex >= 0 && nuevoIndex < canciones.size()) {
                if(espacios>0){
                    for(int i=index;i<nuevoIndex;i++){
                        // Realizar el movimiento de la canción
                        swap(canciones[i], canciones[i+1]);
                    }
                }else{
                    for(int i=index;i>nuevoIndex;i--){
                        // Realizar el movimiento de la canción
                        swap(canciones[i], canciones[i-1]);
                    }
                }

            } else {
                cout << "No se puede mover la canción esa cantidad de espacios, está fuera de los límites." << endl;
            }
        } else {
            cout << "Canción no encontrada." << endl;
        }
    } else {
        // Ordenar por criterio
        sort(canciones.begin(), canciones.end(), [criterio, orden](const Cancionn& a, const Cancionn& b) {
            if (orden == 1) {
                switch (criterio) {
                    case 1: return a.id > b.id;
                    case 2: return a.artist_name > b.artist_name;
                    case 3: return a.track_name > b.track_name;
                    case 4: return a.track_id > b.track_id;
                    case 5: return a.popularity > b.popularity;
                    case 6: return a.year > b.year;
                    case 7: return a.genre > b.genre;
                    case 8: return a.danceability > b.danceability;
                    case 9: return a.energy > b.energy;
                    case 10: return a.key > b.key;
                    case 11: return a.loudness > b.loudness;
                    case 12: return a.mode > b.mode;
                    case 13: return a.speechiness > b.speechiness;
                    case 14: return a.acousticness > b.acousticness;
                    case 15: return a.instrumentalness > b.instrumentalness;
                    case 16: return a.liveness > b.liveness;
                    case 17: return a.valence > b.valence;
                    case 18: return a.tempo > b.tempo;
                    case 19: return a.duration_ms > b.duration_ms;
                    case 20: return a.time_signature > b.time_signature;
                    default:
                        cout << "Vuelve a ingresar una opción válida" << endl;
                        return false;
                }
            } else if (orden == 0) {
                switch (criterio) {
                    case 1: return a.id < b.id;
                    case 2: return a.artist_name < b.artist_name;
                    case 3: return a.track_name < b.track_name;
                    case 4: return a.track_id < b.track_id;
                    case 5: return a.popularity < b.popularity;
                    case 6: return a.year < b.year;
                    case 7: return a.genre < b.genre;
                    case 8: return a.danceability < b.danceability;
                    case 9: return a.energy < b.energy;
                    case 10: return a.key < b.key;
                    case 11: return a.loudness < b.loudness;
                    case 12: return a.mode < b.mode;
                    case 13: return a.speechiness < b.speechiness;
                    case 14: return a.acousticness < b.acousticness;
                    case 15: return a.instrumentalness < b.instrumentalness;
                    case 16: return a.liveness < b.liveness;
                    case 17: return a.valence < b.valence;
                    case 18: return a.tempo < b.tempo;
                    case 19: return a.duration_ms < b.duration_ms;
                    case 20: return a.time_signature < b.time_signature;
                    default:
                        cout << "Vuelve a ingresar una opcion valida ---" << endl;
                        return false;
                }
            } else {
                cout << "Ingresa una opcion valida" << endl;
                return false;
            }
        });
    }

    liberarMemoria();
    for (const auto& cancion : canciones) {
        agregarCancion(cancion);
    }
    cout << "Lista ordenada por " << criterio << ".\n";
}



void buscarPorNombre(const string& nombre, bool& hay) {
    Nodo* actual = cabeza;
    bool encontrado = false;
    cout <<endl<< "Resultados de busqueda para el nombre de cancion \"" << nombre << "\":\n";
    cout<<endl;
    cout << left <<setw(4) <<"N."
         << setw(7) << "id"
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
        if (actual->cancion.track_name.find(nombre)==0) {
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
    cout <<endl<< "Resultados de busqueda para el artista \"" << artista << "\":\n";
    cout<<endl;
    cout << left <<setw(4) <<"N."
         << setw(7) << "id"
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
    int sumar3=1;
    while (actual) {
        if (actual->cancion.artist_name.find(artista)==0) {
            cout << setw(4) << sumar3++;
            actual->cancion.mostrar();
            encontrado = true;
        }
        actual = actual->siguiente;
    }
    hay = encontrado;
}
