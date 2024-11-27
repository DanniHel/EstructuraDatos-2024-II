#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

#define MAX_CHARACTERS 95  // ASCII imprimible desde el espacio hasta '~'

// Estructura de un nodo en el Trie
struct NodoTrie {
    char dato;                   // Caracter almacenado en el nodo
    NodoTrie* hijos[MAX_CHARACTERS]; // Array de punteros a los hijos (95 caracteres posibles)
    bool es_hoja;                // Flag que indica si es un nodo hoja (es una palabra completa)

    // Constructor para inicializar el nodo
    NodoTrie(char dato) {
        this->dato = dato;
        this->es_hoja = false;
        for (int i = 0; i < MAX_CHARACTERS; i++) {
            this->hijos[i] = nullptr;
        }
    }
};

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

// Inserta una palabra en el Trie
NodoTrie* insertar_palabra(NodoTrie* raiz, const std::string& palabra) {
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

    return raiz;
}

// Función recursiva para imprimir el Trie
void imprimir_trie(NodoTrie* raiz, std::string palabra = "") {
    if (raiz == nullptr) return;

    // Si es un nodo hoja, imprimir la palabra formada hasta ese punto
    if (raiz->es_hoja) {
        std::cout << palabra << std::endl;
    }

    // Recorrer los hijos
    for (int i = 0; i < MAX_CHARACTERS; i++) {
        if (raiz->hijos[i] != nullptr) {
            imprimir_trie(raiz->hijos[i], palabra + raiz->hijos[i]->dato);
        }
    }
}

// Función para leer el archivo CSV y procesar las canciones
NodoTrie* procesar_archivo(const std::string& archivo, NodoTrie* raiz) {
    std::ifstream file(archivo);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return raiz;
    }

    // Saltar la cabecera del CSV
    std::getline(file, line);

    // Procesar cada línea del archivo
    //int count = 0;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string n, artist_name, track_name, track_id, popularity, year, genre;
        std::string danceability, energy, key, loudness, mode, speechiness, acousticness;
        std::string instrumentalness, liveness, valence, tempo, duration_ms, time_signature;

        // Leer los campos del CSV separados por comas
        std::getline(ss, n, ',');
        std::getline(ss, artist_name, ',');
        std::getline(ss, track_name, ',');
        std::getline(ss, track_id, ',');
        std::getline(ss, popularity, ',');
        std::getline(ss, year, ',');
        std::getline(ss, genre, ',');
        std::getline(ss, danceability, ',');
        std::getline(ss, energy, ',');
        std::getline(ss, key, ',');
        std::getline(ss, loudness, ',');
        std::getline(ss, mode, ',');
        std::getline(ss, speechiness, ',');
        std::getline(ss, acousticness, ',');
        std::getline(ss, instrumentalness, ',');
        std::getline(ss, liveness, ',');
        std::getline(ss, valence, ',');
        std::getline(ss, tempo, ',');
        std::getline(ss, duration_ms, ',');
        std::getline(ss, time_signature, ',');

        // Imprimir la canción leída para depuración
        if (track_name.empty() || track_name == "track_name") {
            continue;  // Ignorar filas defectuosas
        }

        // Depuración: imprimir el nombre de la canción
        //std::cout << "Procesando canción #" << count + 1 << ": " << track_name << std::endl;
        //count++;

        // Insertar la canción en el Trie
        raiz = insertar_palabra(raiz, track_name);
    }

    file.close();
    return raiz;
}

int main() {
    NodoTrie* raiz = nullptr;

    // Procesar el archivo CSV y cargar las canciones en el Trie
    raiz = procesar_archivo("spotify_data_mini.csv", raiz);

    // Imprimir el Trie (debería imprimir las canciones almacenadas)
    std::cout << "Contenido del Trie: \n";
    imprimir_trie(raiz);

    // Liberar la memoria del Trie
    liberar_trie(raiz);

    return 0;
}
