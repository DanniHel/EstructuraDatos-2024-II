// trie.cpp
#include "trie.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

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
NodoTrie* insertar_palabra(NodoTrie* raiz, const std::string& palabra, const std::string& track_id) {
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

    return raiz;
}

// Función recursiva para imprimir el Trie
void imprimir_trie(NodoTrie* raiz, std::string palabra) {
    if (raiz == nullptr) return;

    // Si es un nodo hoja, imprimir la palabra formada hasta ese punto
    if (raiz->es_hoja) {
        std::cout << "Canción: " << palabra << ", Track ID: " << raiz->track_id << std::endl;
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
void imprimir_trie_mas(NodoTrie* raiz, std::string palabra, TablaHash& tablaHash) {
    if (raiz == nullptr) return;

    // Si es un nodo hoja, significa que hemos encontrado una palabra completa
    if (raiz->es_hoja) {
        try {
            // Usamos el track_id del nodo para buscar la canción en la tabla hash
            Cancion cancion = tablaHash.buscar(raiz->track_id);

            // Mostrar los detalles de la canción
            std::cout << "Canción: " << palabra << ",\n Track ID: " << raiz->track_id << std::endl;
            std::cout << "Artista: " << cancion.artista << std::endl;
            std::cout << "Año: " << cancion.anio << ", Género: " << cancion.genero << std::endl;
            std::cout << "Popularidad: " << cancion.popularidad << ", Danceabilidad: " << cancion.danceabilidad << std::endl;
            std::cout << "Duración: " << cancion.duracion << " ms" << std::endl;
            std::cout << "Tempo: " << cancion.tempo << ", Clave: " << cancion.clave << std::endl;
            std::cout << "Volumen: " << cancion.volumen << ", Modo: " << cancion.modo << std::endl;
            std::cout << std::endl;
        } catch (const std::runtime_error& e) {
            std::cout << "Error al recuperar la canción con Track ID: " << raiz->track_id << std::endl;
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
void buscar_por_prefijo(NodoTrie* raiz, const std::string& prefijo, TablaHash& tablaHash) {
    NodoTrie* actual = raiz;
    // Recorrer el prefijo
    for (char c : prefijo) {
        if (c >= ' ' && c <= '~') {  // Solo buscar caracteres imprimibles
            int indice = obtener_indice_char(c);
            if (actual->hijos[indice] == nullptr) {
                std::cout << "No se encontraron palabras con este prefijo." << std::endl;
                return;
            }
            actual = actual->hijos[indice];
        }
    }

    // Si encontramos el nodo correspondiente al prefijo, imprimir todas las palabras que empiezan con él
    imprimir_trie_mas(actual, prefijo, tablaHash);
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

        // Si el nombre de la canción está vacío o es inválido, continuar
        if (track_name.empty() || track_name == "track_name") {
            continue;
        }

        // Insertar la canción en el Trie junto con su track_id
        raiz = insertar_palabra(raiz, track_name, track_id);
    }

    file.close();
    return raiz;
}
