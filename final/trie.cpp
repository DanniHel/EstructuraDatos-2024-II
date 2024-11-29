// trie.cpp
#include "trie.h"

// Constructor para inicializar el nodo
NodoTrie::NodoTrie(char dato) {
    this->dato = dato;
    this->es_hoja = false;
    this->track_id = "";  // Inicialmente sin track_id
    for (int i = 0; i < MAX_CHARACTERS; i++) {
        this->hijos[i] = nullptr;
    }
}

// Crea un nuevo nodo en el Trie
NodoTrie* crear_nodo_trie(char dato) {
    return new NodoTrie(dato);  // Crear un nodo con el carácter dado
}

// Función auxiliar para liberar el Trie usando DFS (Depth-First Search)
void liberar_trie(NodoTrie* raiz) {
    if (raiz == nullptr) return;

    // Recorrer los hijos
    for (int i = 0; i < MAX_CHARACTERS; i++) {
        liberar_trie(raiz->hijos[i]);
    }

    // Liberar el nodo actual
    delete raiz;
}

// Función para obtener el índice del carácter en el arreglo de hijos
int obtener_indice_char(char c) {
    return c - ' ';  // Mapeo de caracteres imprimibles (desde ' ' hasta '~')
}

// Inserta una palabra en el Trie y guarda el track_id
NodoTrie* insertar_palabra(NodoTrie* raiz, const string& palabra, const string& track_id, int& cont1) {
    if (raiz == nullptr) {
        raiz = crear_nodo_trie('\0');  // Crear la raíz si no existe
    }

    NodoTrie* actual = raiz;
    for (char c : palabra) {
        if (c >= ' ' && c <= '~') {  // Solo insertar caracteres imprimibles
            int indice = obtener_indice_char(c);  // Calcular el índice para el carácter actual
            if (actual->hijos[indice] == nullptr) {
                // Crear un nuevo nodo si no existe
                actual->hijos[indice] = crear_nodo_trie(c);
            }
            actual = actual->hijos[indice];  // Avanzar al siguiente nodo
        }
    }
    actual->es_hoja = true;  // Marcar el nodo como un nodo hoja (palabra completa)
    actual->track_id = track_id;  // Asignar el track_id en el nodo hoja
    cont1++;
    return raiz;
}

// Función recursiva para imprimir el Trie
void imprimir_trie(NodoTrie* raiz, string palabra) {
    if (raiz == nullptr) return;

    // Si es un nodo hoja, imprimir la palabra formada hasta ese punto
    if (raiz->es_hoja) {
        cout << "Canción: " << palabra << endl;
    }

    // Recorrer los hijos
    for (int i = 0; i < MAX_CHARACTERS; i++) {
        if (raiz->hijos[i] != nullptr) {
            imprimir_trie(raiz->hijos[i], palabra + raiz->hijos[i]->dato);
        }
    }
}
//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// Modificamos la función imprimir_trie para buscar y mostrar información desde la tabla hash

void imprimir_trie_mas(NodoTrie* raiz, string palabra, TablaHash& tablaHash) {
    static int num=1;
    if (raiz == nullptr) {
        return;
    }
    // Si es un nodo hoja, significa que hemos encontrado una palabra completa
    if (raiz->es_hoja) {

        try {
            // Usamos el track_id del nodo para buscar la canción en la tabla hash
            Cancion cancion = tablaHash.buscar(raiz->track_id);

            // Mostrar los detalles de la canción
            cout<<"N: "<<num<<endl;
            cout << "Canción: " << palabra << ", Track ID: " << raiz->track_id << endl;

            cout << "Artista: " << cancion.artista << endl;
            cout << "Año: " << cancion.anio << ", Género: " << cancion.genero << endl;
            cout << "Popularidad: " << cancion.popularidad << ", Danceabilidad: " << cancion.danceabilidad << endl;
            cout << "Duración: " << cancion.duracion << " ms" << endl;
            cout << "Tempo: " << cancion.tempo << ", Clave: " << cancion.clave << endl;
            cout << "Volumen: " << cancion.volumen << ", Modo: " << cancion.modo << endl;
            cout << endl;
            num++;
        } catch (const runtime_error& e) {
            cout << "Error al recuperar la canción con Track ID: " << raiz->track_id << endl;
        }
    }

    // Recorrer los hijos del nodo actual
    for (int i = 0; i < MAX_CHARACTERS; i++) {
        if (raiz->hijos[i] != nullptr) {
            imprimir_trie_mas(raiz->hijos[i], palabra + raiz->hijos[i]->dato, tablaHash);
        }
    }
}
//__________________________________________________________________________________________


// Función para buscar canciones por prefijo y recuperar track_id
void buscar_por_prefijo(NodoTrie* raiz, const string& prefijo, TablaHash& tablaHash) {
    NodoTrie* actual = raiz;
    // Recorrer el prefijo
    for (char c : prefijo) {
        if (c >= ' ' && c <= '~') {  // Solo buscar caracteres imprimibles
            int indice = obtener_indice_char(c);
            if (actual->hijos[indice] == nullptr) {
                cout << "No se encontraron palabras con este prefijo." << endl;
                return;
            }
            actual = actual->hijos[indice];
        }
    }
    int num;
    // Si encontramos el nodo correspondiente al prefijo, imprimir todas las palabras que empiezan con él
    imprimir_trie_mas(actual, prefijo, tablaHash);
}
//-----------------------------------------------------------------------------------------------
//-----------------------------Iserción para la lista enlazada-----------------------------------
//-----------------------------------------------------------------------------------------------
//busqueda y recuperación de track_id

// Función auxiliar para realizar el recorrido DFS y recolectar los track_id
void recolectar_track_ids(NodoTrie* nodo, const string& palabra, vector<string>& track_ids) {
    if (nodo == nullptr) return;

    // Si es un nodo hoja, agregar el track_id al vector
    if (nodo->es_hoja) {
        track_ids.push_back(nodo->track_id);  // Agregar el track_id encontrado
    }

    // Recorrer los hijos
    for (int i = 0; i < MAX_CHARACTERS; i++) {
        if (nodo->hijos[i] != nullptr) {
            recolectar_track_ids(nodo->hijos[i], palabra + nodo->hijos[i]->dato, track_ids);
        }
    }
}

// Modificamos la función buscar_por_prefijo para que retorne una lista de track_id
vector<string> buscar_prefijo(NodoTrie* raiz, const string& prefijo) {
    vector<string> track_ids;
    NodoTrie* actual = raiz;

    // Recorrer el prefijo
    for (char c : prefijo) {
        if (c >= ' ' && c <= '~') {  // Solo buscar caracteres imprimibles
            int indice = obtener_indice_char(c);
            if (actual->hijos[indice] == nullptr) {
                // Si no se encuentra el prefijo, retornar lista vacía
                return track_ids;
            }
            actual = actual->hijos[indice];
        }
    }

    // Si encontramos el nodo correspondiente al prefijo, recolectar todos los track_id
    // Realizamos un recorrido en profundidad (DFS) para recolectar los track_ids
    recolectar_track_ids(actual, prefijo, track_ids);

    return track_ids;
}

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

// Función para leer el archivo CSV y procesar las canciones
NodoTrie* procesar_archivo(const string& archivo, NodoTrie* raiz,int& cont1, int& cont2) {
    ifstream file(archivo);
    string line;

    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return raiz;
    }

    // Saltar la cabecera del CSV
    getline(file, line);

    // Procesar cada línea del archivo

    while (getline(file, line)) {
        stringstream ss(line);
        string simbolo;
        string artista, track_name, track_id, genero;
        int id, popularidad, anio, clave, modo, duracion, firmaTiempo; //stoi() ----> convierte a int
        float danceabilidad, energia, volumen, discurso, acustica, instrumentalidad, vivacidad, valencia, tempo;// stof() - convierte a float

        try {
            // Extraemos los datos de la línea
            getline(ss, simbolo, ','); id = stoi(simbolo);  // id
            getline(ss, artista, ',');  // artista
            getline(ss, track_name, ',');  // track_name
            getline(ss, track_id, ',');  // track_id
            getline(ss, simbolo, ','); popularidad = stoi(simbolo);  // popularity
            getline(ss, simbolo, ','); anio = stoi(simbolo);  // year
            getline(ss, genero, ',');  // genre
            getline(ss, simbolo, ','); danceabilidad = stof(simbolo);  // danceability
            getline(ss, simbolo, ','); energia = stof(simbolo);  // energy
            getline(ss, simbolo, ','); clave = stoi(simbolo);  // key
            getline(ss, simbolo, ','); volumen = stof(simbolo);  // loudness
            getline(ss, simbolo, ','); modo = stoi(simbolo);  // mode
            getline(ss, simbolo, ','); discurso = stof(simbolo);  // speechiness
            getline(ss, simbolo, ','); acustica = stof(simbolo);  // acousticness
            getline(ss, simbolo, ','); instrumentalidad = stof(simbolo);  // instrumentalness
            getline(ss, simbolo, ','); vivacidad = stof(simbolo);  // liveness
            getline(ss, simbolo, ','); valencia = stof(simbolo);  // valence
            getline(ss, simbolo, ','); tempo = stof(simbolo);  // tempo
            getline(ss, simbolo, ','); duracion = stoi(simbolo);  // duration_ms
            getline(ss, simbolo, ','); firmaTiempo = stoi(simbolo);  // time_signature

            // Insertar la canción en el Trie junto con su track_id
            raiz = insertar_palabra(raiz, track_name, track_id, cont1);

        } catch (const exception& e) {
            cont2++;
            //cerr << "Error al procesar la línea: " << linea << endl;
        }
    }

    file.close();
    return raiz;
}
